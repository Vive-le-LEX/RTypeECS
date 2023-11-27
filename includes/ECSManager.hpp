/*
** EPITECH PROJECT, 2023
** RTypeServer
** File description:
** ECSManager
*/

#ifndef ECSMANAGER_HPP_
#define ECSMANAGER_HPP_

#include "Entity.hpp"
#include <algorithm>

class ECSManager {
    public:
        void clean() {
            entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                [](const std::unique_ptr<Entity> &currentEntity) {
                    return !currentEntity->isActive();
                }
            ), std::end(entities));
        }

        Entity &addEntity() {
            Entity* e = new Entity();
            std::unique_ptr<Entity> uniquePtr{e};
            entities.emplace_back(std::move(e));
            return *e;
        }

    private:
        std::vector<std::unique_ptr<Entity>> entities;
};

#endif /* !ECSMANAGER_HPP_ */
