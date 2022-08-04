#ifndef JANUS_PLAYER_HPP
#define JANUS_PLAYER_HPP

#include "game_object.hpp"
#include "texture_manager.hpp"
#include <raylib-cpp.hpp>

namespace Janus {
    class Player : public GameObject {
    public:
        explicit Player(EntityHandler* entityHandler, int x, int y) : entityHandler{entityHandler} {
            position.x = x;
            position.y = y;

            texture = TextureManager::getTexture("resources/slime.png");
        };

        void update(float deltaTime) override {
            timer += deltaTime;
            if (timer >= 2) {
                entityHandler->remove(this);
            }
        }

        void render() override {
            //DrawRectangle((int)position.x, (int)position.y, 32, 32, raylib::Color(200,255,200));
            DrawTexturePro(*texture, raylib::Rectangle({0,0}, {(float)texture->width, (float)texture->height}),
                                    raylib::Rectangle({position.x, position.y}, {32, 32}),
                                    {16, 16}, 0, WHITE);
        }
    private:
        EntityHandler* entityHandler = nullptr;
        raylib::Texture2D* texture;

        float timer = 0;
    };
}

#endif //JANUS_PLAYER_HPP
