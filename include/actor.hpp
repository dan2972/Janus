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
            DRONE,
            NONE
        };

        void tick() override;

        [[nodiscard]] glm::vec2 getLastPos() const { return lastPos; }
        [[nodiscard]] glm::vec2 getChunkPos() const { return chunkPos; }
        [[nodiscard]] glm::vec2 getTilePos() const { return tilePos; }
        [[nodiscard]] ActorType getActorType() const { return actorType; }

        glm::vec2 velocity{};

    protected:
        EntityHandler* entityHandler = nullptr;

        bool collidesWithActors = false;
        bool collidesWithTiles = false;
        bool colliding = false;
        enum CollisionResponseType {
            STOP,
            SLIDE
        };
        CollisionResponseType collisionResponseType = CollisionResponseType::STOP;

        ActorType actorType = ActorType::NONE;

        glm::vec2 lastPos{};
        glm::vec2 chunkPos{};
        glm::vec2 tilePos{};

    private:
        void handleMovement();
        void handleCollision(GameObject& obj);
        void handleTileCollision(Tilemap& tilemap);
    };
}

#endif //JANUS_ACTOR_HPP
