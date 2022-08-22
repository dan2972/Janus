#ifndef JANUS_WORLD_HPP
#define JANUS_WORLD_HPP

#include <entt/entity/registry.hpp>
#include "tilemap.hpp"
#include "systems/render_system.hpp"
#include "systems/tick_system.hpp"
#include "systems/startup_system.hpp"
#include "game_camera.hpp"

namespace Janus {
    class World{
    public:
        explicit World(GameCamera* camera);

        template<class T>
        void registerStartupSystem() {
            startupSystems.push_back(std::unique_ptr<StartupSystem>(new T(this)));
        }

        template<class T>
        void registerRenderSystem() {
            renderSystems.push_back(std::unique_ptr<RenderSystem>(new T(this)));
        }

        template<class T>
        void registerTickSystem() {
            tickSystems.push_back(std::unique_ptr<TickSystem>(new T(this)));
        }

        template<class T, typename... Args>
        T spawnEntity(Args&&... args) {
            T entity{registry.create(), this, std::forward<Args>(args)...};
            return entity;
        }

        template<typename... Components>
        auto getEntitiesWith() {
            return registry.view<Components...>();
        }

        template<typename Component>
        Component& getComponentFromEntity(entt::entity entity) {
            return registry.get<Component>(entity);
        }

        template<typename... Components>
        auto getComponentsFromEntity(entt::entity entity) {
            return registry.get<Components...>(entity);
        }

        void initialize();

        void tick();
        void render(float dt);

        void destroyEntity(entt::entity entity);

        Tilemap& getTilemap() { return tilemap; }

        GameCamera& getCamera() { return *camera; }

    private:
        entt::registry registry;
        Tilemap tilemap;

        GameCamera* camera = nullptr;

        std::vector<std::unique_ptr<StartupSystem>> startupSystems;
        std::vector<std::unique_ptr<RenderSystem>> renderSystems;
        std::vector<std::unique_ptr<TickSystem>> tickSystems;

        friend class Entity;
    };
}

#endif //JANUS_WORLD_HPP
