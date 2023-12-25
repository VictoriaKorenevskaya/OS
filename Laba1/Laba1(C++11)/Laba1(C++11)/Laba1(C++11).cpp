
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <Windows.h>

using namespace std;

struct Data {
    int arraySize;
    vector<int> array; 
    int time;
};

void reverseArray(vector<int>& array) {
    for (size_t i = 0; i < array.size() / 2; i++) {
        swap(array[i], array[array.size() - 1 - i]);
    }
}

DWORD WINAPI worker(LPVOID dataRef) {
    cout << "Thread is started." << endl;

    Data* data = reinterpret_cast<Data*>(dataRef);

    int arraySize = data->arraySize;
    vector<int>& array = data->array; 
    int time = data->time;

    cout << "Array size: " << arraySize << '\n';
    cout << "Array:\n";
    for (const auto& element : array) {
        cout << element << ' ';
    }
    cout << endl;

    reverseArray(array);
    this_thread::sleep_for(chrono::milliseconds(time));

    cout << "Thread is finished." << endl;
    return 1;
}

int main() {
    HANDLE hWorker;
    DWORD IDWorker;

    int arraySize = 0, timeDeltaStop, timeDeltaStart;

    cout << "Input array size:\n";
    cin >> arraySize;

    vector<int> array(arraySize); 

    cout << "Input array elements:\n";
    for (int i = 0; i < arraySize; ++i) {
        cin >> array[i];
    }

    cout << "Enter the time delta (ms) for stopping the thread:\n";
    cin >> timeDeltaStop;

    cout << "Enter the time delta (ms) for starting the thread:\n";
    cin >> timeDeltaStart;

    Data data;
    data.arraySize = arraySize;
    data.array = move(array); 
    data.time = timeDeltaStop + timeDeltaStart;

    hWorker = CreateThread(nullptr, 0, worker, &data, 0, &IDWorker);

    if (hWorker == nullptr)
        return GetLastError();

    this_thread::sleep_for(chrono::milliseconds(timeDeltaStop));

    SuspendThread(hWorker);
    cout << "Thread stopped\n";

    this_thread::sleep_for(chrono::milliseconds(timeDeltaStart));

    ResumeThread(hWorker);
    cout << "Thread started\n";

    WaitForSingleObject(hWorker, INFINITE);

    for (const auto& element : data.array) {
        cout << element << " ";
    }
    cout << endl;

    CloseHandle(hWorker);

    system("pause");
    return 0;
}
