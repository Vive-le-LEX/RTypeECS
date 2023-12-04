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
#include <unordered_map>

#include "IComponentArray.hpp"

namespace EpiCS::Components {

    template<typename T>
    class ComponentArray : public IComponentArray {
    public:
        void insert(const Entity &entity, const T &component) {
            assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");

            size_t newIndex = totalSize;
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            componentArray[newIndex] = component;
            ++totalSize;
        }

        void remove(const Entity &entity) {
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non-existent component.");

            size_t &indexToRemove = entityToIndexMap[entity];
            size_t indexOfLastElement = totalSize - 1;
            componentArray[indexToRemove] = std::move(componentArray[indexOfLastElement]);

            Entity &lastEntityElement = indexToEntityMap[indexOfLastElement];
            entityToIndexMap[lastEntityElement] = indexToRemove;
            indexToEntityMap[indexToRemove] = lastEntityElement;

            entityToIndexMap.erase(entity);
            indexToEntityMap.erase(indexToRemove);

            --totalSize;
        }

        T &getComponent(const Entity &entity) {
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");

            return componentArray[entityToIndexMap[entity]];
        }

        void safeRemove(const Entity &entity) noexcept final {
            if (entityToIndexMap.find(entity) != entityToIndexMap.end())
                remove(entity);
        }

    private:
        std::array<T, MAX_ENTITIES> componentArray;
        std::unordered_map<Entity, size_t> entityToIndexMap;
        std::unordered_map<size_t, Entity> indexToEntityMap;
        size_t totalSize = 0;
    };
}// namespace EpiCS::Components
