/*
** EPITECH PROJECT, 2023
** RTypeServer
** File description:
** main
*/

#include <iostream>
#include "ECSManager.hpp"
#include "PositionComponent.hpp"

int main(int ac, char **av) {
    (void)ac;
    (void)av;
    ECSManager manager;

    auto &e = manager.addEntity();

    e.addComponent<PositionComponent>();
    e.getComponent<PositionComponent>().setX(10);
    e.getComponent<PositionComponent>().setY(20);

    std::cout << e.getComponent<PositionComponent>().getX() << std::endl;

    std::cout << "Hello World!" << std::endl;
}
