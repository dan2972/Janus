#include "entity_renderer.hpp"
#include "chunk.hpp"
#include "actor.hpp"
#include "ground_tile.hpp"
#include "player.hpp"

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
                            DrawRectangle(renderPos.x - 2, renderPos.y+actor->getSize().y/2,
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
                    for (auto& tile : chunk->getMap()) {
                        drawTile(*tile);
                    }
                }
            }
        }
    }

    void EntityRenderer::drawTile(Tile &tile) {
        if (tile.getTileType() == Tile::TileType::GROUND) {
            auto& gt = (GroundTile&) tile;
            if (gt.getGroundTileType() == GroundTile::GRASS)
                DrawRectangle(gt.getPos().x, gt.getPos().y, gt.TILE_SIZE, gt.TILE_SIZE, {120,170,100,255});
            else if (gt.getGroundTileType() == GroundTile::WATER)
                DrawRectangle(gt.getPos().x, gt.getPos().y, gt.TILE_SIZE, gt.TILE_SIZE, {80,150,205,255});
            else if (gt.getGroundTileType() == GroundTile::SAND)
                DrawRectangle(gt.getPos().x, gt.getPos().y, gt.TILE_SIZE, gt.TILE_SIZE, {195,185,120,255});
            else if (gt.getGroundTileType() == GroundTile::STONE)
                DrawRectangle(gt.getPos().x, gt.getPos().y, gt.TILE_SIZE, gt.TILE_SIZE, GRAY);
        } else if (tile.getTileType() == Tile::TileType::OBJECT) {
            DrawRectangle(tile.getPos().x, tile.getPos().y, tile.TILE_SIZE, tile.TILE_SIZE, DARKGRAY);
        }
    }

    void EntityRenderer::renderProjectiles() {

    }

    void EntityRenderer::renderParticles() {

    }
}