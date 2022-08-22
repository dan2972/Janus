#ifndef JANUS_ENTITY_HPP
#define JANUS_ENTITY_HPP

#include <entt/entt.hpp>
#include "world.hpp"

namespace Janus {
    class Entity{
    public:
        Entity() = default;
        Entity(entt::entity entity, World* world) : entity{entity}, world{world} {}
        Entity(const Entity& other) = default;

        template<typename T, typename... Args>
        T& addComponent(Args&&... args){
            assert(!hasComponent<T>());
            return world->registry.emplace<T>(entity, std::forward<Args>(args)...);
        }

        template<typename T>
        T& getComponent(){
            assert(hasComponent<T>());
            return world->registry.get<T>(entity);
        }

        template<typename T>
        bool hasComponent(){
            return world->registry.all_of<T>(entity);
        }

        template<typename T>
        void removeComponent(){
            assert(hasComponent<T>());
            world->registry.remove<T>(entity);
        }

        explicit operator bool() const { return entity != entt::null; }
        explicit operator entt::entity() const { return entity; }
        explicit operator uint32_t() const { return (uint32_t)entity; }
    private:
        entt::entity entity{ entt::null };
        World* world = nullptr;
    };
}

#endif //JANUS_ENTITY_HPP
