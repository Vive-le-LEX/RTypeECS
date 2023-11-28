/*
** EPITECH PROJECT, 2023
** RTypeServer
** File description:
** main
*/

#define ASIO_STANDALONE

#include <asio.hpp>
#include <iostream>

#include "ECSManager.hpp"
#include "PositionComponent.hpp"

namespace ip = asio::ip;

std::string getAddress() {
    asio::io_service ioService;
    ip::tcp::resolver resolver(ioService);

    return resolver.resolve(ip::host_name(), "")->endpoint().address().to_string();
}

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
    std::cout << "My IP is: " << getAddress() << std::endl;
}
