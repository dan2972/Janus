#include <glm/glm.hpp>
#include "actor.hpp"
#include "physics/collisions.hpp"
#include "tile_math_helper.hpp"

namespace Janus {
    void Actor::tick() {
        handleMovement();
        chunkPos = glm::vec2{position.x > 0 ? (int)position.x / (Chunk::CHUNK_SIZE*Tile::TILE_SIZE) :
                             (int)(position.x - Chunk::CHUNK_SIZE*Tile::TILE_SIZE)/ (Chunk::CHUNK_SIZE*Tile::TILE_SIZE),
                             position.y > 0 ? (int)position.y / (Chunk::CHUNK_SIZE*Tile::TILE_SIZE) :
                             (int)(position.y - Chunk::CHUNK_SIZE*Tile::TILE_SIZE)/ (Chunk::CHUNK_SIZE*Tile::TILE_SIZE)};
        tilePos = {(position.x + size.x / 2) / Tile::TILE_SIZE,
                   (position.y + size.x / 2) / Tile::TILE_SIZE};
    }

    void Actor::handleMovement() {
        lastPos = position;
        if (collidesWithActors) {
            for (auto& obj : entityHandler->getList(GameObject::ACTOR)) {
                if (obj.get() != this) {
                    handleCollision(*obj);
                }
            }
        }

        if (collidesWithTiles) {
            /*
            auto [checkPosX, checkPosY] = TileMathHelper::tileCoordToInt(tilePos.x, tilePos.y);
            auto tiles = entityHandler->getTileMap().getTilesInRange(checkPosX - 2, checkPosY - 2, checkPosX + 2, checkPosY + 2);
            for (auto tile : tiles) {
                if (tile.get().getTileType() == Tile::TileType::OBJECT)
                    handleCollision(tile.get());
            }*/
            handleTileCollision(entityHandler->getTileMap());
        }

        position.x += velocity.x;
        position.y += velocity.y;
    }

    void Actor::handleCollision(GameObject& obj) {
        glm::vec4 broadPhaseBox = Collisions::GetSweptBroadPhaseBox({position, size}, velocity);

        colliding = false;
        if (Collisions::AABB(broadPhaseBox, {obj.getPos(), obj.getSize()})) {
            colliding = true;
            glm::vec2 normal;

            float contactTime = 0.0f;
            if (Collisions::SweptAABB({position, size}, velocity, {obj.getPos(), obj.getSize()}, normal, contactTime)) {
                if (collisionResponseType == CollisionResponseType::STOP) {
                    velocity = {0,0};
                } else if (collisionResponseType == CollisionResponseType::SLIDE) {
                    velocity += normal * glm::abs(velocity) * (1 - contactTime);
                }
            }
        }
    }

    void Actor::handleTileCollision(Tilemap& tilemap) {
        glm::vec4 broadPhaseBox = Collisions::GetSweptBroadPhaseBox({position, size}, velocity);
        auto [bpbL, bpbT] = TileMathHelper::tileCoordToInt(broadPhaseBox.x / Tile::TILE_SIZE,
                                                           broadPhaseBox.y / Tile::TILE_SIZE);
        auto [bpbR, bpbB] = TileMathHelper::tileCoordToInt((broadPhaseBox.x + broadPhaseBox.z) / Tile::TILE_SIZE,
                                                           (broadPhaseBox.y + broadPhaseBox.w) / Tile::TILE_SIZE);
        auto tiles = tilemap.getTilesInRange(bpbL, bpbT, bpbR, bpbB);

        glm::vec2 cn;
        float t = 0;
        std::vector<std::pair<int, float>> collidedList;
        for (int i = 0; i < tiles.size(); ++i) {
            auto& tile = tiles[i].get();
            if (tile.getTileType() == Tile::TileType::OBJECT) {
                if (Collisions::SweptAABB({position, size}, velocity, {tile.getPos(), tile.getSize()}, cn, t)) {
                    collidedList.emplace_back(i, t);
                }
            }
        }

        std::sort(collidedList.begin(), collidedList.end(),
                  [](const std::pair<int, float>& a, const std::pair<int, float>& b)
                  {
                        return a.second < b.second;
                  });

        colliding = false;
        for (auto pair : collidedList) {
            colliding = true;
            glm::vec2 normal;

            float contactTime = 0.0f;
            auto& tile = tiles[pair.first].get();
            if (Collisions::SweptAABB({position, size}, velocity,
                                      {tile.getPos(), tile.getSize()},
                                      normal, contactTime)) {
                if (collisionResponseType == CollisionResponseType::STOP) {
                    velocity = {0,0};
                } else if (collisionResponseType == CollisionResponseType::SLIDE) {
                    velocity += normal * glm::abs(velocity) * (1 - contactTime);
                }
            }
        }
    }
}