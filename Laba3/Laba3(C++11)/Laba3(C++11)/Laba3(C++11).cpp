// Laba3(C++11).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

vector<double> inputArray, resultArray;
int size_;
int K = 0;
double result = 0;

mutex cs;
condition_variable WorkEvent;
condition_variable CountElementEvent;

void Work()
{
    unique_lock<mutex> lock(cs);
    int count_ = 0;
    for (int i = 0; i < size_; i++)
    {
        if (inputArray[i] > 0)
        {
            resultArray[count_] = inputArray[i];
            count_++;
        }
    }

    WorkEvent.notify_one(); // Notify once after processing all elements

    for (int i = 0; i < size_; i++)
    {
        if (inputArray[i] <= 0)
        {
            resultArray[count_] = inputArray[i];
            count_++;
        }
    }
}

void CountElement()
{
    unique_lock<mutex> lock(cs);
    WorkEvent.wait(lock, [&] { return resultArray.size() >= K; }); // Wait until WorkEvent is notified and resultArray has at least K elements

    for (int i = 0; i < K; i++)
    {
        int a = static_cast<int>(resultArray[i]);
        if (a == resultArray[i])
        {
            result++;
        }
    }

    CountElementEvent.notify_one();
}

int main()
{
    cout << "Enter array size: ";
    if (!(cin >> size_) || size_ <= 0)
    {
        cout << "Invalid array size. Exiting." << endl;
        return 1;
    }

    inputArray.resize(size_);
    resultArray.resize(size_);

    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size_; i++)
    {
        double a;
        cin >> a;
        inputArray[i] = a;
    }

    cout << "Enter the value of K: ";
    if (!(cin >> K) || K <= 0 || K > size_)
    {
        cout << "Invalid value of K. Exiting." << endl;
        return 1;
    }

    thread workThread(Work);
    thread countElementThread(CountElement);

    workThread.join();

    {
        // Acquire the lock before accessing shared variables
        unique_lock<mutex> lock(cs);

        cout << "First K elements: ";
        for (int i = 0; i < K; i++)
        {
            cout << resultArray[i] << " ";
        }

        CountElementEvent.wait(lock);
        cout << endl;
        cout << "The number of integers in the first K elements array: " << result;
    }

    countElementThread.join();

    {
        // Acquire the lock before accessing shared variables
        unique_lock<mutex> lock(cs);

        cout << endl;
        cout << "Remaining elements: ";
        for (int i = K; i < size_; i++)
        {
            cout << resultArray[i] << " ";
        }
    }

    return 0;
}