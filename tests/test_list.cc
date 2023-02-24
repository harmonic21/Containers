#include <gtest/gtest.h>
#include <list>
#include "s21_list.h"

TEST(constructor, def) {
    s21::list<int> a{1, 2, 3, 4, 5, 6};
    s21::list<int> b(a);
    EXPECT_EQ((a.begin() == a.begin()), true);
    EXPECT_EQ((a.begin() != a.end()), true);
    EXPECT_EQ((b.cbegin() == b.cbegin()), true);
    EXPECT_EQ((b.cend() != b.cbegin()), true);
    s21::list<int> c(std::move(b));
    EXPECT_EQ((c.cbegin() == c.cend()), false);
    EXPECT_EQ((a.cbegin() != a.cend()), true);
    EXPECT_EQ(*(a.cbegin()++), 1);
    auto  it = --a.cend();
    EXPECT_EQ(*(a.cend()--), 0);
    EXPECT_EQ(*it, 6);
}

TEST(constructor, const2) {
    s21::list<int> a(10);
    std::list<int> b(10);
    EXPECT_EQ(a.empty(), b.empty());
    EXPECT_EQ(a.size(), b.size());
    s21::list<int> l1(0);
    std::list<int> l2(0);
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.size(), l2.size());
    l1 = a;
    l2 = b;
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.size(), l2.size());
}

TEST(method, clear_1) {
    std::list<int> l1{12, 21, 3, 4, 5, 1};
    s21::list<int> l2{12, 21, 3, 4, 5, 1};
    EXPECT_EQ(l2.empty(), false);
    EXPECT_EQ(l2.size(), 6);
    EXPECT_EQ(l2.size(), l1.size());
    EXPECT_EQ(l2.max_size(), l1.max_size());
    l1.clear();
    l2.clear();
    EXPECT_EQ(l2.size(), l1.size());
    EXPECT_EQ(l1.empty(), l2.empty());
    l1.insert(l1.cbegin(), 5);
    l2.insert(l2.cbegin(), 5);
    EXPECT_EQ(*l1.begin(), *l2.begin());
}

TEST(method, clear_2) {
    s21::list<int> l1{};
    std::list<int> l2{};
    EXPECT_EQ(l1.empty(), true);
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.size(), l2.size());
    l1.clear();
    l2.clear();
    EXPECT_EQ(*l1.begin(), 0);
    EXPECT_EQ(*l1.end(), 0);
    EXPECT_ANY_THROW(l1.front());
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.size(), l2.size());
    l1.push_back(2);
    l2.push_back(2);
    EXPECT_EQ(*l1.begin(), *l2.begin());
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.size(), l2.size());
    l1.clear();
    l2.clear();
    EXPECT_EQ(*l1.begin(), 0);
    EXPECT_ANY_THROW(l1.front());
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.size(), l2.size());
}

TEST(method, clear_3) {
    std::list<int> l1;
    s21::list<int> l2;
    EXPECT_EQ(l1.empty(), true);
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.size(), l2.size());
    l1.clear();
    l2.clear();
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.size(), l2.size());
    l1.push_front(5);
    l2.push_front(5);
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.size(), l2.size());
}

TEST(method, insert) {
    std::list<int> l1;
    s21::list<int> l2;
    l1.insert(l1.cbegin(), 7);
    l2.insert(l2.cbegin(), 7);
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.front(), l2.front());
    l1.push_front(2);
    l2.push_front(2);
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_EQ(l1.front(), l2.front());
    l1.insert(l1.begin(), 7);
    l2.insert(l2.begin(), 7);
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_EQ(l1.front(), l2.front());
    l1.insert(l1.end(), 7);
    l2.insert(l2.end(), 7);
    auto i2 = l2.begin();
    for(int &i : l1) {
        EXPECT_EQ(i, *i2);
        i2++;
    }
}

