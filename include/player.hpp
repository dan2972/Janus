#ifndef JANUS_PLAYER_HPP
#define JANUS_PLAYER_HPP

#include <raylib-cpp.hpp>
#include <glm/glm.hpp>
#include "texture_manager.hpp"
#include "actor.hpp"

namespace Janus {
    class Player : public Actor {
    public:
        Player(float x, float y, EntityHandler *entityHandler) : Actor(x, y, entityHandler){
            size.x = 32;
            size.y = 32;

            texture = TextureManager::GetTexture("resources/slime.png");

            collisionResponseType = CollisionResponseType::SLIDE;
            collidesWithActors = true;
        };

        void tick() override {
            Actor::tick();
            if (timer >= 2) {
                //entityHandler->remove(this);
            }

            if (!entityHandler->getTileMap().chunkExistsAt((int)chunkPos.x, (int)chunkPos.y)) {
                entityHandler->getTileMap().addChunk(new Chunk((int)chunkPos.x, (int)chunkPos.y));
            }

            float speed = 6;

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

        void render(float dt) override {
            glm::vec2 renderPos = glm::mix(lastPos, position, dt);

            DrawTexturePro(*texture, raylib::Rectangle({0,0}, {(float)texture->width, (float)texture->height}),
                                    raylib::Rectangle({renderPos.x, renderPos.y}, {size.x, size.y}),
                                    {0, 0}, 0, WHITE);
        }
    private:
        raylib::Texture2D* texture = nullptr;

        float timer = 0;
    };
}

#endif //JANUS_PLAYER_HPP
