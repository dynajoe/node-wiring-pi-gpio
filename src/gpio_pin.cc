#ifndef BUILDING_NODE_EXTENSION
#define BUILDING_NODE_EXTENSION
#endif
#include <node.h>
#include "gpio_pin.h"
extern "C" {
#include <wiringPi.h>
}
using namespace v8;

Persistent<Function> GPIOPin::constructor;

GPIOPin::GPIOPin(int pin, int direction) :
  m_pin(pin)
{
  pinMode(pin, direction ? OUTPUT : INPUT);
}

GPIOPin::~GPIOPin()
{
}

void GPIOPin::Init()
{
  if (wiringPiSetup() == -1) {
    ThrowException(Exception::TypeError(String::New("Unable to setup wiringPi!")));
    return;
  }

  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

  tpl->SetClassName(String::NewSymbol("GPIOPin"));

  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  tpl->PrototypeTemplate()->Set(String::NewSymbol("write"),
    FunctionTemplate::New(Write)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
}

Handle<Value> GPIOPin::New(const Arguments& args)
{
  HandleScope scope;

  Handle<Object> options = Handle<Object>::Cast(args[0]);

  int pin = options->Get(String::New("pin"))->ToInt32()->Value();
  int direction = options->Get(String::New("direction"))->ToInt32()->Value();

  if (args.IsConstructCall()) {
    GPIOPin* obj = new GPIOPin(pin, direction);
    obj->Wrap(args.This());
    return args.This();
  } else {
    const unsigned argc = 1;
    Local<Value> argv[argc] = { args[0] };
    return scope.Close(constructor->NewInstance(argc, argv));
  }
}

Handle<Value> GPIOPin::NewInstance(const Arguments& args)
{
  HandleScope scope;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = { args[0] };
  Local<Object> instance = constructor->NewInstance(argc, argv);

  return scope.Close(instance);
}

Handle<Value> GPIOPin::Write(const Arguments& args)
{
  HandleScope scope;
  GPIOPin* obj = ObjectWrap::Unwrap<GPIOPin>(args.This());
  Local<Integer> value = Local<Integer>::Cast(args[0]);
  obj->SetValue((int)(value->Int32Value()));

  return scope.Close(args.This());
}

void GPIOPin::SetValue(int value)
{
   digitalWrite(this->m_pin, value >= 1 ? HIGH : LOW);
}
