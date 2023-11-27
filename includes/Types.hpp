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

class Component;
class Entity;

using ComponentID = int64_t;

constexpr std::size_t maxComponents = 128;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;


#endif /* !TYPES_HPP_ */
