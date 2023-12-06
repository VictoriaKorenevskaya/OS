// Laba1.cpp : Кореневская Виктория, 8 группа
//             Написать программу для консольного процесса, который состоит из двух потоков: main и worker. 
//    a) Поток main должен выполнить следующие действия :
//   1. Создать массив целых чисел, размерность и элементы которого вводятся с консоли (или сгенерировать случайно).
//	 2. Ввести время для остановки и запуска потока worker.
//	 3. Создать поток worker, передать в поток данные : размер маcсива, масив и т.д.
//	 4. Приостановить поток worker(SuspendThread), затем через некоторое время снова запустить поток.
//	 5. Уметь создавать поток фкнкциями _beginthreadex и CreateThread
//	 6. Дождаться завершения потока worker.
//	 7. Вывести на консоль результат работы потока worker
//	 8. Завершить работу.
//	b) Глобальные переменные не использовать!
//	c) Розбраться с типами данных, которые используются
//	d) Обяснить: что такое идентификатор и дескриптор, работу функций.

// C++98
#include <iostream>
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