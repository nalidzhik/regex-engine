/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Nazife Alidzhik
* @idnumber 62598
* @compiler VC
*
* <file with all unit tests>
*
*/

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

TEST(TestMatch, DotMatch)
{
	std::string regex, input;

	regex = "a.c";
	input = "abc";
	EXPECT_TRUE(match(regex, input));

	regex = "b.a";
	input = "abba";
	EXPECT_TRUE(match(regex, input));

	regex = ".e";
	input = "abcedfg";
	EXPECT_TRUE(match(regex, input));

	regex = ".ba";
	input = "baab";
	EXPECT_FALSE(match(regex, input));

	regex = "a.c.";
	input = "abc";
	EXPECT_FALSE(match(regex, input));

	regex = "...b";
	input = "baab";
	EXPECT_TRUE(match(regex, input));
}

TEST(TestMatch, StarMatch)
{
	std::string regex, input;

	regex = "a*";
	input = "aaaaaaaaa";
	EXPECT_TRUE(match(regex, input));

	regex = "e*";
	input = "abba";
	EXPECT_TRUE(match(regex, input));

	regex = "a*";
	input = "bbbbbbbb";
	EXPECT_TRUE(match(regex, input));

	regex = "b*a";
	input = "aaaaaaa";
	EXPECT_TRUE(match(regex, input));

	regex = "a*c";
	input = "abc";
	EXPECT_TRUE(match(regex, input));

	regex = "aaa*c";
	input = "abc";
	EXPECT_FALSE(match(regex, input));
}

TEST(TestMatch, PlusMatch)
{
	std::string regex, input;

	regex = "a+";
	input = "aaaaaaaaa";
	EXPECT_TRUE(match(regex, input));

	regex = "a+b";
	input = "aaaaab";
	EXPECT_TRUE(match(regex, input));

	regex = "c+d+e";
	input = "ccde";
	EXPECT_TRUE(match(regex, input));

	regex = "c+d+e";
	input = "ccdae";
	EXPECT_FALSE(match(regex, input));

	regex = "a+";
	input = "bbbbbb";
	EXPECT_FALSE(match(regex, input));
}

TEST(TestMatch, QuestionMatch)
{
	std::string regex, input;

	regex = "c?ba";
	input = "cba";
	EXPECT_TRUE(match(regex, input));

	regex = "c?ba";
	input = "bba";
	EXPECT_TRUE(match(regex, input));

	regex = "c?dae?aljaj";
	input = "daaljaj";
	EXPECT_TRUE(match(regex, input));

	regex = "aaaa?bba?";
	input = "aabb";
	EXPECT_FALSE(match(regex, input));

	regex = "a?b?c?d?";
	input = "e";
	EXPECT_TRUE(match(regex, input));
}

TEST(TestMatch, CombinationMatch)
{
	std::string regex, input;

	regex = "^a?dcs.why";
	input = "adcswwhy";
	EXPECT_TRUE(match(regex, input));

	regex = "^hello?sesi*q";
	input = "hellosesiiq";
	EXPECT_TRUE(match(regex, input));

	regex = "a?aaa?bcdef.";
	input = "aaaabcdeff";
	EXPECT_TRUE(match(regex, input));

	regex = "a?aaa?bcdef.";
	input = "aaaabcdef";
	EXPECT_FALSE(match(regex, input));
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
