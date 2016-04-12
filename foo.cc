#include <unistd.h>
#include <stdlib.h>
#include "uv.h"
#include "v8.h"
#include "node.h"


using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void *worker(void *data);

int interval = 0;

void foo(uv_async_t *async) {
//  fprintf(stderr, "hello world!\n");
}


void *randomizer(void *data)
{
  while(true) {
    interval = random() % 1009;
    usleep(interval);
  }
  return NULL;
}

void entry(const FunctionCallbackInfo<Value>& args)
{
  for(int i=0;i<5;i++) {
    pthread_t thread;
    pthread_create(&thread, NULL, worker, NULL);
  }
  
  pthread_t rthread;
  pthread_create(&rthread, NULL, randomizer, NULL);
}

void *worker(void *data) {
  while(true) {
    uv_async_t *async = new uv_async_t;
    uv_async_init(uv_default_loop(), async, foo);
    usleep(interval);
    uv_async_send(async);
  }
  return NULL;
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "entry", entry);
}
NODE_MODULE(addon, init)

