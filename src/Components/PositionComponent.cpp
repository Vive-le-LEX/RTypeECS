/*
** EPITECH PROJECT, 2023
** RTypeServer
** File description:
** PositionComponent
*/

#include "PositionComponent.hpp"

PositionComponent::PositionComponent()
{
}

PositionComponent::~PositionComponent()
{
}

void PositionComponent::init()
{
    x = 0;
    y = 0;
}

void PositionComponent::update()
{
}

void PositionComponent::setX(int x)
{
    this->x = x;
}

void PositionComponent::setY(int y)
{
    this->y = y;
}

int PositionComponent::getX() const
{
    return x;
}

int PositionComponent::getY() const
{
    return y;
}
