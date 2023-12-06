// Parent.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Кореневская Виктория, 8 группа
//                  Общее задание :
//1. Два проекта(процессы) хранить в одном Solution(Решении) в VS Studio!
//2. В Solution(Решениии) настроить, чтобы.exe файлы лежали в одном Debug!
//3. Объяснить какие данные хранят структуры : STARTUPINFO, PROCESS_INFORMATION.
//4. Написать программы двух консольных процессов Parent и Child, которые выполняют.
// Ввести размер массива, ввести элементы массива;
// Формирует командную строку, которая содержит информацию об размерности массива, элементах и т.д.
//(согласно индивидуальному варианту);
//  3. Установить высоту буфера для Сhild.                          
// Запускает дочерний процесс Child, которому через командную строку передается информация об
//размерности массива, элементах и т.д.;
// 
//           Процесс Child :
//3. Сортировка методом “пузырька”.Полученный массив вывести.Тип элементов - вещественные числа двойной точности
//                                           Примечания.
//1.Для ожидания завершения работы процесса Child и его потока использовать функцию WaitForSingleObject
//2. В Solution(Решениии) настроить, что бы.exe файлы лежали в одном Debug!

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>

using namespace std;

int main()
{
    SetConsoleTitle(L"Parent Window");
    
    cout << "Input array size:\n";
    int arraySize = 0;

    cin >> arraySize;

    int* array = new int[arraySize];

    cout << "Input array elements:\n";
    for (int i = 0; i < arraySize; ++i)
    {
        cin >> array[i];
       
    }

    wstring temp = L"Child.exe"; 
    for (int i = 0; i < arraySize; ++i)
    {
        temp.append(L" ");
        temp.append(to_wstring(array[i]));
    }

    wcout << temp;
    wchar_t commandLine[100];
    wcscpy(commandLine, temp.c_str());
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
   
    CreateProcess(NULL, commandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);


}