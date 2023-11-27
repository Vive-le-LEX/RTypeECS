/*
** EPITECH PROJECT, 2023
** RTypeServer
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "Types.hpp"

inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

class IComponent {
    public:
        virtual void init() = 0;
        virtual void update() = 0;
};

class AComponent : public IComponent {
    public:
        Entity *entity;
};

#endif /* !COMPONENT_HPP_ */
