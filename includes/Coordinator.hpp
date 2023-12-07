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

#include "Types.hpp"

#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "Singleton.hpp"

class Coordinator : public Singleton<Coordinator> {
public:
    Coordinator() {
        entityManager = new EntityManager();
        componentManager = new ComponentManager();
        systemManager = new SystemManager();
    };

    ~Coordinator() {
        delete entityManager;
        delete componentManager;
        delete systemManager;
    }

    Entity createEntity() {
        return entityManager->createEntity();
    }

    void destroyEntity(Entity entity) {
        entityManager->destroyEntity(entity);

        systemManager->destroyEntity(entity);

        componentManager->destroyEntity(entity);
    }

    template<typename T>
    void registerComponent() {
        componentManager->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity entity, T component) {
        componentManager->addComponent<T>(entity, component);

        auto signature = entityManager->getSignature(entity);
        signature.set(componentManager->getComponentType<T>(), true);
        entityManager->setSignature(entity, signature);

        systemManager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    void removeComponent(Entity entity) {
        componentManager->removeComponent<T>(entity);

        auto signature = entityManager->getSignature(entity);
        signature.set(componentManager->getComponentType<T>(), false);
        entityManager->setSignature(entity, signature);

        systemManager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& getComponent(Entity entity) {
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
    void setSystemSignature(Signature signature) {
        systemManager->setSignature<T>(signature);
    }
private:
    EntityManager *entityManager;
    SystemManager *systemManager;
    ComponentManager *componentManager;
};
