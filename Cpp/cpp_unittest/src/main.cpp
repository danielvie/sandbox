#include <iostream>
#include <gtest/gtest.h>

int add(int a, int b) {
    return a + b;
}

TEST(AddTest, Positive) {
    EXPECT_EQ(3, add(2, 1));
}

TEST(AddTest, Negative) {
    EXPECT_EQ(-3, add(-2, -1));
}

TEST(AddTest, Zero) {
    EXPECT_EQ(0, add(0, 0));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
