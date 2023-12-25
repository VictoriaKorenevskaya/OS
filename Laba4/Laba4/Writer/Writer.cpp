<<<<<<< HEAD
﻿#include <iostream>
=======
#include <iostream>
>>>>>>> 93e8c58e5fc30470e41c5484de3cb24965e449c8
#include <string>
#include <windows.h>

int main(int argc, char* argv[])
{
    HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, "WriterMutex");
    HANDLE writerEvents[4];
    for (int i = 0; i < 3; ++i) {
        writerEvents[i] = OpenEvent(EVENT_MODIFY_STATE, FALSE, ("WriterEvent" + std::to_string(i)).c_str());
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
    for (int i = 0; i < messageNum; ++i) {
        char message;
        std::cout << "Enter message(A, B, C): ";
        std::cin >> message;
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
    std::string s;
    getline(std::cin, s);
    getline(std::cin, s);
    PulseEvent(writerEvents[3]);
    CloseHandle(hMutex);
    for (int i = 0; i < 4; ++i) {
        CloseHandle(writerEvents[i]);
    }
    return 0;
}