TEST(method, insert_1) {
    std::list<int> l1;
    s21::list<int> l2;
    l1.insert(l1.cend(), 7);
    l2.insert(l2.cend(), 7);
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.front(), l2.front());
    EXPECT_EQ(l1.back(), l2.back());
    l1.clear();
    l2.clear();
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_ANY_THROW(l2.back());
    l1.insert(l1.end(), 7);
    l2.insert(l2.end(), 7);
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_EQ(l1.empty(), l2.empty());
    EXPECT_EQ(l1.front(), l2.front());
    EXPECT_EQ(l1.back(), l2.back());
}

TEST(method, insert_2) {
    std::list<std::string> l1;
    s21::list<std::string> l2;
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_EQ(l1.empty(), l2.empty());
    l1.insert(l1.cbegin(), "hi");
    l2.insert(l2.cbegin(), "hi");
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_EQ(l1.front(), l2.front());
    EXPECT_EQ(l1.back(), l2.back());
    l1.insert(l1.cbegin(), "");
    l2.insert(l2.cbegin(), "");
    l1.insert(l1.cbegin(), "ddddddddddddddddddhi");
    l2.insert(l2.cbegin(), "ddddddddddddddddddhi");
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_EQ(l1.front(), l2.front());
    EXPECT_EQ(l1.back(), l2.back());
}

TEST(method, insert_3) {
    std::list<int> l1{1, 2, 3, 4, 5, 6, 7};
    s21::list<int> l2{1, 2, 3, 4, 5, 6, 7};
    auto it1 = ++(l1.begin());
    s21::list<int>::iterator it2 = ++(l2.begin());
    it1++;
    ++it2;
    l1.insert(it1, 200);
    l2.insert(it2, 200);
    s21::list<int>::iterator j = l2.begin();
    for (auto i : l1) {
        EXPECT_EQ(*j, i);
        ++j;
    }
}

TEST(method, erase_1) {
    std::list<std::string> l1{"hi", "so"};
    s21::list<std::string> l2{"hi", "so"};
    l1.erase(l1.cbegin());
    l2.erase(l2.cbegin());
    EXPECT_EQ(*l1.begin(), *l2.begin());
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_EQ(l1.front(), l2.front());
    EXPECT_EQ(l1.back(), l2.back());
    l1.erase(l1.begin());
    l2.erase(l2.begin());
    EXPECT_EQ(l1.size(), l2.size());
    EXPECT_ANY_THROW(l2.front());
    EXPECT_ANY_THROW(l2.back());
}

TEST(method, erase_2) {
    s21::list<int> a;
    std::list<s21::list<int>> l1{a, a, a, a, a};
    s21::list<s21::list<int>> l2{a, a, a, a, a};
    EXPECT_EQ(l1.size(), l2.size());
    l1.erase(l1.cbegin());
    l2.erase(l2.cbegin());
    l1.erase(l1.cbegin());
    l2.erase(l2.cbegin());
    EXPECT_EQ(l1.size(), l2.size());
}

TEST(method, push_back) {
    s21::list<int> l1;
    s21::list<int> l2(l1);
    std::list<int> test{2, 5, 6, 7, 8, 1, 0, 3};
    EXPECT_EQ(0, l2.size());
    l1.push_back(2);
    l1.push_back(5);
    l1.push_back(6);
    l1.push_back(7);
    l1.push_back(8);
    l1.push_back(1);
    l1.push_back(0);
    l1.push_back(3);
    s21::list<int>::iterator j = l1.begin();
    for (auto i : test) {
        EXPECT_EQ(*j, i);
        ++j;
    }
}

