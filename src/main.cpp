/*
** EPITECH PROJECT, 2023
** RTypeServer
** File description:
** main
*/

#define ASIO_STANDALONE

#include <asio.hpp>
#include <iostream>

#define UNUSED(x) (void)(x)

namespace ip = asio::ip;

std::string getAddress() {
    asio::io_service ioService;
    ip::tcp::resolver resolver(ioService);

    return resolver.resolve(ip::host_name(), "")->endpoint().address().to_string();
}

int main(int ac, char **av) {
    UNUSED(ac);
    UNUSED(av);
    int a = add(5, 6);
    std::cout << "Hello World!" << std::endl;
    std::cout << "My IP is: " << getAddress() << std::endl;
}
