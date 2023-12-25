#include <iostream>
#include <vector>
using namespace std;

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

vector<int> generateFactorials(int n) {
    vector<int> factorials;

    if (n < 0) {
        throw invalid_argument("Input should be a non-negative integer");
    }

    for (int i = 0; i <= n; ++i) {
        factorials.push_back(factorial(i));
    }

    return factorials;
}

int main() {
    try {
        int n;
        cout << "Enter a non-negative integer n: ";
        cin >> n;

        vector<int> result = generateFactorials(n);

        cout << "Factorials:";
        for (int i : result) {
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
