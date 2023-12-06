// laba1.1.cpp : Индивидуальное задание
// Кореневская Виктория, 8 группа
// Поток worker должен выполнить следующую работу:
//       Найти сумму элементов. После каждого суммимрования элементов "спать" 20 миллисенкуд. Завершить свою работу.

#include <iostream>
#include <Windows.h>

using namespace std;


struct Data {
	int arraySize;
	int* array;
	int sum;
};


int sumOfTheElements(int* array, int arraySize) {
	int sum = 0;
	for (int i = 0; i < arraySize; i++) {
		sum += array[i];
	}
	return sum;
	
}

DWORD WINAPI worker(LPVOID dataRef)
{
	cout << "Thread is started." << endl;

	Data* data = (Data*)dataRef;

	int arraySize = data->arraySize;
	int* array = data->array;
	int sum = data->sum;

	cout << "Array size: " << arraySize << '\n';
	cout << "Array:\n";
	for (int i = 0; i < arraySize; ++i) {
		cout << array[i] << ' ';
	}
	cout << endl;
	cout << "Sum of the elements: " << sumOfTheElements(array, arraySize);
	cout << endl;

	Sleep(20);

	cout << "Thread is finished." << endl;
	return 1;
}


int main() {
	HANDLE	hWorker;
	DWORD	IDWorker;

	int arraySize = 0, timeDeltaStop, timeDeltaStart, sum = 0;

	cout << "Input array size:\n";
	cin >> arraySize;

	int* array = new int[arraySize];

	cout << "Input array elements:\n";
	for (int i = 0; i < arraySize; ++i)
	{
		cin >> array[i];
	}

	Data data;
	data.array = array;
	data.arraySize = arraySize;
	data.sum = sum;

	hWorker = CreateThread(NULL, 0, worker, &data, 0, &IDWorker);

	if (hWorker == NULL)
		return GetLastError();

	Sleep(20);

	SuspendThread(hWorker);
	cout << "Thread stopped\n";

	Sleep(20);

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
