// koloc1.cpp : Коллок Семенченко С++
//1.  На вход натуральное число n. На выход контейнер с первыми n факториалами.

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

// Функция для генерации факториалов от 0 до n включительно
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


//
//#include <gtest/gtest.h>
//
//// Включаем функции из вашего кода
//#include "your_factorial_code.h"
//
//// Тест для функции factorial
//TEST(FactorialTest, HandlesZeroAndOne) {
//    EXPECT_EQ(factorial(0), 1);
//    EXPECT_EQ(factorial(1), 1);
//}
//
//TEST(FactorialTest, HandlesPositiveNumbers) {
//    EXPECT_EQ(factorial(2), 2);
//    EXPECT_EQ(factorial(3), 6);
//    EXPECT_EQ(factorial(4), 24);
//    // Добавьте дополнительные тестовые случаи при необходимости
//}
//
//// Тест для функции generateFactorials
//TEST(GenerateFactorialsTest, HandlesZeroAndOne) {
//    EXPECT_EQ(generateFactorials(0), std::vector<int>{1});
//    EXPECT_EQ(generateFactorials(1), std::vector<int>{1, 1});
//}
//
//TEST(GenerateFactorialsTest, HandlesPositiveNumbers) {
//    EXPECT_EQ(generateFactorials(2), std::vector<int>{1, 1, 2});
//    EXPECT_EQ(generateFactorials(3), std::vector<int>{1, 1, 2, 6});
//    // Добавьте дополнительные тестовые случаи при необходимости
//}
//
//TEST(GenerateFactorialsTest, HandlesNegativeInput) {
//    // Тест на обработку исключительной ситуации
//    EXPECT_THROW(generateFactorials(-1), std::invalid_argument);
//}
//
//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}