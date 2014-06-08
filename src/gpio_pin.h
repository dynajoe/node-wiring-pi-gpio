#ifndef BUILDING_NODE_EXTENSION
#define BUILDING_NODE_EXTENSION
#endif
#ifndef MAX6675_H
#define MAX6675_H

#include <node.h>

using namespace v8;

class GPIOPin : node::ObjectWrap {
   public:
      static void Init();
      static Handle<Value> NewInstance(const Arguments& args);
      static Handle<Value> Write(const Arguments& args);
      void SetValue(int value);

   private:
      GPIOPin(int pin, int direction);
      ~GPIOPin();

      static Handle<Value> New(const Arguments& args);
      static Persistent<Function> constructor;

      int m_pin;
};

#endif
