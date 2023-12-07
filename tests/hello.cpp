/*
** EPITECH PROJECT, 2023
** RTypeECS
** File description:
** hello
*/

#include <gtest/gtest.h>
#include "RTypeECS/Types.hpp"

Entity addEntity(Entity a, Entity b)
{
    return a + b;
}

TEST(addEntity, test1)
{
    EXPECT_EQ(addEntity(898, 2), 900);
}
