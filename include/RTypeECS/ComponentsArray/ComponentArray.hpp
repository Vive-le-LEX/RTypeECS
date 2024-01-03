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
#include <set>
#include <iostream>
#include <functional>

#include "IComponentArray.hpp"

template<typename T>
class ComponentArray : public IComponentArray {
public:

    ComponentArray(const RemoveComponentFunction<T> &delFunc) : deleteFunction(
            delFunc) {}

    void insert(const Entity entity, const T component) {
        assert(entityToIndexMap.find(entity) == entityToIndexMap.end() &&
               "Component added to same entity more than once.");

        size_t newIndex = totalSize;
        entityToIndexMap[entity] = newIndex;
        indexToEntityMap[newIndex].insert(entity);
        componentArray[newIndex] = component;
        ++totalSize;
    }

    void remove(const Entity entity) {
        assert(entityToIndexMap.find(entity) != entityToIndexMap.end() &&
               "Removing non-existent component.");

        size_t indexToRemove = entityToIndexMap[entity];
        size_t indexOfLastElement = totalSize - 1;

        if (indexToEntityMap[indexToRemove].size() == 1) {
            auto &component = componentArray[indexToRemove];
            if (deleteFunction.has_value())
                deleteFunction.value()(component);
            componentArray[indexToRemove] = componentArray[indexOfLastElement];
            auto lastEntities = indexToEntityMap[indexOfLastElement];
            for (auto const &en: lastEntities) {
                entityToIndexMap[en] = indexToRemove;
            }
            indexToEntityMap[indexToRemove] = lastEntities;
            indexToEntityMap.erase(indexOfLastElement);
            entityToIndexMap.erase(entity);
            --totalSize;
            std::cout << "At exit we got : " << std::endl;
            for (auto const &[index, en]: entityToIndexMap) {
                std::cout << "\tindex: " << index << std::endl;
            }
        } else {
            indexToEntityMap[indexToRemove].erase(entity);
            entityToIndexMap.erase(entity);

        }
    }

    void copy(const Entity src, const Entity dst) {
        assert(entityToIndexMap.find(src) != entityToIndexMap.end() &&
               "Copying non-existent component.");
        assert(entityToIndexMap.find(dst) == entityToIndexMap.end() &&
               "Copying to an already existing component.");

        size_t indexToCopy = entityToIndexMap[src];
        entityToIndexMap[dst] = indexToCopy;
        indexToEntityMap[indexToCopy].insert(dst);
    }

    T &getComponent(const Entity entity) {
        assert(entityToIndexMap.find(entity) != entityToIndexMap.end() &&
               "Retrieving non-existent component.");

        return componentArray[entityToIndexMap[entity]];
    }

    void safeRemove(const Entity &entity) noexcept final {
            std::cout << "Safe remove of comp : " << typeid(T).name() << std::endl;
            for (auto const &[index, en]: entityToIndexMap) {
                std::cout << "\tRemove index: " << index << std::endl;
            }
            if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
                std::cout << "\tFind it so going to remove it " << std::endl;
                remove(entity);
            }
    }

private:
    std::array<T, MAX_ENTITIES> componentArray;
    std::unordered_map<Entity, size_t> entityToIndexMap;
    std::unordered_map<size_t, std::set<Entity>> indexToEntityMap;
    RemoveComponentFunction<T> deleteFunction;
    size_t totalSize = 0;
};
