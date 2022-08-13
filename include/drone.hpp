#ifndef JANUS_DRONE_HPP
#define JANUS_DRONE_HPP

#include "actor.hpp"

namespace Janus {
    class Drone : public Actor {
    public:
        Drone(float x, float y, EntityHandler* entityHandler) : Actor(x, y, entityHandler) {
            size.x = 8;
            size.y = 8;

            collisionResponseType = CollisionResponseType::SLIDE;
            collidesWithActors = false;
            collidesWithTiles = true;

            actorType = ActorType::DRONE;
        }

        void tick() override {
            Actor::tick();
            velocity.x = std::cos(direction) * speed;
            velocity.y = std::sin(direction) * speed;

            ++timer;
            if (timer == 10) {
                timer = 0;
                float adder = (float) GetRandomValue(0, 360) / 360.0f - 0.5f;
                direction += adder;
            }
        }

    private:
        int timer = 0;
        float speed = 10;
        float direction = (float) GetRandomValue(0, 360) / 360.0f * 3.14f * 2;
    };
}

#endif //JANUS_DRONE_HPP
