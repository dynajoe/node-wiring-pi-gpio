#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "gpio_pin.h"

using namespace v8;

Handle<Value> CreateObject(const Arguments& args) {
   HandleScope scope;
   return scope.Close(GPIOPin::NewInstance(args));
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
   GPIOPin::Init();

   module->Set(String::NewSymbol("exports"),
      FunctionTemplate::New(CreateObject)->GetFunction());
}

NODE_MODULE(GPIOPin, InitAll)