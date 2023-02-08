#include <gtest/gtest.h>
#include <set>
#include "s21_set.h"

TEST(constructor, isdefault) {
    std::set<int> a;
    s21::set<int> b;
    EXPECT_EQ(*a.begin(), *b.begin());
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.empty(), b.empty());
}

TEST(constructor, copy) {
    s21::set<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(112);
    a.insert(-5);
    a.insert(4);
    a.insert(17);
    a.insert(4);
    s21::set<int> b(a);
    EXPECT_EQ(*a.begin(), *b.begin());
    EXPECT_EQ(a.size(), b.size());
}

TEST(constructor, move) {
    s21::set<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(112);
    a.insert(-5);
    a.insert(4);
    a.insert(17);
    a.insert(4);
    s21::set<int> b(std::move(a));
    EXPECT_EQ(-5, *b.begin());
    EXPECT_EQ(7, b.size());
    s21::set<int> c;
    s21::set<int> d(std::move(c));
    std::set<int> e;
    std::set<int> f(std::move(e));
    EXPECT_EQ(f.size(), d.size());
    EXPECT_EQ(*d.begin(), *f.begin());
    EXPECT_EQ(f.empty(), d.empty());
}

TEST(method, maxsize) {
    s21::set<int> a;
    std::set<int> b;
    EXPECT_EQ(a.max_size(), b.max_size());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}