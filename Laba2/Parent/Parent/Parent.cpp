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
