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

#include "RTypeECS/Types.hpp"

#include "RTypeECS/Managers/SystemManager.hpp"
#include "RTypeECS/Managers/EntityManager.hpp"
#include "RTypeECS/Managers/ComponentManager.hpp"
#include "RTypeECS/Singleton.hpp"

#include <iostream>
#include <memory>
#include <functional>

class Coordinator {
public:
    Coordinator() {
        entityManager = std::make_unique<EntityManager>();
        componentManager = std::make_unique<ComponentManager>();
        systemManager = std::make_unique<SystemManager>();
    };

    Entity createEntity() {
        return entityManager->createEntity();
    }

    void destroyEntity(const Entity &entity) {
        entityManager->destroyEntity(entity);

        systemManager->destroyEntity(entity);

        componentManager->destroyEntity(entity);
    }

    template<typename T>
    void registerComponent(std::function<void(T &)> deleteFunction) {
        componentManager->registerComponent<T>(deleteFunction);
    }

    template<typename T>
    void addComponent(const Entity &entity, const T &component) {
        componentManager->addComponent<T>(entity, component);

        updateSignature<T>(entity, 1);
    }

    template<typename T>
    void removeComponent(const Entity &entity) {
        componentManager->removeComponent<T>(entity);

        updateSignature<T>(entity, 0);
    }

    template<typename T>
    void copyComponent(const Entity &src, const Entity &dst) {
        componentManager->copyComponent<T>(src, dst);

        updateSignature<T>(dst, 1);
    }

    template<typename T>
    T& getComponent(const Entity &entity) {
        return componentManager->getComponent<T>(entity);
    }

    template<typename T>
    ComponentType getComponentType() {
        return componentManager->getComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> registerSystem() {
        return systemManager->registerSystem<T>();
    }

    template<typename T>
    void setSystemSignature(const Signature &signature) {
        systemManager->setSignature<T>(signature);
    }
private:
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<SystemManager> systemManager;
    std::unique_ptr<ComponentManager> componentManager;

    template<typename T>
    inline void updateSignature(const Entity &entity, bool value) {
        auto signature = entityManager->getSignature(entity);
        signature.set(componentManager->getComponentType<T>(), value);
        entityManager->setSignature(entity, signature);

        systemManager->entitySignatureChanged(entity, signature);
    }
};
