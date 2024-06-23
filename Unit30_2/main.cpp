#include <iostream>
#include "requesthandler.h"
#include "threadpool.h"

std::mutex coutLocker;

void taskFunc(int id, int delay){
   // имитируем время выполнения задачи
   std::this_thread::sleep_for(std::chrono::seconds(delay));
   // выводим информацию о завершении
   std::unique_lock<std::mutex> l(coutLocker);
   std::cout << "task " << id << " made by thread_id " << std::this_thread::get_id() << std::endl;
}

void taskFunc2(int id, int delay){
   std::this_thread::sleep_for(std::chrono::microseconds(delay)); 
}      

int main (int argc, char* argv[])
{
    srand(0);
    RequestHandlerThread rh;
    RequestHandlerThreadQueue rhq;
    auto start = std::chrono::high_resolution_clock::now(); 
    for(int i=0; i<100; i++){
       rh.pushRequest(taskFunc2, i, 1 + rand()%4);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time of " << elapsed.count() << " sec" << std::endl;
    start = std::chrono::high_resolution_clock::now(); 
    for(int i=0; i<100; i++){
       rhq.pushRequest(taskFunc2, i, 1 + rand()%4);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Elapsed time of " << elapsed.count() << " sec" << std::endl;
    return 0;
}