//
// Created by denis on 14.11.2021.
//

#include "Spinlock.h"

#include <iostream>

#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>

const int count_to = 10;

volatile int value = 0;

uma::Spinlock l;

int task(int count_to)
{

    std::cout << "Started  " << count_to << std::endl;
    for (int i = 0; i < count_to; ++i)
    {
        l.lock();
        value++;
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        l.unlock();
        // std::cout << "Value  " << value << std::endl;
        // l.unlock();
    }

    return 0;
}

int main(int, char **)
{
    time_t begin, end; // time_t is a datatype to store time values.
    time(&begin);      // note time before execution
    const int num_workers = 5;
    std::vector<std::thread> threads;
    std::cout << "SpinLock inc MyTest start" << std::endl;
    value = 0;
    for (int i = 0; i < num_workers; ++i)
        threads.push_back(std::move(std::thread(task, count_to)));

    for (auto it = threads.begin(); it != threads.end(); it++)
        it->join();
    time(&end); // note time after execution
    double difference = difftime(end, begin);
    std::cout << "job done" << std::endl;
    std::cout << "count_: " << value << std::endl;
    std::cout << "time taken for function() %.2lf seconds.\n"
              << std::endl;

    std::cout << std::fixed << std::setw(11) << std::setprecision(6)
              << std::setfill('0') << difference;
    if (value == count_to * num_workers)
    {
        std::cout << "SpinLock  passed" << std::endl;
        return true;
    }
    else
    {
        std::cout << "SpinLock failed" << std::endl;
        return false;
    }
}