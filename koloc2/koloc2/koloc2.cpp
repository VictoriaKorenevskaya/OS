#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
using namespace std;

template <typename T>
vector<T> removeDuplicates(vector<T>& input) {

    sort(input.begin(), input.end());
    auto it = unique(input.begin(), input.end());

    input.erase(it, input.end());

    return input;
}

int main() {
    try {
        vector<int> input;

        cout << "Enter Original List: ";

        string inputString;
        getline(cin, inputString);

        istringstream inputStream(inputString);

        int number;
        // Считываем числа из потока и добавляем в вектор
        while (inputStream >> number) {
            input.push_back(number);
        }

        removeDuplicates(input);

        cout << "List without Duplicates:";
        for (int i : input) {
            cout << " " << i;
        }
        cout << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