TEST(method, pop_back){
    s21::list<int> l1;
    s21::list<int> l2{2, 5, 6, 7, 9, 0, 1, 66};
    std::list<int> test{2, 5, 6, 7, 9};
    EXPECT_EQ(*l2.begin(), *test.begin());
    EXPECT_ANY_THROW(l1.pop_back());
    EXPECT_EQ(0, l1.size());
    l2.pop_back();
    l2.pop_back();
    l2.pop_back();
    s21::list<int>::iterator j = l2.begin();
    for (auto i : test) {
        EXPECT_EQ(*j, i);
        ++j;
    }
    s21::list<int>::const_iterator j1 = ++(l2.cbegin());
    auto j2 = ++(test.cbegin());
    EXPECT_EQ(*j1, *j2);
}

TEST(method, push_front){
    s21::list<int> l1;
    s21::list<int> l2(std::move(l1));
    EXPECT_EQ(0, l2.size());
    l2.push_front(2);
    EXPECT_EQ(1, l2.size());
    EXPECT_EQ(2, l2.front());
    EXPECT_EQ(2, l2.back());
    l2.erase(l2.cbegin());
    EXPECT_EQ(0, l2.size());
    l2.push_front(5);
    EXPECT_EQ(1, l2.size());
    EXPECT_EQ(5, l2.front());
    EXPECT_EQ(5, l2.back());
}

TEST(method, pop_front) {
    s21::list<int> l1{2, 3, 4, 5, 3, 34, 5, 5};
    std::list<int> l2{3, 34, 5, 5};
    l1.pop_front();
    l1.pop_front();
    l1.pop_front();
    l1.pop_front();
    s21::list<int>::iterator j = l1.begin();
    for (auto i : l2) {
        EXPECT_EQ(*j, i);
        ++j;
    }
    l1.pop_front();
    l1.pop_front();
    l1.pop_front();
    l1.pop_front();
    EXPECT_ANY_THROW( l1.pop_front());
    EXPECT_EQ(0, l1.size());
}

TEST(method, emplace_back) {
    s21::list<int> l1;
    std::list<int> l2;
    l1.emplace_back(1);
    l1.emplace_back(2);
    l1.emplace_back(3);

    l2.emplace_back(1);
    l2.emplace_back(2);
    l2.emplace_back(3);
    auto j = l1.begin();
    for (auto i : l2) {
        EXPECT_EQ(*j, i);
        std::cout << *j << " " << i << '\n';
        ++j;
    }
}

TEST(method, emplace_back1) {
    s21::list<int> l1(0);
    std::list<int> l2(0);
    l1.emplace_back(1);
    l1.emplace_back(2);
    l1.emplace_back(3);

    l2.emplace_back(1);
    l2.emplace_back(2);
    l2.emplace_back(3);
    auto j = l1.begin();
    for (auto i : l2) {
        EXPECT_EQ(*j, i);
        std::cout << *j << " " << i << '\n';
        ++j;
    }
}

TEST(method, emplace_back2) {
    s21::list<int> l1{1, 2, 3, 4, 5, 6, 7};
    std::list<int> l2{1, 2, 3, 4, 5, 6, 7};
    l1.emplace_back(1);
    l1.emplace_back(2);
    l1.emplace_back(3);

    l2.emplace_back(1);
    l2.emplace_back(2);
    l2.emplace_back(3);
    auto j = l1.begin();
    for (auto i : l2) {
        EXPECT_EQ(*j, i);
        std::cout << *j << " " << i << '\n';
        ++j;
    }
}

TEST(method, emplace_front) {
    s21::list<int> l1;
    std::list<int> l2;
    l1.emplace_front(1);
    l1.emplace_front(2);
    l1.emplace_front(3);

    l2.emplace_front(1);
    l2.emplace_front(2);
    l2.emplace_front(3);
    auto j = l1.begin();
    for (auto i : l2) {
        EXPECT_EQ(*j, i);
        ++j;
    }
}

