#include <iostream>
#include <string>
#include <windows.h>

int main(int argc, char* argv[])
{
    HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ReaderSemaphore");
    HANDLE readerEvents[4];

    for (int i = 0; i < 3; ++i) {
        readerEvents[i] = OpenEvent(SYNCHRONIZE, FALSE, ("ReaderEvent" + std::to_string(i)).c_str());
        if (readerEvents[i] == NULL) {
            return GetLastError();
        }
    }
    readerEvents[3] = OpenEvent(EVENT_MODIFY_STATE, FALSE, "ReaderEndEvent");
    if (readerEvents[3] == NULL || hSemaphore == NULL) {
        return GetLastError();
    }
    int messageNum = atoi(argv[0]);
    WaitForSingleObject(hSemaphore, INFINITE);
    while (messageNum) {
        DWORD message = WaitForMultipleObjects(3, readerEvents, FALSE, INFINITE);
        switch (message) {
        case 0:
            std::cout << "Recieved message: A\n";
            break;
        case 1:
            std::cout << "Recieved message: B\n";
            break;
        case 2:
            std::cout << "Recieved message: C\n";
            break;
        }
        --messageNum;
    }
    ReleaseSemaphore(hSemaphore, 1, NULL);
    std::string s;
    getline(std::cin, s);
    PulseEvent(readerEvents[3]);
    CloseHandle(hSemaphore);
    for (int i = 0; i < 4; ++i) {
        CloseHandle(readerEvents[i]);
    }
    return 0;
}


