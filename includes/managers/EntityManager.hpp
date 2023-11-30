/*
 * Copyright (c) 2023 - Kleo
 * Authors:
 * - LEO VILTARD <leo.viltard@epitech.eu>
 * NOTICE: All information contained herein is, and remains
 * the property of Kleo © and its suppliers, if any.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Kleo ©.
*/

#pragma once

#include <array>
#include <cassert>
#include <cinttypes>
#include <queue>

#include "Types.hpp"

namespace EpiCS::Managers {

    class EntityManager {
    public:
        EntityManager() : entityCount(0) {
            for (Entity e = 0; e < MAX_ENTITIES; ++e) {
                availableEntities.push(e);
            }
        };

        const Entity &CreateEntity() {
            assert(entityCount < MAX_ENTITIES && "Too many entities have been loaded.");

            Entity &newId = availableEntities.front();
            availableEntities.pop();
            ++entityCount;

            return newId;
        }

        void DestroyEntity(const Entity &entity) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            signatures[entity].reset();

            availableEntities.push(entity);
            --entityCount;
        }

        void SetSignature(const Entity &entity, const Signature &signature) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            signatures[entity] = signature;
        }

        const Signature &getSignature(const Entity &entity) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            return signatures[entity];
        }

        ~EntityManager() = default;

    private:
        std::queue<Entity> availableEntities{};
        Entity entityCount;
        std::array<Signature, MAX_ENTITIES> signatures{};

    };

}// namespace EpiCS::Managers
