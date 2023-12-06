#include<iostream>
#include<ctime>
#include<string>
#include<windows.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int arraySize, N;
    cout << "Enter array size: " << endl;
    cin >> arraySize;
    double sumOfSquares;

    double* arr = new double[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        arr[i] = ((double)(rand() % 1000 - 500)) / 10;
    }
    for (int i = 0; i < arraySize; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
    cout << "Enter N:" << endl;
    cin >> N;

    HANDLE hWritePipe, hReadPipe;
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
    {
        cout << "create pipe is failed" << endl;
        return GetLastError();
    }

    DWORD bytesWritten;
   
    WriteFile(hWritePipe, &arraySize, sizeof(int), &bytesWritten, NULL);

    WriteFile(hWritePipe, arr, sizeof(double) * arraySize, &bytesWritten, NULL);

    if (!WriteFile(hWritePipe, &N, sizeof(N), &bytesWritten, NULL))
    {
        cout << "N write is failed " << endl;
        return GetLastError();
    }

    string sum_cmd = "Sum.exe " + to_string((int)hWritePipe) + " " + to_string((int)hReadPipe) + " ";
    wstring Wsum_cmd = wstring(sum_cmd.begin(), sum_cmd.end());
    LPWSTR  sum = &Wsum_cmd[0];
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, sum, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        cout << "check sum.exe \n";
        return GetLastError();
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    cout << "Array with squares of numbers > N:" << endl;
    for (int i = 0; i <= arraySize; i++)
    {
        DWORD byteRead;
        double data;
        if (i == arraySize)
        {
            cout << endl << "Sum:" << endl;
        }
        if (!ReadFile(hReadPipe, &data, sizeof(data), &byteRead, NULL))
        {
            cout << "N read is failed " << endl;
            return GetLastError();
        }

        cout << data << " ";
    }

    CloseHandle(hReadPipe);
    CloseHandle(hWritePipe);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    delete[] arr;

    return 0;
}