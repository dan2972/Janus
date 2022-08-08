#ifndef JANUS_ACTOR_HPP
#define JANUS_ACTOR_HPP

#include "game_object.hpp"
#include "entity_handler.hpp"
#include "texture_manager.hpp"

namespace Janus {
    class Actor : public GameObject {
    public:
        explicit Actor(EntityHandler* entityHandler, float x, float y) : entityHandler{entityHandler} {
            position.x = x;
            position.y = y;
            size.x = 32;
            size.y = 32;
            type = Type::ACTOR;
        }

        void tick() override {
            handleMovement();
        }

        void render(float dt) override {
            DrawRectangle((int)position.x, (int)position.y, (int)size.x, (int)size.y, raylib::Color(200,255,200));
        }

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

        glm::vec2 lastPos{};

    private:
        void handleMovement();
        void handleCollision(GameObject* obj);
    };
}

#endif //JANUS_ACTOR_HPP
