#include <iostream>
#include <windows.h>

using namespace std;

double* inputArray, * resultArray;
int size_;
int K = 0;
double result = 0;

CRITICAL_SECTION cs;
HANDLE WorkEvent;
HANDLE CountElementEvent;

DWORD WINAPI Work(LPVOID lpParam)
{
    EnterCriticalSection(&cs);
    int count_ = 0;
    for (int i = 0; i < size_; i++)
    {
        if (inputArray[i] > 0)
        {
            resultArray[count_] = inputArray[i];
            count_++;
        }

        if (K == count_)
        {
            SetEvent(WorkEvent);
        }
    }
    for (int i = 0; i < size_; i++)
    {
        if (inputArray[i] <= 0)
        {
            resultArray[count_] = inputArray[i];
            count_++;
        }

        if (K == count_)
        {
            SetEvent(WorkEvent);
        }
    }
    LeaveCriticalSection(&cs);

    return 0;
}

DWORD WINAPI CountElement(LPVOID lpParam)
{
    WaitForSingleObject(WorkEvent, INFINITE);

    for (int i = 0; i < K; i++)
    {
        int a = resultArray[i];
        if (a == resultArray[i])
        {
            result++;
        }
    }

    SetEvent(CountElementEvent);
    return 0;
}

int main()
{
    InitializeCriticalSection(&cs);
    EnterCriticalSection(&cs);
    WorkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    CountElementEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    cout << "Enter array size: ";
    cin >> size_;
    inputArray = new double[size_];
    resultArray = new double[size_];

    HANDLE hThread[2];
    DWORD dwThread[2];

    hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Work, NULL, 0, &dwThread[0]);
    hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CountElement, NULL, 0, &dwThread[1]);

    double a;
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size_; i++)
    {
        cin >> a;
        inputArray[i] = a;

    }

    cout << "Enter the value of K: ";
    cin >> K;

    LeaveCriticalSection(&cs);

    WaitForSingleObject(WorkEvent, INFINITE);

    cout << "First K elements: ";
    for (int i = 0; i < K; i++)
    {
        cout << resultArray[i] << " ";
    }

    WaitForSingleObject(CountElementEvent, INFINITE);
    cout << endl;
    cout << "The number of integers in the first K elements array : ";
    cout << result;

    WaitForSingleObject(Work, INFINITE);
    cout << endl;
    cout << "Remaining elements: ";
    for (int i = K; i < size_; i++)
    {
        cout << resultArray[i] << " ";
    }

    DeleteCriticalSection(&cs);
    CloseHandle(WorkEvent);
    CloseHandle(CountElementEvent);
}