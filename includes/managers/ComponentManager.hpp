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

#include <cassert>
#include <typeinfo>
#include <unordered_map>

#include "../components/ComponentArray.hpp"
#include "../components/IComponentArray.hpp"
#include "Types.hpp"

namespace EpiCS::Managers {
    class ComponentManager {
    public:
        template<typename T>
        void registerComponent() {
            std::size_t hashCode = typeid(T).hash_code();
            assert(componentTypes.find(hashCode) == componentTypes.end() && "Registering component type more than once.");

            componentTypes[hashCode] = nextComponentType;
            componentArrays[hashCode] = new Components::ComponentArray<T>();
            ++nextComponentType;
        }

        template<typename T>
        const ComponentType &getComponentType() {
            std::size_t hashCode = typeid(T).hash_code();
            assert(componentTypes.find(hashCode) != componentTypes.end() && "Component not registered before use.");

            return componentTypes[hashCode];
        }

        template<typename T>
        void addComponent(const Entity &entity, const T &component) {
            getComponentArray<T>()->insert(entity, component);
        }

        template<typename T>
        void removeComponent(const Entity &entity) {
            getComponentArray<T>()->remove(entity);
        }

        template<typename T>
        T &getComponent(const Entity &entity) {
            return getComponentArray<T>()->getComponent(entity);
        }

        void entityDestroyed(const Entity &entity) {
            for (auto const &[_, component]: componentArrays) {
                component->safeRemove(entity);
            }
        }

    private:
        std::unordered_map<std::size_t, ComponentType> componentTypes;
        ComponentType nextComponentType{};
        std::unordered_map<std::size_t, Components::IComponentArray *> componentArrays;

        template<typename T>
        Components::ComponentArray<T> *getComponentArray() {
            std::size_t hashCode = typeid(T).hash_code();
            assert(componentTypes.find(hashCode) != componentTypes.end() && "Component not registered before use.");

            return static_cast<Components::ComponentArray<T> *>(componentArrays[hashCode]);
        }
    };
}// namespace EpiCS::Managers

#include "Types.hpp"
