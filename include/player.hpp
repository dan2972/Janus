#ifndef JANUS_PLAYER_HPP
#define JANUS_PLAYER_HPP

#include <raylib-cpp.hpp>
#include <glm/glm.hpp>
#include "texture_manager.hpp"
#include "actor.hpp"
#include "tile_math_helper.hpp"
#include "object_tile.hpp"
#include "global_values.hpp"
#include "ground_tile.hpp"
#include "input_manager.hpp"

namespace Janus {
    class Player : public Actor {
    public:
        Player(float x, float y, EntityHandler* entityHandler, GameCamera* camera)
            : Actor(x, y, entityHandler), camera{camera} {
            size.x = 20;
            size.y = 26;

            collisionResponseType = CollisionResponseType::SLIDE;
            collidesWithActors = false;
            collidesWithTiles = true;

            actorType = ActorType::PLAYER;
        }

        void tick() override {
            Actor::tick();
            if (timer >= 2) {
                //entityHandler->remove(this);
            }

            int chunkLoadRadius = CHUNK_LOAD_DISTANCE;
            for (int i = (int)chunkPos.y - chunkLoadRadius; i <= (int)chunkPos.y + chunkLoadRadius; ++i) {
                for (int j = (int)chunkPos.x - chunkLoadRadius; j <= (int)chunkPos.x + chunkLoadRadius; ++j) {
                    if (!entityHandler->getTileMap().chunkExistsAt((int) j, (int) i)) {
                        entityHandler->getTileMap().addChunk(new Chunk((int) j, (int) i, &entityHandler->getTileMap()));
                    }
                }
            }

            inWater = false;
            auto [tileX, tileY] = TileMathHelper::tileCoordToInt(tilePos.x, tilePos.y);
            Tile* currTile = entityHandler->getTileMap().getTileAt(tileX, tileY);
            if (currTile != nullptr && currTile->getTileType() == Tile::TileType::GROUND) {
                auto* gt = (GroundTile*) currTile;
                if (gt->getGroundTileType() == GroundTile::WATER) {
                    inWater = true;
                }
            }

            auto[mTileX, mTileY] = TileMathHelper::screenCoordToTileCoordInt(GetMouseX(), GetMouseY(), *camera);
            Tile* mouseTile = entityHandler->getTileMap().getTileAt(mTileX, mTileY);
            if (mouseTile != nullptr ) {
                if (InputManager::PlayerAttackDown()) {
                    if (mouseTile->getTileType() == Tile::TileType::GROUND) {
                        entityHandler->getTileMap().replaceTileAt(mTileX, mTileY,
                                                                  new ObjectTile(mTileX * 32, mTileY * 32,
                                                                                 &entityHandler->getTileMap()));
                    }
                } else if (InputManager::PlayerPlaceDown()){
                    entityHandler->getTileMap().replaceTileAt(mTileX, mTileY,
                                                              new GroundTile(mTileX * 32, mTileY * 32,
                                                                             GroundTile::STONE,
                                                                             &entityHandler->getTileMap()));
                }
            }

            if (inWater) speed = waterSpeed;
            else speed = groundSpeed;

            if (InputManager::MoveLeftDown()) {
                velocity.x = -speed;
            } else if (InputManager::MoveRightDown()) {
                velocity.x = speed;
            }else {
                velocity.x = 0;
            }
            if (InputManager::MoveDownDown()) {
                velocity.y = speed;
            } else if (InputManager::MoveUpDown()) {
                velocity.y = -speed;
            } else {
                velocity.y = 0;
            }
        }

        [[nodiscard]] bool isInWater() const { return inWater; }

    private:
        GameCamera* camera;

        float timer = 0;
        float groundSpeed = 10;
        float waterSpeed = 6;
        float speed = groundSpeed;
        bool inWater = false;
    };
}

#endif //JANUS_PLAYER_HPP
