#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <chrono>

#include "barrier.hpp"
#include "RWLock.hpp"

#define READERS_COUNT 3
#define WRITERS_COUNT 1
#define TOTAL_THREADS (READERS_COUNT + WRITERS_COUNT)

std::vector<int> dataVector(100000, 0);
RWLock lock;
int temp;
barrier simpleBarrier(TOTAL_THREADS);
std::vector <long long> threadDurations(TOTAL_THREADS, 0);

void reader14(int index);
void writer14(int index);

int main()
{
    std::vector<std::thread*> readers;
    std::vector<std::thread*> writers;

    int i;

    for (i = 0; i < READERS_COUNT; i++)
        readers.emplace_back(new std::thread(reader14, i));

    for (i = 0; i < WRITERS_COUNT; i++)
        writers.emplace_back(new std::thread(writer14, READERS_COUNT + i));

    for (auto& reader : readers)
        reader->join();

    for (auto& writer : writers)
        writer->join();

    for (i = 0; i < TOTAL_THREADS; i++)
    {
        std::cout << "Thread " << i << " duration: "
            << threadDurations[i] << " nanoseconds" << std::endl;
    }

    return 0;
}

void reader14(int index)
{
    unsigned int i;
    simpleBarrier.count_down_and_wait();
	auto start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < dataVector.size(); i++)
    {
        lock.reader_lock();
        temp = dataVector[i];
        //std::this_thread::sleep_for(std::chrono::milliseconds(300));
        lock.reader_unlock();
    }
	auto end = std::chrono::high_resolution_clock::now();
	threadDurations[index] = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

void writer14(int index)
{
    unsigned int i;
    simpleBarrier.count_down_and_wait();
	auto start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < dataVector.size(); i++)
    {
        lock.writer_lock();       
        dataVector[i] = i;
        //std::this_thread::sleep_for(std::chrono::milliseconds(300));        
        lock.writer_unlock();
        
    }
	auto end = std::chrono::high_resolution_clock::now();
	threadDurations[index] = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}