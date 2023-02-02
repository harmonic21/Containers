#include <gtest/gtest.h>
#include <set>

TEST(method, test) {
    std::set<int> s;
    std::cout << *s.begin() << '\n';
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}