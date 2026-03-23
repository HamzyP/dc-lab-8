// Ex 13: 

// Evaluate the time improvements of reader / writer lock compared with a standard mutex in ex13 and ex14.For this remove all the printout and measure time the execution from the beginning to the end of each thread;




#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <chrono>

#include "barrier.hpp"

#define READERS_COUNT 3
#define WRITERS_COUNT 1
#define TOTAL_THREADS (READERS_COUNT + WRITERS_COUNT)

std::vector<int> dataVector(100000, 0);
std::mutex dataMutex;
int temp;
barrier simpleBarrier(TOTAL_THREADS);

std::vector <long long> threadDurations(TOTAL_THREADS, 0);

void reader(int index);
void writer(int index);

int main()
{
    std::vector<std::thread> readers;
    std::vector<std::thread> writers;

    int i;

    for (i = 0; i < READERS_COUNT; i++)
        readers.emplace_back(reader, i);

    for (i = 0; i < WRITERS_COUNT; i++)
        writers.emplace_back(writer, READERS_COUNT + i);

    for (auto& reader : readers)
        reader.join();

    for (auto& writer : writers)
        writer.join();

    for (i = 0; i < TOTAL_THREADS; i++)
    {
        std::cout << "Thread " << i << " duration: "
            << threadDurations[i] << " nanoseconds" << std::endl;
    }

    return 0;
}

void reader(int index)
{
    unsigned int i;
    simpleBarrier.count_down_and_wait();

	auto start = std::chrono::high_resolution_clock::now();

    for (i = 0; i < dataVector.size(); i++)
    {
        dataMutex.lock();
        temp = dataVector[i];
        dataMutex.unlock();
    }
    auto end = std::chrono::high_resolution_clock::now();
    threadDurations[index] = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

void writer(int index)
{
    unsigned int i;
    simpleBarrier.count_down_and_wait();
    auto start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < dataVector.size(); i++)
    {
        dataMutex.lock();
        dataVector[i] = i;
        dataMutex.unlock();
    }

	auto end = std::chrono::high_resolution_clock::now();
	threadDurations[index] = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}