#include "threadpool.h"

void ThreadPool::start()
{
   m_work = true;
   for(int i=0;i<4; i++) {
       m_threads.push_back(std::thread(&ThreadPool::threadFunction, this));
   }
}

void ThreadPool::stop()
{
   m_work = false;
   m_event_holder.notify_all();
   for(auto& t: m_threads) {
       t.join();
   }
}

void ThreadPool::push_back(FuncType f, int id, int arg)
{
    std::lock_guard<std::mutex> l(m_locker);
    task_type new_task([=] {f(id, arg);});
    m_task_queue.push(new_task);
    m_event_holder.notify_one();
}

void ThreadPool::threadFunction()
{
    while(true)
    {
        task_type task_to_do;
        {
           std::unique_lock<std::mutex> l(m_locker);
           if(m_task_queue.empty() && !m_work)
           {
              break;
           }
           if (m_task_queue.empty()) 
           {
              m_event_holder.wait(l, [&](){return !m_task_queue.empty() || !m_work;});
           }
           else
           {
              task_to_do = m_task_queue.front();
              m_task_queue.pop();
           }
        }
        if(task_to_do)
        {
            task_to_do();
        }
    }
}