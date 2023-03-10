#include <gtest/gtest.h>
#include <set>
#include "s21_set.h"

TEST(constructor, isdefault) {
    std::set<int> a;
    s21::set<int> b;
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

TEST(mathod, clear) {
    s21::set<int> a;
    std::set<int> b;
    a.clear();
    b.clear();
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(*a.begin(), 0);
    a.insert(1);
    a.insert(2);
    b.insert(1);
    b.insert(2);
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(*a.begin(), *b.begin());
    EXPECT_EQ(*a.begin()++, *b.begin()++);
}

TEST(method, erase) {
    s21::set<int> a{1, 2, 3, 4, 5, 6, 7};
    std::set<int> c{1, 2, 3, 4, 5, 6, 7};
    a.erase(a.begin());
    c.erase(c.begin());
    auto it1 = c.begin();
    for(auto it = a.cbegin(); it != a.cend(); it++) {
        EXPECT_EQ(*it, *it1);
        it1++;
    }
}

TEST(method, swap) {
    s21::set<int> a{1, 2, 3, 4, 5, 6, 7};
    s21::set<int> b{3, 2};
    std::set<int> c{1, 2, 3, 4, 5, 6, 7};
    std::set<int> d{3,2};
    a.swap(b);
    c.swap(d);
    auto it1 = a.begin();
    for(auto it = c.begin(); it != c.end(); it++) {
        EXPECT_EQ(*it, *it1);
        it1++;
    }
    auto it2 = b.cbegin();
    for(auto it3 = d.begin(); it3 != d.end(); it3++) {
        EXPECT_EQ(*it2, *it3);
        it2++;
    }
    EXPECT_EQ(a.size(), c.size());
    EXPECT_EQ(b.size(), d.size());
    a = b;
    auto it3 = a.begin();
    for(auto it4 = d.begin(); it4 != d.end(); it4++) {
        EXPECT_EQ(*it4, *it3);
        it3++;
    }
    EXPECT_EQ(a.size(), d.size());
}

TEST(method, merge) {
    s21::set<int> a{1, 2, 3, 4, 5, 6, 7};
    s21::set<int> b{3, 9};
    std::set<int> c{1, 2, 3, 4, 5, 6, 7, 9};
    a.merge(b);
    auto it1 = a.begin();
    for(auto it = c.begin(); it != c.end(); it++) {
        EXPECT_EQ(*it, *it1);
        it1++;
    }
}

TEST(method, find) {
    s21::set<int> a{1, 2, 3, 4, 5, 6, 11, 7, 0};
    std::set<int> c{1, 2, 3, 4, 5, 6, 11, 7, 0};
    EXPECT_EQ(*a.find(7), *c.find(7));
    EXPECT_EQ(*a.find(0), *c.find(0));
    EXPECT_EQ(*a.find(12), *a.end());
    EXPECT_EQ(*a.find(1), *c.find(1));
}

TEST(method, contains) {
    s21::set<int> a{1, 2, 3, 4, 5, 6, 11, 7, 0};
    EXPECT_EQ(a.contains(10), false);
    EXPECT_EQ(a.contains(5), true);
}

TEST(method, contains2) {
    const s21::set<int> a{1, 2, 3, 4, 5, 6, 11, 7, 0};
    EXPECT_EQ(a.contains(10), false);
    EXPECT_EQ(a.contains(5), true);
}

TEST(method, emplace) {
    s21::set<int> a;
    std::set<int> b;
    a.emplace(1);
    a.emplace(1);
    a.emplace(2);
    a.emplace(3);
    a.emplace(4);
    a.emplace(5);

    b.emplace(1);
    b.emplace(1);
    b.emplace(2);
    b.emplace(3);
    b.emplace(4);
    b.emplace(5);
    EXPECT_EQ(a.size(), b.size());
    auto it1 = a.begin();
    for(auto it = b.begin(); it != b.end(); it++) {
        EXPECT_EQ(*it, *it1);
        it1++;
    }
}

TEST(method, emplace1) {
    s21::set<int> a{1, 2, 3, 40, 60};
    std::set<int> b{1, 2, 3, 40, 60};
    a.emplace(1);
    a.emplace(1);
    a.emplace(2);
    a.emplace(3);
    a.emplace(4);
    a.emplace(5);

    b.emplace(1);
    b.emplace(1);
    b.emplace(2);
    b.emplace(3);
    b.emplace(4);
    b.emplace(5);
    EXPECT_EQ(a.size(), b.size());
    auto it1 = a.begin();
    for(auto it = b.begin(); it != b.end(); it++) {
        EXPECT_EQ(*it, *it1);
        it1++;
    }
}

TEST(method, emplace3) {
    s21::set<int> a{1, 2, 3, 40, 60};
    std::set<int> b{1, 2, 3, 40, 60};
    a.emplace(1, 1, 2, 3, 4, 5);

    b.emplace(1);
    b.emplace(1);
    b.emplace(2);
    b.emplace(3);
    b.emplace(4);
    b.emplace(5);
    EXPECT_EQ(a.size(), b.size());
    auto it1 = a.begin();
    for(auto it = b.begin(); it != b.end(); it++) {
        EXPECT_EQ(*it, *it1);
        it1++;
    }
}

TEST(method, emplace4) {
    s21::set<int> a;
    std::set<int> b;
    a.emplace(1, 1, 2, 3, 4, 5);

    b.emplace(1);
    b.emplace(1);
    b.emplace(2);
    b.emplace(3);
    b.emplace(4);
    b.emplace(5);
    EXPECT_EQ(a.size(), b.size());
    auto it1 = a.begin();
    for(auto it = b.begin(); it != b.end(); it++) {
        EXPECT_EQ(*it, *it1);
        it1++;
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}