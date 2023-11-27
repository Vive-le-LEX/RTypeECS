/*
** EPITECH PROJECT, 2023
** RTypeServer
** File description:
** Types
*/

#ifndef TYPES_HPP_
#define TYPES_HPP_

#include <array>
#include <bitset>
#include <iostream>
#include <stdint.h>

class AComponent;
class Entity;

using ComponentID = int64_t;

constexpr std::size_t maxComponents = 128;

using ComponentBitSet = std::bitset<64>;
using ComponentArray = std::array<AComponent*, maxComponents>;

#endif /* !TYPES_HPP_ */
