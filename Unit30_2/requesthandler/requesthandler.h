#pragma once

#include "threadpool.h"
#include "threadpoolqueue.h"

template <typename T>
class RequestHandler {
   public:
       RequestHandler();
       ~RequestHandler();
       // отправка запроса на выполнение
       void pushRequest(FuncType f, int id, int arg);
   private:
       // пул потоков
       T m_tpool;
};

template <typename T>
RequestHandler<T>::RequestHandler()
{
   m_tpool.start();
}

template <typename T>
RequestHandler<T>::~RequestHandler()
{
   m_tpool.stop();
}

template <typename T>
void RequestHandler<T>::pushRequest(FuncType f, int id, int arg)
{
   m_tpool.push_back(f, id, arg);
}

using RequestHandlerThread = RequestHandler<ThreadPool>;
using RequestHandlerThreadQueue = RequestHandler<ThreadPoolQueue>;