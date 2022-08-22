#ifndef JANUS_TILEMAP_TICK_SYSTEM_HPP
#define JANUS_TILEMAP_TICK_SYSTEM_HPP

#include <raylib.h>
#include "tilemap.hpp"
#include "tick_system.hpp"
#include "world.hpp"

namespace Janus {
    class TilemapTickSystem : public TickSystem{
    public:
        using TickSystem::TickSystem;
        void tick() override {
            auto view = world->getEntitiesWith<PlayerComponent>();
            for (auto entity : view) {
                auto& actor = world->getComponentFromEntity<ActorComponent>(entity);
                tickTilemap(static_cast<int>(actor.chunkPos.x), static_cast<int>(actor.chunkPos.y), CHUNK_TICK_RADIUS);
            }
        }
    private:
        void tickTilemap(int centerX, int centerY, int radius) {
            for (int i = centerY - radius; i <= centerY + radius; ++i) {
                for (int j = centerX - radius; j <= centerX + radius; ++j) {
                    Chunk* chunk = world->getTilemap().getChunkAt(j, i);
                    if (chunk != nullptr) {
                        tickChunk(*chunk);
                    }
                }
            }
        }

        void tickChunk(Chunk& chunk) {
            for (unsigned int i = 0; i < Chunk::CHUNK_SIZE; ++i) {
                for (unsigned int j = 0; j < Chunk::CHUNK_SIZE; ++j) {
                    ObjectTile& ot = chunk.getObjectTileAt(j, i);
                    tickObjectTile(ot);
                }
            }
        }

        void tickObjectTile(ObjectTile& ot) {
            switch (ot.id) {
                case ObjectTileID::AIR:
                    break;
                default:
                    break;
            }
        }
    };
}

#endif //JANUS_TILEMAP_TICK_SYSTEM_HPP
