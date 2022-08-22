#ifndef JANUS_PLAYER_TICK_SYSTEM_HPP
#define JANUS_PLAYER_TICK_SYSTEM_HPP

#include "tick_system.hpp"
#include "components/components.hpp"
#include "world.hpp"
#include "global_values.hpp"
#include "input_manager.hpp"

namespace Janus{
    class PlayerTickSystem : public TickSystem {
    public:
        using TickSystem::TickSystem;
        void tick() override {
            auto view = world->getEntitiesWith<PlayerComponent>();
            for (auto entity : view) {
                auto [m, actor] = world->getComponentsFromEntity<MovementControllerComponent, ActorComponent>(entity);

                world->getTilemap().loadChunks((int)actor.chunkPos.x, (int)actor.chunkPos.y, CHUNK_LOAD_DISTANCE);

                float speed = 10;

                if (InputManager::PlayerUse()) {
                    auto [tileX, tileY] = TileMathHelper::screenCoordToTileCoordInt(GetMouseX(), GetMouseY(), world->getCamera());
                    world->getTilemap().replaceObjectTileAt(tileX, tileY, ObjectTileID::STONE);
                }else if (InputManager::PlayerAttack()) {
                    auto [tileX, tileY] = TileMathHelper::screenCoordToTileCoordInt(GetMouseX(), GetMouseY(), world->getCamera());
                    world->getTilemap().replaceObjectTileAt(tileX, tileY, ObjectTileID::AIR);
                }

                if (m.movingUp) {
                    actor.velocity.y = -speed;
                } else if (m.movingDown) {
                    actor.velocity.y = speed;
                } else {
                    actor.velocity.y = 0;
                }

                if (m.movingLeft) {
                    actor.velocity.x = -speed;
                } else if (m.movingRight) {
                    actor.velocity.x = speed;
                } else {
                    actor.velocity.x = 0;
                }
            }
        }
    };
}

#endif //JANUS_PLAYER_TICK_SYSTEM_HPP
