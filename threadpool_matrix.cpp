// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

#include "ThreadPool.h"


int threadTask(int i, int j, std::vector<std::vector<int>> *mResult, std::vector<std::vector<int>> m1, std::vector<std::vector<int>> m2) {
    (*mResult)[i][j] = m1[i][j] + m2[i][j];

    return 0;
}


int main()
{
    // std thread hardware concurrency gives us the number of cores we have
    // so we can create a threadpool of the number of cores
    ThreadPool pool(std::thread::hardware_concurrency()); // create x threads in the thread pool

    std::vector<std::vector<int>> m1, m2, mResult;

    m1.resize(10);
    m2.resize(10);
    mResult.resize(10);

    //reset seed for random number generation
    srand((unsigned int)time(0));

    for (int index = 0; index < m1.size(); ++index)
    {
        m1[index].resize(10);
        m2[index].resize(10);
        mResult[index].resize(10);

        //fill each element of m1 and m2 with a random number between 0 and 100
        for (int j = 0; j < m1[index].size(); ++j)
        {
            m1[index][j] = rand() % 100;
            m2[index][j] = rand() % 100;
        }
    }
    std::vector<std::future<int>> ret; // ret exists to make sure we let it finish all the calculations before 
    for (int i = 0; i < m1.size(); ++i)
    {
        for (int j = 0; j < m1[i].size(); ++j)
        {
            ret.push_back(pool.enqueue(threadTask, i, j, &mResult, m1, m2));
        }
    }

    for (int i = 0; i < ret.size();i++)
        ret[i].get(); // the sauce is in .get() as if we recieve a value then it has completed

    for (auto& res : mResult) {
        for (auto& val : res) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    ////write the result to a file
    //std::ofstream outputFile("result.txt");
    //if (outputFile.is_open())
    //{
    //    for (int i = 0; i < m1.size(); ++i)
    //    {
    //        for (int j = 0; j < m1[i].size(); ++j)
    //        {
    //            outputFile << std::setw(3) << m1[i][j] << " ";
    //        }
    //        outputFile << std::endl;
    //    }
    //    outputFile << std::endl;
    //    outputFile << std::endl;

    //    for (int i = 0; i < m2.size(); ++i)
    //    {
    //        for (int j = 0; j < m2[i].size(); ++j)
    //        {
    //            outputFile << std::setw(3) << m2[i][j] << " ";
    //        }
    //        outputFile << std::endl;
    //    }
    //    outputFile << std::endl;
    //    outputFile << std::endl;

    //    for (int i = 0; i < mResult.size(); ++i)
    //    {
    //        for (int j = 0; j < mResult[i].size(); ++j)
    //        {
    //            outputFile << std::setw(3) << mResult[i][j] << " ";
    //        }
    //        outputFile << std::endl;
    //    }
    //    outputFile.close();
    //}
    //else
    //{
    //    std::cerr << "Unable to open file" << std::endl;
    //}
}
