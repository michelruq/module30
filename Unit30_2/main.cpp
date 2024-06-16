#include <iostream>
#include "requesthandler.h"

std::mutex coutLocker;

void taskFunc(int id, int delay){
   // имитируем время выполнения задачи
   std::this_thread::sleep_for(std::chrono::seconds(delay));
   // выводим информацию о завершении
   std::unique_lock<std::mutex> l(coutLocker);
   std::cout << "task " << id << " made by thread_id " << std::this_thread::get_id() << std::endl;
}

int main (int argc, char* argv[])
{
    srand(0);
    RequestHandler rh;
    for(int i=0; i<20; i++)
       rh.pushRequest(taskFunc, i, 1 + rand()%4);
     return 0;
}