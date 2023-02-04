#include <gtest/gtest.h>
#include "s21_tree.h"
#include "iostream"

/**
 * FIXME:
 * 0) деструктор
 * 1) копирование
 * 2) конструкторы
 */

TEST(method, insert) {
    s21::BinaryTree<int> a;

    a.insert(100);
    a.insert(200);
    a.insert(300);
    a.insert(400);
    a.insert(500);
    a.insert(50);
    a.insert(70);
    a.insert(131);
    a.insert(134);
    a.insert(149);

    for (s21::BinaryTree<int>::iterator it = a.begin(); it != a.end(); it++) {
        std::cout << *it << '\n';
    }
 std::cout << "++++++++++++++++++++++++++" << '\n';
    auto it1 = a.begin();

    for (; *it1 != 200; it1++) {}
    a.erase(it1);

    for (s21::BinaryTree<int>::iterator it = a.begin(); it != a.end(); it++) {
        std::cout << *it << '\n';
    }
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}