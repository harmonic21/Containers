#include <iostream>
#include <gtest/gtest.h>
#include <set>

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
    for(; *it != 15; ++it) {}
    a.erase(it);
    EXPECT_EQ(*a.begin(), 123);
}

TEST(method, erase2) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(14);
    a.insert_not_unique(5);
    a.insert_not_unique(20);
    a.insert_not_unique(8);
    a.insert_not_unique(17);
    s21::BinaryTree<int> b;
    b.insert_not_unique(14);
    b.insert_not_unique(5);
    b.insert_not_unique(8);
    a.erase(--a.end());
    a.erase(--a.end());
    s21::BinaryTree<int> c = b;
    auto it2 = a.begin();
    for (auto it = c.begin(); it != c.end(); ++it) {
        EXPECT_EQ(*it, *it2);
        ++it2;
    }
}

TEST(method, erase3) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(14);
    a.insert_not_unique(5);
    a.insert_not_unique(17);
    a.insert_not_unique(20);
    a.insert_not_unique(8);
    a.insert_not_unique(8);
    a.insert_not_unique(8);
    a.insert_not_unique(8);

    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
     EXPECT_EQ(a.size(), 0);
}

TEST(method, erase4) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(1);
    a.insert_not_unique(1);
    a.insert_not_unique(1);
    a.insert_not_unique(1);
    a.insert_not_unique(1);
    a.insert_not_unique(1);
    a.insert_not_unique(1);
    a.insert_not_unique(1);

    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    EXPECT_EQ(a.size(), 0);
}

TEST(method, erase5) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(0);
    a.insert_not_unique(1234);
    a.insert_not_unique(17);
    a.insert_not_unique(9);
    a.insert_not_unique(45);
    a.insert_not_unique(78);
    a.insert_not_unique(12);
    a.insert_not_unique(0);
    a.insert_not_unique(0);
    a.insert_not_unique(145);

    a.insert_not_unique(600);
    a.insert_not_unique(14);
    a.insert_not_unique(18);
    a.insert_not_unique(20);
    a.insert_not_unique(1032);
    a.insert_not_unique(104);
    a.insert_not_unique(99);
    a.insert_not_unique(33);
    a.insert_not_unique(12);
    a.insert_not_unique(76);

    a.insert_not_unique(600);
    a.insert_not_unique(14);
    a.insert_not_unique(18);
    a.insert_not_unique(20);
    a.insert_not_unique(1032);
    a.insert_not_unique(104);
    a.insert_not_unique(99);
    a.insert_not_unique(33);
    a.insert_not_unique(12);
    a.insert_not_unique(76);

    a.insert_not_unique(600);
    a.insert_not_unique(14);
    a.insert_not_unique(18);
    a.insert_not_unique(20);
    a.insert_not_unique(1032);
    a.insert_not_unique(104);
    a.insert_not_unique(99);
    a.insert_not_unique(33);
    a.insert_not_unique(12);
    a.insert_not_unique(76);

    a.insert_not_unique(43);
    a.insert_not_unique(111);
    a.insert_not_unique(97);
    a.insert_not_unique(15);
    a.insert_not_unique(0);

    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());

    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());

    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());

    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());

    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());
    EXPECT_EQ(a.size(), 0);
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

TEST(method, erase) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(1);
    a.insert_not_unique(2);
    a.insert_not_unique(3);
    a.insert_not_unique(4);
    a.insert_not_unique(1);
    a.insert_not_unique(2);
    s21::BinaryTree<int>b;
    b = a;
    s21::BinaryTree<int>c;
    c.insert_not_unique(1);
    c.insert_not_unique(2);
    c.insert_not_unique(3);
    c.insert_not_unique(1);
    c.insert_not_unique(2);
    auto it = b.begin();
    for(; *it != 4; it++) {}
    b.erase(it);
    EXPECT_EQ(b.size(), 5);
    auto it2 = b.begin();
    for (auto it3 = c.begin(); it3 != c.end(); it3++) {
        EXPECT_EQ(*it3, *it2);
        it2++;
    }
}

TEST(method, max_size) {
    s21::BinaryTree<int> a;
    std::set<int> b;
    EXPECT_EQ(a.max_size(), b.max_size());
}

TEST(method, iterator) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(7);
    a.insert_not_unique(10);
    a.insert_not_unique(2);
    a.insert_not_unique(5);
    a.insert_not_unique(8);
    a.insert_not_unique(17);
    a.insert_not_unique(11);
    a.insert_not_unique(11);
    s21::BinaryTree<int> b(a);
    auto it1 = a.cend();
    auto it2 = b.cend();
    it1--;
    it2--;
    --it1;
    --it2;
    EXPECT_EQ(*it1, 11);
    EXPECT_EQ(11, *it2);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 11);
    EXPECT_EQ(*it2, 11);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 10);
    EXPECT_EQ(*it2, 10);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 8);
    EXPECT_EQ(8, *it2);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 7);
    EXPECT_EQ(7, *it2);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 5);
    EXPECT_EQ(5, *it2);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 2);
    EXPECT_EQ(2, *it2);
    EXPECT_EQ(*it1, *it2);
    EXPECT_EQ((it1 == it1), true);
    it1++;
    it2++;
    EXPECT_EQ(*it1, 5);
    EXPECT_EQ(5, *it2);
    EXPECT_EQ(*it1, *it2);
}

