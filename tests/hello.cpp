/*
** EPITECH PROJECT, 2023
** RTypeECS
** File description:
** hello
*/

#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

TEST(add, test1)
{
    EXPECT_EQ(add(1, 1), 2);
}
