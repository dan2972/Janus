#ifndef JANUS_TILEMAP_RENDER_SYSTEM_HPP
#define JANUS_TILEMAP_RENDER_SYSTEM_HPP

#include <raylib.h>
#include <queue>
#include "render_system.hpp"
#include "world.hpp"
#include "tilemap.hpp"
#include "tile_data.hpp"
#include "renderer/chunk_renderer.hpp"

namespace Janus {
    class TilemapRenderSystem : public RenderSystem{
    public:
        using RenderSystem::RenderSystem;
        ~TilemapRenderSystem() override { ChunkRenderer::unload(); }
        void render(float d) override {
            auto view = world->getEntitiesWith<PlayerComponent>();
            for (auto entity : view) {
                auto& actor = world->getComponentFromEntity<ActorComponent>(entity);
                renderTilemap(static_cast<int>(actor.chunkPos.x), static_cast<int>(actor.chunkPos.y), CHUNK_RENDER_DISTANCE);
            }
        }
    private:
        void renderTilemap(int centerX, int centerY, int radius) {
            for (int i = centerY - radius; i <= centerY + radius; ++i) {
                for (int j = centerX - radius; j <= centerX + radius; ++j) {
                    Chunk* chunk = world->getTilemap().getChunkAt(j, i);
                    if (chunk != nullptr) {
                        if (!chunk->updateTextureRequested())
                            ChunkRenderer::drawChunk(world->getTilemap(), *chunk, world->getCamera());
                        else if (!chunk->isWaitingForTextureUpdate()) {
                            chunk->waitForTextureUpdate();
                            if (chunk->textureUpdateIsHighPriority())
                                highPriorityChunkRenderQueue.push(std::ref(*chunk));
                            else
                                chunkRenderQueue.push(std::ref(*chunk));
                        }
                    }
                }
            }

            int counter = MAX_CHUNK_TEXTURE_LOAD_PER_RENDER_UPDATE;
            while (!highPriorityChunkRenderQueue.empty() && counter > 0) {
                ChunkRenderer::drawChunk(world->getTilemap(), highPriorityChunkRenderQueue.front(), world->getCamera());
                highPriorityChunkRenderQueue.pop();
                --counter;
            }
            while (!chunkRenderQueue.empty() && counter > 0) {
                ChunkRenderer::drawChunk(world->getTilemap(), chunkRenderQueue.front(), world->getCamera());
                chunkRenderQueue.pop();
                --counter;
            }
        }

        std::queue<std::reference_wrapper<Chunk>> chunkRenderQueue;
        std::queue<std::reference_wrapper<Chunk>> highPriorityChunkRenderQueue;
    };
}

#endif //JANUS_TILEMAP_RENDER_SYSTEM_HPP
