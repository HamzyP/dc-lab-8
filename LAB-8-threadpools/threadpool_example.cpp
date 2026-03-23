#include <iostream>
#include <vector>
#include <chrono>
#include <string>

#include "ThreadPool.hpp"

int threadTask(int i)
{
    std::string str = "hello " + std::to_string(i) + "\n";
    std::cout << str;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    str = "world " + std::to_string(i) + "\n";
    std::cout << str;
    return i * i;
}

int main()
{

    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue(threadTask, i)
        );
    }

    for (auto&& result : results)
    {
        std::string str = "result: " + std::to_string(result.get()) + "\n";
        std::cout << str;
    }

    std::cout << std::endl;

    return 0;
}
