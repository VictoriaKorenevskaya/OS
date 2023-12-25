﻿#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
using namespace std;

int main(int argc, char* argv[])
{
   
    HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, "WriterMutex");
    HANDLE writerEvents[4];

    for (int i = 0; i < 3; ++i) {
        writerEvents[i] = OpenEvent(EVENT_MODIFY_STATE, FALSE, ("WriterEvent" + to_string(i)).c_str());
        if (writerEvents[i] == NULL) {
            return GetLastError();
        }
    }
    writerEvents[3] = OpenEvent(EVENT_MODIFY_STATE, FALSE, "WriterEndEvent");

    if (writerEvents[3] == NULL || hMutex == NULL) {
        return GetLastError();
    }

    int messageNum = atoi(argv[0]);
    WaitForSingleObject(hMutex, INFINITE);
    cout << "mutex active";

    for (int i = 0; i < messageNum; ++i) {
        char message; 

        cout << "Enter message(A, B, C): ";
        cin >> message;

        switch (message) {
        case 'A':
            PulseEvent(writerEvents[0]);
            break;
        case 'B':
            PulseEvent(writerEvents[1]);
            break;
        case 'C':
            PulseEvent(writerEvents[2]);
            break;
        }
    }

    PulseEvent(writerEvents[3]);
    ReleaseMutex(hMutex);

    string s;

    getline(cin, s);
    getline(cin, s);

    PulseEvent(writerEvents[3]);
    CloseHandle(hMutex);

    for (int i = 0; i < 4; ++i) {
        CloseHandle(writerEvents[i]);
    }

    return 0;
   
   // getch();
}
