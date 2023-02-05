#include <gtest/gtest.h>
#include "s21_tree.h"
#include "iostream"

/**
 * FIXME:
 * 1) копирование
 * 2) конструкторы
 */

TEST(method, insert) {
    s21::BinaryTree<int> a;

    a.insert_unique(100);
    a.insert_unique(200);
    a.insert_unique(300);
    a.insert_unique(400);
    a.insert_unique(500);
    a.insert_unique(50);
    a.insert_unique(70);
    a.insert_unique(131);
    a.insert_unique(134);
    a.insert_unique(149);
    a.insert_unique(149);

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
    a.clear();

}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}