#ifndef JANUS_ACTOR_HPP
#define JANUS_ACTOR_HPP

#include "game_object.hpp"
#include "entity_handler.hpp"
#include "texture_manager.hpp"

namespace Janus {
    class Actor : public GameObject {
    public:
        explicit Actor(EntityHandler* entityHandler, int x, int y) : entityHandler{entityHandler} {
            position.x = (float)x;
            position.y = (float)y;
            size.x = 32;
            size.y = 32;
        }

        void tick(float deltaTime) override {
            handleMovement(deltaTime);
        }

        void render() override {
            DrawRectangle((int)position.x, (int)position.y, 32, 32, raylib::Color(200,255,200));
        }

        glm::vec2 velocity{};

    protected:
        EntityHandler* entityHandler = nullptr;
        raylib::Texture2D* texture = nullptr;

        bool collidesWithActors = false;

        enum CollisionResponseType {
            STOP,
            SLIDE
        };
        CollisionResponseType collisionResponseType = CollisionResponseType::STOP;

        bool colliding = false;

    private:
        void handleMovement(float deltaTime);
        void handleCollision(GameObject* obj, float deltaTime);
    };
}

#endif //JANUS_ACTOR_HPP
