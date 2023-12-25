#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int main()
{
    HANDLE hMutex = CreateMutex(NULL, FALSE, "WriterMutex");
    HANDLE hSemaphore = CreateSemaphore(NULL, 1, 1, "ReaderSemaphore");
    if (hMutex == NULL || hSemaphore == NULL) {
        return GetLastError();
    }
    HANDLE writerEvents[5];
    HANDLE readerEvents[3];

    for (int i = 0; i < 3; ++i) {
        writerEvents[i] = CreateEvent(NULL, FALSE, FALSE, ("WriterEvent" + to_string(i)).c_str());
        readerEvents[i] = CreateEvent(NULL, FALSE, FALSE, ("ReaderEvent" + to_string(i)).c_str());
        if (writerEvents[i] == NULL || readerEvents[i] == NULL) {
            return GetLastError();
        }
    }

    writerEvents[3] = CreateEvent(NULL, FALSE, FALSE, "WriterEndEvent");
    writerEvents[4] = CreateEvent(NULL, FALSE, FALSE, "ReaderEndEvent");
    int processNumber;
    int messageNumber;

    cout << "Enter number of Writer(Reader) processes: ";
    cin >> processNumber;
    cout << "Enter number of messages: ";
    cin >> messageNumber;

    STARTUPINFO si;
    PROCESS_INFORMATION* w_pi = new PROCESS_INFORMATION[processNumber];
    PROCESS_INFORMATION* read_pi = new PROCESS_INFORMATION[processNumber];
    string writerInfo = to_string(messageNumber);
    string readerInfo;

    for (int i = 0; i < processNumber; ++i) {
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        if (!CreateProcess("x64\\Debug\\Writer.exe", (char*)writerInfo.c_str(), NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &si, &w_pi[i])) {
            cout << " Writer process is not created\n";
            return GetLastError();
        }
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        if (!CreateProcess("x64\\Debug\\Reader.exe", (char*)writerInfo.c_str(), NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &si, &read_pi[i])) {
            cout << " Reader process is not created\n";
            return GetLastError();
        }
    }

    int writerNum = processNumber;
    int readerNum = processNumber;
    while (writerNum || readerNum) {
        DWORD message = WaitForMultipleObjects(5, writerEvents, FALSE, INFINITE);
        switch (message) {
        case 0:
            cout << "Recieved message: A\n";
            PulseEvent(readerEvents[0]);
            break;
        case 1:
            cout << "Recieved message: B\n";
            PulseEvent(readerEvents[1]);
            break;
        case 2:
            cout << "Recieved message: C\n";
            PulseEvent(readerEvents[2]);
            break;
        case 3:
            cout << "Writer Process ended\n";
            --writerNum;
            break;
        case 4:
            cout << "Reader Process ended\n";
            --readerNum;
            break;

        }
    }


    CloseHandle(hMutex);
    CloseHandle(hSemaphore);

    for (int i = 0; i < 3; ++i) {
        CloseHandle(writerEvents[i]);
        CloseHandle(readerEvents[i]);
    }

    CloseHandle(writerEvents[3]);
    CloseHandle(writerEvents[4]);

    for (int i = 0; i < processNumber; ++i) {
        CloseHandle(w_pi[i].hThread);
        CloseHandle(w_pi[i].hProcess);
        CloseHandle(read_pi[i].hThread);
        CloseHandle(read_pi[i].hProcess);
    }

    return 0;
}