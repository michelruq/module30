#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>

typedef std::function<void()> task_type;

typedef void (*FuncType) (int, int);

class ThreadPool
{
   private:
      std::vector<std::thread> m_threads;
      std::mutex m_locker;
      std::queue<task_type> m_task_queue;
      std::condition_variable m_event_holder;
      volatile bool m_work;

   public:
      void start();
      void stop();
      void push_back(FuncType f, int id, int arg);
      void threadFunction();

};