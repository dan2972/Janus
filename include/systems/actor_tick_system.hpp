#ifndef JANUS_ACTOR_TICK_SYSTEM_HPP
#define JANUS_ACTOR_TICK_SYSTEM_HPP

#include "tick_system.hpp"
#include "world.hpp"
#include "components/components.hpp"
#include "tile_math_helper.hpp"
#include "tile_data.hpp"
#include "glm/vec4.hpp"
#include "physics/collisions.hpp"

namespace Janus {
    class ActorTickSystem : public TickSystem{
    public:
        using TickSystem::TickSystem;
        void tick() override {
            auto view = world->getEntitiesWith<ActorComponent>();
            for (auto entity : view) {
                auto& actor = world->getComponentFromEntity<ActorComponent>(entity);

                handleMovement(entity, actor);

                float centerX = actor.position.x + actor.size.x / 2;
                float centerY = actor.position.y + actor.size.y / 2;
                auto [tileX, tileY] = TileMathHelper::tileCoordToInt(centerX / TILE_SIZE, centerY / TILE_SIZE);
                actor.tilePos = {tileX, tileY};
                auto [chunkX, chunkY] = TileMathHelper::tileCoordToChunk(tileX, tileY);
                actor.chunkPos = {chunkX, chunkY};
            }
        }
    private:
        void handleMovement(entt::entity actorID, ActorComponent& actor) {
            actor.lastPos = actor.position;
            if (actor.collidesWithActors) {
                auto view = world->getEntitiesWith<ActorComponent>();
                for (auto entity : view) {
                    if (actorID != entity) {
                        auto& other = world->getComponentFromEntity<ActorComponent>(entity);
                        handleActorCollision(actor, other);
                    }
                }
            }

            if (actor.collidesWithTiles) {
                handleTileCollision(actor, world->getTilemap());
            }

            actor.position += actor.velocity;
        }

        void handleActorCollision(ActorComponent& main, ActorComponent& other) {
            glm::vec4 broadPhaseBox = Collisions::GetSweptBroadPhaseBox({main.position, main.size}, main.velocity);

            if (Collisions::AABB(broadPhaseBox, {other.position, other.size})) {
                glm::vec2 normal;

                float contactTime = 0.0f;
                if (Collisions::SweptAABB({main.position, main.size}, main.velocity,
                                          {other.position, other.size}, normal, contactTime)) {
                    if (main.collisionResponseType == CollisionResponseType::STOP) {
                        main.velocity = {0,0};
                    } else if (main.collisionResponseType == CollisionResponseType::SLIDE) {
                        main.velocity += normal * glm::abs(main.velocity) * (1 - contactTime);
                    }
                }
            }
        }

        void handleTileCollision(ActorComponent& actor, Tilemap& tilemap) {
            glm::vec4 broadPhaseBox = Collisions::GetSweptBroadPhaseBox({actor.position, actor.size}, actor.velocity);
            auto [bpbL, bpbT] = TileMathHelper::tileCoordToInt(broadPhaseBox.x / TILE_SIZE,
                                                               broadPhaseBox.y / TILE_SIZE);
            auto [bpbR, bpbB] = TileMathHelper::tileCoordToInt((broadPhaseBox.x + broadPhaseBox.z) / TILE_SIZE,
                                                               (broadPhaseBox.y + broadPhaseBox.w) / TILE_SIZE);
            auto tiles = tilemap.getObjectTilesInRange(bpbL, bpbT, bpbR, bpbB);

            glm::vec2 cn;
            float t = 0;
            std::vector<std::pair<int, float>> collidedList;
            for (int i = 0; i < tiles.size(); ++i) {
                auto& tile = tiles[i].get();
                if (tile.id != ObjectTileID::AIR && tile.id != ObjectTileID::NONE) {
                    int tilePosX = tile.tileX * TILE_SIZE;
                    int tilePosY = tile.tileY * TILE_SIZE;
                    if (Collisions::SweptAABB({actor.position, actor.size}, actor.velocity,
                                              {tilePosX, tilePosY, TILE_SIZE, TILE_SIZE}, cn, t)) {
                        collidedList.emplace_back(i, t);
                    }
                }
            }

            std::sort(collidedList.begin(), collidedList.end(),
                      [](const std::pair<int, float>& a, const std::pair<int, float>& b)
                      {
                          return a.second < b.second;
                      });

            for (auto pair : collidedList) {
                glm::vec2 normal;

                float contactTime = 0.0f;
                auto& tile = tiles[pair.first].get();
                int tilePosX = tile.tileX * TILE_SIZE;
                int tilePosY = tile.tileY * TILE_SIZE;
                if (Collisions::SweptAABB({actor.position, actor.size}, actor.velocity,
                                          {tilePosX, tilePosY, TILE_SIZE, TILE_SIZE},
                                          normal, contactTime)) {
                    if (actor.collisionResponseType == CollisionResponseType::STOP) {
                        actor.velocity = {0,0};
                    } else if (actor.collisionResponseType == CollisionResponseType::SLIDE) {
                        actor.velocity += normal * glm::abs(actor.velocity) * (1 - contactTime);
                    }
                }
            }
        }
    };
}

#endif //JANUS_ACTOR_TICK_SYSTEM_HPP
