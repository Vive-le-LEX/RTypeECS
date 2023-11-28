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
            for (size_t i = 0; i < maxComponents; i++) {
                if (componentBitSet[i])
                    componentArray[i]->update();
            }
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

            ComponentID id = getComponentTypeID<T>();
            componentArray[id] = component;
            componentBitSet[id] = true;

            component->init();
            return *component;
        }

        template <typename T>
        T& getComponent(void) const {
            auto ptr(componentArray[getComponentTypeID<T>()]);
            return *static_cast<T*>(ptr);
        }

    private:
        bool _isActive = true;

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;
};

#endif /* !ENTITY_HPP_ */
