#ifndef JANUS_GAME_CAMERA_HPP
#define JANUS_GAME_CAMERA_HPP

#include <raylib-cpp.hpp>
#include <glm/glm.hpp>
#include "player.hpp"

namespace Janus {
    class GameCamera {
    public:
        GameCamera() {
            camera.SetZoom(1);
            camera.SetRotation(0);
            camera.SetOffset({0, 0});
        }

        void setTargetPlayer(Player* player) {
            targetPlayer = player;
            camera.SetOffset({400 - player->getSize().x / 2, 300 - player->getSize().y / 2});
        }
        void start() { camera.BeginMode(); }
        void end() { camera.EndMode(); }
        void update() {
            pos = glm::mix(pos, targetPlayer->getRenderPos(), 0.1f);
            camera.SetTarget({pos.x, pos.y});
        }

    private:
        raylib::Camera2D camera;

        glm::vec2 pos{};

        Player* targetPlayer = nullptr;
    };
}

#endif //JANUS_GAME_CAMERA_HPP
