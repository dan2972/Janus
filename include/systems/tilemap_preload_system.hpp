#ifndef JANUS_TILEMAP_PRELOAD_SYSTEM_HPP
#define JANUS_TILEMAP_PRELOAD_SYSTEM_HPP

#include "startup_system.hpp"
#include "global_values.hpp"
#include "chunk.hpp"
#include "world.hpp"
#include "renderer/chunk_renderer.hpp"

namespace Janus {
    class TilemapPreloadSystem : public StartupSystem{
    public:
        using StartupSystem::StartupSystem;
        void run() override {
            int radius = CHUNK_PRELOAD_DISTANCE;

            world->getTilemap().loadChunks(0, 0, radius+1);

            for (int i = -radius; i <= radius; ++i) {
                for (int j = -radius; j <= radius; ++j) {
                    Chunk* chunk = world->getTilemap().getChunkAt(j, i);
                    if (chunk != nullptr) {
                        ChunkRenderer::loadChunk(world->getTilemap(), *chunk, world->getCamera());
                    }
                }
            }
        }
    };
}

#endif //JANUS_TILEMAP_PRELOAD_SYSTEM_HPP
