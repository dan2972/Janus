#ifndef JANUS_PLAYER_HPP
#define JANUS_PLAYER_HPP

#include "texture_manager.hpp"
#include "actor.hpp"
#include <raylib-cpp.hpp>
#include <iostream>

namespace Janus {
    class Player : public Actor {
    public:
        explicit Player(EntityHandler *entityHandler, int x, int y) : Actor(entityHandler, x, y){
            size.x = 32;
            size.y = 32;

            texture = TextureManager::GetTexture("resources/slime.png");

            collisionResponseType = CollisionResponseType::SLIDE;
            collidesWithActors = true;
        };

        void tick(float deltaTime) override {
            Actor::tick(deltaTime);
            timer += deltaTime;
            if (timer >= 2) {
                //entityHandler->remove(this);
            }

            float speed = 200;

            if (IsKeyDown(KEY_A)) {
                velocity.x = -speed;
            } else if (IsKeyDown(KEY_D)) {
                velocity.x = speed;
            }else {
                velocity.x = 0;
            }
            if (IsKeyDown(KEY_S)) {
                velocity.y = speed;
            } else if (IsKeyDown(KEY_W)) {
                velocity.y = -speed;
            } else {
                velocity.y = 0;
            }

        }

        void render() override {
            //DrawRectangle((int)position.x, (int)position.y, 32, 32, raylib::Color(200,255,200));
            DrawTexturePro(*texture, raylib::Rectangle({0,0}, {(float)texture->width, (float)texture->height}),
                                    raylib::Rectangle({position.x, position.y}, {size.x, size.y}),
                                    {0, 0}, 0, WHITE);
        }
    private:
        EntityHandler* entityHandler = nullptr;
        raylib::Texture2D* texture = nullptr;

        float timer = 0;
    };
}

#endif //JANUS_PLAYER_HPP
