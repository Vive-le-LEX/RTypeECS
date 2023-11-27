/*
** EPITECH PROJECT, 2023
** RTypeServer
** File description:
** PositionComponent
*/

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_

#include "Component.hpp"

class PositionComponent : public AComponent {
    private:
        int x;
        int y;

    public:
        PositionComponent();
        ~PositionComponent();
        void init() final;
        void update() final;
        void setX(int x);
        void setY(int y);
        int getX() const;
        int getY() const;
};

#endif /* !POSITIONCOMPONENT_HPP_ */