TEST(method, iterator2) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(7);
    a.insert_not_unique(10);
    a.insert_not_unique(2);
    a.insert_not_unique(5);
    a.insert_not_unique(8);
    a.insert_not_unique(17);
    a.insert_not_unique(11);
    a.insert_not_unique(11);
    s21::BinaryTree<int> b(a);
    auto it1 = a.end();
    auto it2 = b.end();
    it1--;
    it2--;
    --it1;
    --it2;
    EXPECT_EQ(*it1, 11);
    EXPECT_EQ(11, *it2);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 11);
    EXPECT_EQ(*it2, 11);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 10);
    EXPECT_EQ(*it2, 10);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 8);
    EXPECT_EQ(8, *it2);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 7);
    EXPECT_EQ(7, *it2);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 5);
    EXPECT_EQ(5, *it2);
    EXPECT_EQ(*it1, *it2);
    --it1;
    --it2;
    EXPECT_EQ(*it1, 2);
    EXPECT_EQ(2, *it2);
    EXPECT_EQ(*it1, *it2);
    EXPECT_EQ((it1 == it1), true);
    it1++;
    it2++;
    EXPECT_EQ(*it1, 5);
    EXPECT_EQ(5, *it2);
    EXPECT_EQ(*it1, *it2);
}

TEST(method, upper_bound) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(7);
    a.insert_not_unique(10);
    a.insert_not_unique(2);
    a.insert_not_unique(5);
    a.insert_not_unique(8);
    a.insert_not_unique(17);
    a.insert_not_unique(11);
    a.insert_not_unique(11);
    EXPECT_EQ(*a.upper_bound(1), 2);
    a.insert_not_unique(1);
    EXPECT_EQ(*a.upper_bound(1), 2);
    a.clear();
    EXPECT_EQ(*a.upper_bound(2), 0);
}

TEST(method, lower_bound) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(7);
    a.insert_not_unique(10);
    a.insert_not_unique(2);
    a.insert_not_unique(5);
    a.insert_not_unique(8);
    a.insert_not_unique(17);
    a.insert_not_unique(11);
    a.insert_not_unique(11);
    EXPECT_EQ(*a.lower_bound(1), 2);
    a.insert_not_unique(1);
    EXPECT_EQ(*a.lower_bound(1), 1);
    a.clear();
    EXPECT_EQ(*a.lower_bound(2), 0);
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

TEST(method, merge5) {
    s21::BinaryTree<int> a;
    a.insert_unique(1);
    a.insert_unique(2);
    a.insert_unique(3);
    a.insert_unique(4);

    s21::BinaryTree<int> c;
    a.insert_unique(1);
    a.insert_unique(2);
    a.insert_unique(3);
    a.insert_unique(4);
    a.insert_unique(1);
    a.insert_unique(1);
    a.insert_unique(2);
    a.insert_unique(3);
    a.insert_unique(4);
    a.insert_unique(1);
    a.insert_unique(2);
    s21::BinaryTree<int> b(a);
    b.merge(a);

    auto it2 = b.begin();
    for (auto it = c.begin(); it != c.end(); ++it) {
        EXPECT_EQ(*it, *it2);
        ++it2;
    }
}

TEST(method, merge6) {
    s21::BinaryTree<int> a;
    a.insert_not_unique(1);
    a.insert_not_unique(2);
    a.insert_not_unique(3);
    a.insert_not_unique(4);
    a.insert_not_unique(1);
    a.insert_not_unique(2);

    s21::BinaryTree<int> c;
    c.insert_not_unique(1);
    c.insert_not_unique(2);
    c.insert_not_unique(3);
    c.insert_not_unique(4);
    c.insert_not_unique(5);
    c.insert_not_unique(6);
    c.insert_not_unique(7);
    c.insert_not_unique(8);
    c.insert_not_unique(9);
    c.insert_not_unique(10);
    c.insert_not_unique(11);

    s21::BinaryTree<int> b(c);
    auto it0 = b.begin();
    for (auto it = c.begin(); it != c.end(); ++it) {
        EXPECT_EQ(*it, *it0);
        ++it0;
    }
    b.insert_not_unique(1);
    b.insert_not_unique(2);

    a.unique_merge(c);
    auto it1 = a.begin();
    for (auto it = b.begin(); it != b.end(); ++it) {
        EXPECT_EQ(*it, *it1);
        ++it1;
    }

    s21::BinaryTree<int> c2;
    c2.insert_not_unique(1);
    c2.insert_not_unique(2);
    c2.insert_not_unique(3);
    c2.insert_not_unique(4);

    s21::BinaryTree<int> d(c);
    auto it2 = d.begin();
    for (auto it = c2.begin(); it != c2.end(); ++it) {
        EXPECT_EQ(*it, *it2);
        ++it2;
    }
}

TEST(method, emplase) {
    s21::BinaryTree<int> a;
    s21::BinaryTree<int> b;
    b.insert_not_unique(1);
    b.insert_not_unique(3);
    b.insert_not_unique(5);
    a.emplace(1);
    a.emplace(3);
    a.emplace(5);
    auto it2 = b.begin();
    for (auto it = a.begin(); it != a.end(); it++) {
        EXPECT_EQ(*it, *it2);
        it2++;
    }
}

TEST(method, emplase_uniq) {
    s21::BinaryTree<int> a;
    s21::BinaryTree<int> b;
    b.insert_unique(1);
    b.insert_unique(1);
    b.insert_unique(1);
    b.insert_unique(3);
    b.insert_unique(3);
    b.insert_unique(3);
    b.insert_unique(5);
    b.insert_unique(5);
    b.insert_unique(5);
    a.emplace_uniq(1);
    a.emplace_uniq(1);
    a.emplace_uniq(1);
    a.emplace_uniq(3);
    a.emplace_uniq(3);
    a.emplace_uniq(3);
    a.emplace_uniq(5);
    a.emplace_uniq(5);
    a.emplace_uniq(5);
    auto it2 = b.begin();
    for (auto it = a.begin(); it != a.end(); it++) {
        EXPECT_EQ(*it, *it2);
        it2++;
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}