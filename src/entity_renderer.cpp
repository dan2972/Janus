#include "entity_renderer.hpp"
#include "chunk.hpp"
#include "actor.hpp"
#include "ground_tile.hpp"
#include "player.hpp"
#include "chunk_renderer.hpp"

namespace Janus {
    void EntityRenderer::renderActors(const std::vector<std::unique_ptr<GameObject>>& actorList, float dt) {
        raylib::Texture* texture;
        for (auto& obj : actorList) {
            auto actor = (Actor*)obj.get();
            glm::vec2 renderPos = glm::mix(actor->getLastPos(), actor->getPos(), dt);
            switch (actor->getActorType()) {
                case Actor::ActorType::PLAYER:
                    texture = TextureManager::GetTexture("resources/slime.png");
                    if (actor->getActorType() == Actor::PLAYER) {
                        auto* player = (Player*) actor;
                        if (player->isInWater()) {
                            DrawRectangle(renderPos.x - 2, renderPos.y+actor->getSize().y/2 - 4,
                                          actor->getSize().x + 4, 10, SKYBLUE);
                            DrawTexturePro(*texture, raylib::Rectangle({0,0}, {(float)texture->width, (float)texture->height / 2}),
                                           raylib::Rectangle({renderPos.x, renderPos.y}, {actor->getSize().x, actor->getSize().y / 2}),
                                           {0, 0}, 0, WHITE);
                        } else {
                            DrawTexturePro(*texture, raylib::Rectangle({0,0}, {(float)texture->width, (float)texture->height}),
                                           raylib::Rectangle({renderPos.x, renderPos.y}, {actor->getSize().x, actor->getSize().y}),
                                           {0, 0}, 0, WHITE);
                        }
                    }
                    break;
                case Actor::ActorType::DRONE:
                    DrawRectangle(renderPos.x, renderPos.y, actor->getSize().x, actor->getSize().y, {200, 255, 200, 255});
                    break;
                case Actor::ActorType::NONE:
                    DrawRectangle(renderPos.x, renderPos.y, actor->getSize().x, actor->getSize().y, {200, 255, 200, 255});
                    break;
            }
        }
    }

    void EntityRenderer::preloadTilemapTextures(GameCamera& camera, int centerX, int centerY, int radius) {
        for (int i = centerY - radius; i <= centerY + radius; ++i) {
            for (int j = centerX - radius; j <= centerX + radius; ++j) {
                Chunk* chunk = tilemap->getChunk(j, i);
                if (chunk != nullptr) {
                    ChunkRenderer::loadChunk(*tilemap, *chunk, camera);
                }
            }
        }
    }

    void EntityRenderer::renderTilemap(GameCamera& camera, int centerX, int centerY, int radius, float dt) {
        for (int i = centerY - radius; i <= centerY + radius; ++i) {
            for (int j = centerX - radius; j <= centerX + radius; ++j) {
                Chunk* chunk = tilemap->getChunk(j, i);
                if (chunk != nullptr) {
                    if (!chunk->updateTextureRequested())
                        ChunkRenderer::drawChunk(*tilemap, *chunk, camera);
                    else if (!chunk->isWaitingForTextureUpdate()){
                        chunk->waitForTextureUpdate();
                        chunkRenderQueue.push(std::ref(*chunk));
                    }
                }
            }
        }
        int counter = MAX_CHUNK_TEXTURE_LOAD_PER_TICK;
        while (!chunkRenderQueue.empty() && counter > 0) {
            ChunkRenderer::drawChunk(*tilemap, chunkRenderQueue.front().get(), camera);
            chunkRenderQueue.pop();
            counter--;
        }
    }

    void EntityRenderer::renderProjectiles() {

    }

    void EntityRenderer::renderParticles() {

    }
}