TEST(method, emplace_front1) {
    s21::list<int> l1(0);
    std::list<int> l2(0);
    l1.emplace_front(1);
    l1.emplace_front(2);
    l1.emplace_front(3);

    l2.emplace_front(1);
    l2.emplace_front(2);
    l2.emplace_front(3);
    auto j = l1.begin();
    EXPECT_EQ((j == l1.begin()), true);
    for (auto i : l2) {
        EXPECT_EQ(*j, i);
        std::cout << *j << " " << i << '\n';
        ++j;
    }
}

TEST(method, emplace_front2) {
    s21::list<int> l1{1, 2, 3, 4, 5, 6};
    std::list<int> l2{1, 2, 3, 4, 5, 6};
    l1.emplace_front(1);
    l1.emplace_front(2);
    l1.emplace_front(3);

    l2.emplace_front(1);
    l2.emplace_front(2);
    l2.emplace_front(3);
    auto j = l1.begin();
    for (auto i : l2) {
        EXPECT_EQ(*j, i);
        std::cout << *j << " " << i << '\n';
        ++j;
    }
}

TEST(method, swap) {
    s21::list<int> l1;
    s21::list<int> l2;
    s21::list<int> l3{7, 3, 2};
    s21::list<int> l4{9, 4, 5};
    l1.swap(l2);
    EXPECT_EQ(0, l1.size());
    EXPECT_EQ(0, l2.size());
    l1.push_front(2);
    l1.push_front(3);
    l1.push_front(7);
    l2.push_front(5);
    l2.push_front(4);
    l2.push_front(9);
    s21::list<int>::iterator j = l1.begin();
    for (auto i : l3) {
        EXPECT_EQ(*j, i);
        ++j;
    }
    s21::list<int>::iterator j1 = l2.begin();
    for (auto i : l4) {
        EXPECT_EQ(*j1, i);
        ++j1;
    }
}

TEST(method, merge_1) {
    s21::list<int> l1;
    s21::list<int> l2;
    l1.merge(l2);
    EXPECT_EQ(0, l1.size());
    EXPECT_EQ(0, l2.size());
    s21::list<int> l3{1, 2, 3, 5, 6, 7};
    s21::list<int> l4{1, 2, 3, 5, 6, 7};
    std::list<int> test1{1, 2, 3, 5, 6, 7};
    std::list<int> test2{1, 2, 3, 5, 6, 7};
    l3.merge(l4);
    test1.merge(test2);
    s21::list<int>::iterator j = l3.begin();
    for (auto i : test1) {
        EXPECT_EQ(*j, i);
        ++j;
    }
}

TEST(method, merge_2) {
    s21::list<int> l3{0, 0, 0};
    s21::list<int> l4{-1, -1, -1, -1};
    std::list<int> test1{0, 0, 0};
    std::list<int> test2{-1, -1, -1, -1};
    l3.merge(l4);
    test1.merge(test2);
    s21::list<int>::iterator j = l3.begin();
    for (auto i : test1) {
        EXPECT_EQ(*j, i);
        ++j;
    }
}

TEST(method, splice_1) {
    s21::list<int> l1;
    s21::list<int> l2{-1, 1, 2, 3, 5, 7};
    std::list<int> test1;
    std::list<int> test2{-1, 1, 2, 3, 5, 7};
    l1.splice(l1.cbegin(), l2);
    test1.splice(test1.cbegin(), test2);
    s21::list<int>::iterator j = l1.begin();
    for (auto i : test1) {
        EXPECT_EQ(*j, i);
        ++j;
    }
    s21::list<int> l3{-1, 1, 2, 3, 5, 7};
    s21::list<int> l4(l3);
    s21::list<int>::iterator j1 = l3.begin();
    for (auto i = l4.begin(); i != l4.end(); ++i) {
        EXPECT_EQ(*j1, *i);
        ++j1;
    }
}

