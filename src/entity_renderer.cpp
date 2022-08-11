#include "entity_renderer.hpp"
#include "chunk.hpp"
#include "actor.hpp"

namespace Janus {
    void EntityRenderer::renderActors(const std::vector<GameObject*>& actorList, float dt) {
        raylib::Texture* texture;
        for (auto& obj : actorList) {
            auto* actor = (Actor*)obj;
            glm::vec2 renderPos = glm::mix(actor->getLastPos(), actor->getPos(), dt);
            switch (actor->getActorType()) {
                case Actor::ActorType::PLAYER:
                    texture = TextureManager::GetTexture("resources/slime.png");
                    DrawTexturePro(*texture, raylib::Rectangle({0,0}, {(float)texture->width, (float)texture->height}),
                                   raylib::Rectangle({renderPos.x, renderPos.y}, {actor->getSize().x, actor->getSize().y}),
                                   {0, 0}, 0, WHITE);
                    break;
                case Actor::ActorType::NONE:
                    DrawRectangle(actor->getPos().x, actor->getPos().y, actor->getSize().x, actor->getSize().y, {200, 255, 200, 255});
                    break;
            }
        }
    }

    void EntityRenderer::renderTilemap(int centerX, int centerY, int radius, float dt) {
        for (int i = centerY - radius; i <= centerY + radius; ++i) {
            for (int j = centerX - radius; j <= centerX + radius; ++j) {
                Chunk* chunk = tilemap->getChunk(j, i);
                if (chunk != nullptr) {
                    for (auto tile : chunk->getMap()) {
                        switch (tile->getTileType()) {
                            case Tile::TileType::GROUND:
                                DrawRectangle(tile->getPos().x, tile->getPos().y, tile->TILE_SIZE, tile->TILE_SIZE, GRAY);
                                break;
                            case Tile::TileType::OBJECT:
                                DrawRectangle(tile->getPos().x, tile->getPos().y, tile->TILE_SIZE, tile->TILE_SIZE, DARKGRAY);
                                break;
                            default:
                                DrawRectangle(tile->getPos().x, tile->getPos().y, tile->TILE_SIZE, tile->TILE_SIZE, WHITE);
                                break;
                        }
                    }
                }
            }
        }
    }

    void EntityRenderer::renderProjectiles() {

    }

    void EntityRenderer::renderParticles() {

    }
}