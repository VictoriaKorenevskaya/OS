<<<<<<< HEAD
﻿#include <iostream>
=======
#include <iostream>
>>>>>>> e9219bce2b837fc5ac1cf05cbaf670ed8697a017
#include <Windows.h>

using namespace std;

struct Data {
	int arraySize;
	int* array;
	int time;
};


void reverseArray(int* array, int arraySize) {
	for (int i = 0; i < arraySize / 2; i++) {
		swap(array[i], array[arraySize - 1 - i]);		
	}
}


DWORD WINAPI worker(LPVOID dataRef)
{
	cout << "Thread is started." << endl;

	Data* data = (Data*)dataRef;

	int arraySize = data->arraySize;
	int* array = data->array;
	int time = data->time;

	cout <<"Array size: " << arraySize << '\n';
	cout << "Array:\n";
	for (int i = 0; i < arraySize; ++i) {
		cout << array[i] << ' ';
	}
	cout << endl;

	reverseArray(array, arraySize);
	Sleep(time);

	cout << "Thread is finished." << endl;
	return 1;
}


int main() {
	HANDLE	hWorker;
	DWORD	IDWorker;
	
	int arraySize = 0, timeDeltaStop, timeDeltaStart;

	cout << "Input array size:\n";
	cin >> arraySize;

	int* array = new int[arraySize];

	cout << "Input array elements:\n";
	for (int i = 0; i < arraySize; ++i)
	{
		cin >> array[i];
	}
	
	cout << "Enter the time delta (ms) for stopping the thread:\n";
	cin >> timeDeltaStop;

	cout << "Enter the time delta (ms) for starting the thread:\n";
	cin >> timeDeltaStart;

	Data data;
	data.array = array;
	data.arraySize = arraySize;
	data.time = timeDeltaStop + timeDeltaStart;

	hWorker = CreateThread(NULL, 0, worker, &data, 0, &IDWorker);

	if (hWorker == NULL)
		return GetLastError();

	Sleep(timeDeltaStop);

	SuspendThread(hWorker);
	cout << "Thread stopped\n";

	Sleep(timeDeltaStart);

	ResumeThread(hWorker);
	cout << "Thread started\n";
	
	WaitForSingleObject(hWorker, INFINITE);

	for (int i = 0; i < arraySize; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	CloseHandle(hWorker); 

	system("pause");
	return 0;
}
