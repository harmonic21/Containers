#include <iostream>
#include <gtest/gtest.h>

#include "s21_tree.h"

TEST(constructor, copy) {
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
    s21::BinaryTree<int> b(a);
    s21::BinaryTree<int> c = b;

    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(*a.begin(), *b.begin());
    auto it1 = b.begin();
    for (auto it = a.begin(); it != a.end(); it++) {
        EXPECT_EQ(*it, *it1);
        it1++;
    }
    auto it2 = a.begin();
    for (auto it = c.begin(); it != c.end(); it++) {
        EXPECT_EQ(*it, *it2);
        it2++;
    }
}

TEST(constructor, copy2) {
    s21::BinaryTree<int> a;
    a.insert_unique(1);
    a.insert_unique(1);
    a.insert_unique(1);
    a.insert_unique(1);
    a.insert_unique(1);
    a.insert_unique(1);
    a.insert_not_unique(1);
    s21::BinaryTree<int> b(a);
    EXPECT_EQ(*a.begin(), *b.begin());
    EXPECT_EQ(a.size(), b.size());

    auto it1 = b.begin();
    for (auto it = a.begin(); it != a.end(); it++) {
        EXPECT_EQ(*it, *it1);
        it1++;
    }
    s21::BinaryTree<int> c = b;
    auto it2 = a.begin();
    for (auto it = c.begin(); it != c.end(); it++) {
        EXPECT_EQ(*it, *it2);
        it2++;
    }
}

TEST(method, move_constructor) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(1);
    a.insert_not_unique(1);
    a.insert_not_unique(1);
    s21::BinaryTree<int> b(std::move(a));
}

TEST(method, begin) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(1);
    a.insert_not_unique(1);
    a.insert_not_unique(1);
    s21::BinaryTree<int> b(std::move(a));
    EXPECT_EQ(1, *b.begin());
    EXPECT_EQ(3, b.size());
    b.erase(b.begin());
    b.insert_not_unique(2);
    EXPECT_EQ(*b.begin(), 1);
}

TEST(method, begin2) {
    s21::BinaryTree<int> a;
    a.insert_unique(123);
    a.insert_unique(14);
    a.insert_unique(15);
    EXPECT_EQ(*a.begin(), 14);
    auto it = a.begin();
    a.erase(it++);
    for(; *it != 15; it++) {}
    a.erase(it);
    EXPECT_EQ(*a.begin(), 123);
}

TEST(method, empty) {
    s21::BinaryTree<int> a;
    EXPECT_EQ(a.empty(), true);
    a.insert_unique(123);
    a.insert_unique(14);
    EXPECT_EQ(a.empty(), false);
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.empty(), true);
}

TEST(method, empty2) {
    s21::BinaryTree<int> a;
    s21::BinaryTree<int> b(std::move(a));
    EXPECT_EQ(b.empty(), true);
    b.insert_unique(123);
    b.insert_unique(14);
    EXPECT_EQ(b.empty(), false);
}

TEST(method, clear) {
    s21::BinaryTree<int> a;
    a.insert_unique(1);
    a.insert_unique(1);
    a.insert_unique(1);
    a.insert_unique(1);
    a.insert_unique(1);
    a.insert_unique(1);
    a.clear();
    EXPECT_EQ(a.size(), 0);
    s21::BinaryTree<int> b;
    b.clear();
    EXPECT_EQ(b.size(), 0);
}

TEST(method, clear2) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(1);
    a.insert_not_unique(2);
    a.insert_not_unique(3);
    a.insert_not_unique(4);
    a.insert_not_unique(1);
    a.insert_not_unique(2);
    EXPECT_EQ(a.size(), 6);
    a.clear();
    EXPECT_EQ(a.size(), 0);
    a.insert_not_unique(1);
    a.insert_not_unique(2);
    EXPECT_EQ(a.size(), 2);
}

TEST(method, merge) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(1);
    a.insert_not_unique(2);

    s21::BinaryTree<int> b;
    b.insert_not_unique(1);
    b.insert_not_unique(2);

    s21::BinaryTree<int> c;
    c.insert_not_unique(1);
    c.insert_not_unique(2);
    c.insert_not_unique(1);
    c.insert_not_unique(2);

    a.merge(b);

    auto it2 = a.begin();
    for (auto it = c.begin(); it != c.end(); it++) {
        EXPECT_EQ(*it, *it2);
        it2++;
    }
}

TEST(method, merge1) {
    s21::BinaryTree<int> a;
    s21::BinaryTree<int> b(a);
    a.merge(b);
    EXPECT_EQ(a.size(), b.size());
}

TEST(method, merge2) {
    s21::BinaryTree<int> a;
    s21::BinaryTree<int> b;
    a.merge(b);
    EXPECT_EQ(a.size(), b.size());
}

TEST(method, merge3) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(1);
    a.insert_not_unique(2);

    s21::BinaryTree<int> b;
    b.insert_not_unique(1);
    b.insert_not_unique(2);

    s21::BinaryTree<int> c;
    c.insert_not_unique(1);
    c.insert_not_unique(2);

    a.unique_merge(b);
    auto it2 = a.begin();
    for (auto it = c.begin(); it != c.end(); it++) {
        EXPECT_EQ(*it, *it2);
        it2++;
    }
    s21::BinaryTree<int> d;
    s21::BinaryTree<int> e;
    d.unique_merge(e);
    EXPECT_EQ(d.size(), 0);
    EXPECT_EQ(e.size(), 0);
}

TEST(method, merge4) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(1);
    a.insert_not_unique(2);
    a.insert_not_unique(3);
    a.insert_not_unique(4);
    a.insert_not_unique(1);
    a.insert_not_unique(2);

    s21::BinaryTree<int> c;
    a.insert_not_unique(1);
    a.insert_not_unique(2);
    a.insert_not_unique(3);
    a.insert_not_unique(4);
    a.insert_not_unique(1);
    a.insert_not_unique(1);
    a.insert_not_unique(2);
    a.insert_not_unique(3);
    a.insert_not_unique(4);
    a.insert_not_unique(1);
    a.insert_not_unique(2);
    s21::BinaryTree<int> b(a);
    b.merge(a);

    auto it2 = b.begin();
    for (auto it = c.begin(); it != c.end(); it++) {
        EXPECT_EQ(*it, *it2);
        it2++;
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}