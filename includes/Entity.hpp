/*
** EPITECH PROJECT, 2023
** RTypeServer
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <memory>
#include <vector>
#include "Component.hpp"

class Entity {
    public:

        void setActive(const bool &active) { _isActive = active; }
        const bool &isActive(void) const { return _isActive; }

        void update(void) {
            for (auto &component : components)
                component->update();
        }

        void destroy(void) {
            _isActive = false;
        }

        template <typename T>
        bool hasComponent() const {
            return componentBitSet[getComponentTypeID<T>()];
        }

        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&... args) {
            T* component(new T(std::forward<TArgs>(args)...));
            component->entity = this;
            std::unique_ptr<AComponent> uPtr{component};
            components.emplace_back(std::move(uPtr));

            componentArray[getComponentTypeID<T>()] = component;
            componentBitSet[getComponentTypeID<T>()] = true;

            component->init();
            return *component;
        }

        template <typename T>
        T& getComponent(void) const {
            auto ptr(componentArray[getComponentTypeID<T>()])
            return *static_cast<T*>(ptr);
        }

    private:
        bool _isActive = true;
        std::vector<std::unique_ptr<AComponent>> components;

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;
};

#endif /* !ENTITY_HPP_ */
