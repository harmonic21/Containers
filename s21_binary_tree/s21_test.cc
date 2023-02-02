#include <gtest/gtest.h>
#include "s21_tree.h"
#include "iostream"

/**
 * FIXME:
 * 0) деструктор
 * 1) Балансировку в инсерт
 * 2) эрейс
 * 3) файнд
 * 4) копирование
 *
 */

TEST(method, insert) {
    s21::BinaryTree<int> a;

    a.insert(2);
    a.insert(2);
    a.insert(2);
    a.insert(1);
    a.insert(3);
    a.insert(4);
    a.insert(-150);

    for (s21::BinaryTree<int>::iterator it = a.begin(); it != a.end(); it++) {
        std::cout << *it << '\n';
    }

}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}