#ifndef JANUS_ACTOR_HPP
#define JANUS_ACTOR_HPP

#include <glm/glm.hpp>
#include "game_object.hpp"
#include "entity_handler.hpp"
#include "texture_manager.hpp"
#include "chunk.hpp"

namespace Janus {
    class Actor : public GameObject {
    public:
        Actor(float x, float y, EntityHandler* entityHandler) : entityHandler{entityHandler} {
            position.x = x;
            position.y = y;
            size.x = 32;
            size.y = 32;
            type = Type::ACTOR;
        }

        enum ActorType {
            PLAYER,
            NONE
        };

        void tick() override {
            handleMovement();
            chunkPos = glm::vec2{position.x > 0 ? (int)position.x / (Chunk::CHUNK_SIZE*Tile::TILE_SIZE) :
                                 (int)(position.x - Chunk::CHUNK_SIZE*Tile::TILE_SIZE)/ (Chunk::CHUNK_SIZE*Tile::TILE_SIZE),
                                 position.y > 0 ? (int)position.y / (Chunk::CHUNK_SIZE*Tile::TILE_SIZE) :
                                 (int)(position.y - Chunk::CHUNK_SIZE*Tile::TILE_SIZE)/ (Chunk::CHUNK_SIZE*Tile::TILE_SIZE)};
        }

        [[nodiscard]] glm::vec2 getLastPos() const { return lastPos; }
        [[nodiscard]] glm::vec2 getChunkPos() const { return chunkPos; }
        [[nodiscard]] ActorType getActorType() const { return actorType; }

        glm::vec2 velocity{};

    protected:
        EntityHandler* entityHandler = nullptr;
        raylib::Texture2D* texture = nullptr;

        bool collidesWithActors = false;
        bool colliding = false;
        enum CollisionResponseType {
            STOP,
            SLIDE
        };
        CollisionResponseType collisionResponseType = CollisionResponseType::STOP;

        ActorType actorType = ActorType::NONE;

        glm::vec2 lastPos{};
        glm::vec2 chunkPos{};

    private:
        void handleMovement();
        void handleCollision(GameObject* obj);
    };
}

#endif //JANUS_ACTOR_HPP
