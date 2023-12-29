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

#include <memory>

#include "RTypeECS/Types.hpp"
#include "RTypeECS/Systems/System.hpp"
#include "RTypeECS/Managers/ComponentManager.hpp"

class SystemManager {
    public:
        template<typename T>
        std::shared_ptr<T> registerSystem() {
            std::size_t hashCode = typeid(T).hash_code();
            assert(systems.find(hashCode) == systems.end() && "Registering system type more than once.");

            auto system = std::make_shared<T>();
            systems.insert({hashCode, system});
            return system;
        }

        template<typename T>
        void setSignature(const Signature &signature) {
            std::size_t hashCode = typeid(T).hash_code();
            assert(systems.find(hashCode) != systems.end() && "System used before registered.");

            signatures.insert({hashCode, signature});
        }

        void destroyEntity(const Entity &entity) {
            for (auto const& pair : systems) {
                auto const& system = pair.second;

                system->entities.erase(entity);
            }
        }

        void entitySignatureChanged(const Entity &entity, const Signature &entitySignature) {
            for (auto const& pair : systems) {
                auto const& type = pair.first;
                auto const& system = pair.second;
                auto const& systemSignature = signatures[type];

                if ((entitySignature & systemSignature) == systemSignature) {
                    system->entities.insert(entity);
                } else {
                    system->entities.erase(entity);
                }
            }
        }

        template<typename T>
        T &getSystem() {
            std::size_t hashCode = typeid(T).hash_code();
            assert(systems.find(hashCode) != systems.end() && "System used before registered.");

            return *std::static_pointer_cast<T>(systems[hashCode]);
        }

    private:
        std::unordered_map<std::size_t, Signature> signatures = {};

        std::unordered_map<std::size_t, std::shared_ptr<System>> systems = {};
};
