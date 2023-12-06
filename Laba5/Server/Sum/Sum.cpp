#include<iostream>
#include<string>
#include<windows.h>
#include<vector>
#include<conio.h>

using namespace std;

int main(int argc, char* argv[])
{
    HANDLE hWritePipe, hReadPipe;
    int N;
    int arraySize;

    vector<double> result;
    hWritePipe = (HANDLE)atoi(argv[1]);
    hReadPipe = (HANDLE)atoi(argv[2]);
    DWORD bytesWritten;

    if (!ReadFile(hReadPipe, &arraySize, sizeof(arraySize), &bytesWritten, NULL))
    {
        cout << "array size read is failed " << endl;
        return GetLastError();
    }

    double* arr = new double[arraySize+1];

    if (!ReadFile(hReadPipe, arr, sizeof(double) * arraySize, &bytesWritten, NULL))
    {
        cout << "array  read is failed " << endl;
        return GetLastError();
    }
    if (!ReadFile(hReadPipe, &N, sizeof(N), &bytesWritten, NULL))
    {
        cout << "N read is failed " << endl;
        return GetLastError();
    }

  
    double sumOfSquares = 0;
    for (int i = 0; i < arraySize; i++) {
        if (arr[i] > N) {
            arr[i] *= arr[i];
            sumOfSquares += arr[i];
            
        }
        
        cout << arr[i] << "   ";
       
    }
          
    result.push_back(sumOfSquares);  
    arr[arraySize] = sumOfSquares;

    cout << endl;
    _cprintf("sum with numbers greater than N: \n");
    for (int i = 0; i < result.size(); i++)
    {
        _cprintf("%f ", result[i]);
    }

    for (int i = 0; i <= arraySize; i++)
    {
        DWORD dwB;
        if (!WriteFile(hWritePipe, &arr[i], sizeof(arr[i]), &dwB, NULL))
        {
            _getch();
            return GetLastError();
        }
    }
  
    _cprintf("\nPress any key to exit ");
    _getch();

}


