// Child.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#define _CDT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <sstream>
#include <Windows.h>
using namespace std;


void BubbleSort(double arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    cout << "Number of elements: " << argc - 1 << endl;

    if (argc <= 1) {
        std::cout << "No arguments provided." << std::endl;
        return 0;
    }

    int size = argc - 1;
    double* values = new double[size];

    for (int i = 0; i < size; i++) {
        values[i] = std::stod(argv[i + 1]);
    }

    BubbleSort(values, size);

    std::cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;

    delete[] values;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize; 

    std::cout << "Enter the width of the buffer (X): ";
    std::cin >> bufferSize.X;

    std::cout << "Enter the height of the buffer (Y): ";
    std::cin >> bufferSize.Y;

    SetConsoleScreenBufferSize(hConsole, bufferSize);

    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

    if (bufferInfo.dwSize.X == bufferSize.X && bufferInfo.dwSize.Y == bufferSize.Y) {
        std::cout << "The size of the buffer is new!" << std::endl;
    }
    else {
        std::cout << ":( " << std::endl;
    }

    _getch();
    return 0;
}
