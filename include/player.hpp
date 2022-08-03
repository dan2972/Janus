#ifndef JANUS_PLAYER_HPP
#define JANUS_PLAYER_HPP

#include "game_object.hpp"
#include <raylib-cpp.hpp>

namespace Janus {
    class Player : public GameObject {
    public:
        explicit Player(EntityHandler* entityHandler, int x, int y) : entityHandler{entityHandler} {
            position.x = x;
            position.y = y;
        };

        void update(float deltaTime) override {
            timer += deltaTime;
            if (timer >= 2) {
                entityHandler->remove(this);
            }
        }

        void render() override {
            DrawRectangle((int)position.x, (int)position.y, 32, 32, raylib::Color(200,255,200));
        }
    private:
        EntityHandler* entityHandler = nullptr;
        float timer = 0;
    };
}

#endif //JANUS_PLAYER_HPP
