#include "pch.h"
#include "../regex-engine/regex-engine.h"
#include "../regex-engine/regex-engine.cpp"

TEST(TestMatch, SimpleLiteralMatch)
{
    std::string regex, input;

    regex = "abc";
    input = "abc";
    EXPECT_TRUE(match(regex, input));

    regex = "abcd";
    input = "abc";
    EXPECT_FALSE(match(regex, input));

    regex = "abc";
    input = "Hello abc!";
    EXPECT_TRUE(match(regex, input));

    regex = "abc";
    input = "Hello azc!";
    EXPECT_FALSE(match(regex, input));

    regex = "abc";
    input = "Hello abc";
    EXPECT_TRUE(match(regex, input));
}

TEST(TestMatch, StartMatch)
{
    std::string regex, input;

    regex = "^abc";
    input = "aabc";
    EXPECT_FALSE(match(regex, input));

    regex = "^abc";
    input = "abc";
    EXPECT_TRUE(match(regex, input));

    regex = "^abc";
    input = "abcedfg";
    EXPECT_TRUE(match(regex, input));

    regex = "^abc";
    input = "baab";
    EXPECT_FALSE(match(regex, input));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