TEST(method, splice_2) {
    s21::list<int> l1{4, 7, 8, 9, 10};
    s21::list<int> l2{-1, 1, 2, 3, 5, 7};
    std::list<int> test1{4, 7, 8, 9, 10};
    std::list<int> test2{-1, 1, 2, 3, 5, 7};
    l1.splice(l1.cend(), l2);
    test1.splice(test1.cend(), test2);
    s21::list<int>::iterator j = l1.begin();
    for (auto i : test1) {
        EXPECT_EQ(*j, i);
        ++j;
    }
}

TEST(method, reverse_1) {
    s21::list<int> l1{1, 2, 3, 5, 6, 10};
    std::list<int> test1{10, 6, 5, 3, 2, 1};
    l1.reverse();
    s21::list<int>::iterator j = l1.begin();
    for (auto i : test1) {
        EXPECT_EQ(*j, i);
        ++j;
    }
}

TEST(method, reverse_2) {
    s21::list<int> l1;
    std::list<int> test1{7, 5, 3};
    l1.reverse();
    EXPECT_EQ(0, l1.size());
    l1.push_front(3);
    l1.push_front(5);
    l1.push_front(7);
    l1.reverse();
    l1.reverse();
    s21::list<int>::iterator j = l1.begin();
    for (auto i : test1) {
        EXPECT_EQ(*j, i);
        ++j;
    }
}

TEST(method, unique) {
    s21::list<int> l1;
    l1.unique();
    EXPECT_EQ(0, l1.size());
    s21::list<int> l2{1, 1, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 7, 7, 8};
    std::list<int> test1{1, 2, 3, 4, 5, 7, 8};
    l2.unique();
    EXPECT_EQ(7, l2.size());
    s21::list<int>::iterator j = l2.begin();
    for (auto i : test1) {
        EXPECT_EQ(*j, i);
        ++j;
    }
    s21::list<int> l3{0, 0, 0, 0, 0, 0, 0};
    l3.unique();
    EXPECT_EQ(1, l3.size());
    std::list<int> test2{0};
    s21::list<int>::iterator j1 = l3.begin();
    for (auto i : test2) {
        EXPECT_EQ(*j1, i);
        ++j1;
    }
}

TEST(method, sort_1) {
    s21::list<int> l1;
    l1.sort();
    EXPECT_EQ(0, l1.size());
    s21::list<int> l2{1};
    l1.sort();
    EXPECT_EQ(1, l2.size());
    s21::list<int> l3{1, -123, 3, 0, 5, 1};
    std::list<int> test1{-123, 0, 1, 1, 3, 5};
    l3.sort();
    s21::list<int>::iterator j1 = l3.begin();
    for (auto i : test1) {
        EXPECT_EQ(*j1, i);
        ++j1;
    }
}

TEST(method, sort_2) {
    std::list<int> l1{2, 134, 6, -1, 9, 0, 23, 45, 1, -11, 3, 12};
    s21::list<int> l2{2, 134, 6, -1, 9, 0, 23, 45, 1, -11, 3, 12};
    l1.sort();
    l2.sort();
    EXPECT_EQ(*l1.begin(), *l2.begin());
    auto i2 = l2.begin();
    for(int &i : l1) {
        EXPECT_EQ(i, *i2);
        ++i2;
    }
}

TEST(method, sort_3) {
    std::list<int> l1{1, 1, 2, 3};
    s21::list<int> l2{1, 1, 2, 3};
    l1.sort();
    l2.sort();
    EXPECT_EQ(*l1.begin(), *l2.begin());
    l2.push_back(4);
    l1.push_back(4);
    auto i2 = l2.begin();
    for(int i : l1) {
        EXPECT_EQ(i, *i2);
        ++i2;
    }
}

TEST(method, sort_4) {
    s21::list<int> l1;
    std::list<int> l2{1, 1};
    l1.push_back(1);
    l1.push_back(1);
    l1.sort();
    auto i1 = l1.begin();
    for(int i : l2) {
        EXPECT_EQ(i, *i1);
        ++i1;
    }
    l1.push_back(1);
    l1.push_back(1);
    EXPECT_EQ(4, l1.size());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}