#ifndef JANUS_PLAYER_HPP
#define JANUS_PLAYER_HPP

#include <raylib-cpp.hpp>
#include <glm/glm.hpp>
#include "texture_manager.hpp"
#include "actor.hpp"
#include "tile_math_helper.hpp"
#include "object_tile.hpp"
#include <iostream>

namespace Janus {
    class Player : public Actor {
    public:
        Player(float x, float y, EntityHandler* entityHandler) : Actor(x, y, entityHandler) {
            size.x = 32;
            size.y = 32;

            collisionResponseType = CollisionResponseType::SLIDE;
            collidesWithActors = true;
            collidesWithTiles = true;

            actorType = ActorType::PLAYER;
        }

        void tick() override {
            Actor::tick();
            if (timer >= 2) {
                //entityHandler->remove(this);
            }

            for (int i = (int)chunkPos.y - 1; i <= (int)chunkPos.y + 1; ++i) {
                for (int j = (int)chunkPos.x - 1; j <= (int)chunkPos.x + 1; ++j) {
                    if (!entityHandler->getTileMap().chunkExistsAt((int) j, (int) i)) {
                        entityHandler->getTileMap().addChunk(new Chunk((int) j, (int) i, &entityHandler->getTileMap()));
                    }
                }
            }

            float speed = 6;

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                auto [tileX, tileY] = TileMathHelper::tileCoordToInt(tilePos.x, tilePos.y);
                auto [chunkX, chunkY, posX, posY] = TileMathHelper::tileCoordToChunkAndLocalChunkCoord(tileX, tileY);
                Chunk* chunk = entityHandler->getTileMap().getChunk(chunkX, chunkY);
                if (chunk != nullptr) {
                    if (chunk->getTileAt(posX, posY).getTileType() == Tile::TileType::GROUND) {
                        entityHandler->getTileMap().replaceTileAt(tileX, tileY, new ObjectTile(tileX * 32, tileY * 32,
                                                                                               &entityHandler->getTileMap()));
                    }
                }
            }

            if (IsKeyDown(KEY_A)) {
                velocity.x = -speed;
            } else if (IsKeyDown(KEY_D)) {
                velocity.x = speed;
            }else {
                velocity.x = 0;
            }
            if (IsKeyDown(KEY_S)) {
                velocity.y = speed;
            } else if (IsKeyDown(KEY_W)) {
                velocity.y = -speed;
            } else {
                velocity.y = 0;
            }
        }

    private:
        float timer = 0;
    };
}

#endif //JANUS_PLAYER_HPP
