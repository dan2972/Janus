#include "game_camera.hpp"
#include "player.hpp"

namespace Janus {
    GameCamera::GameCamera() {
        camera.SetZoom(zoomValue);
        camera.SetRotation(0);
        camera.SetOffset({0, 0});
    }

    void GameCamera::setTargetPlayer(Player *player) {
        targetPlayer = player;
        camera.SetOffset({400 - (player->getSize().x / 2) * zoomValue,
                          300 - (player->getSize().y / 2) * zoomValue});
    }

    void GameCamera::update(float dt) {
        pos = glm::mix(targetPlayer->getLastPos(), targetPlayer->getPos(), dt);
        camera.SetTarget({pos.x, pos.y});

        if (IsKeyReleased(KEY_MINUS)) {
            zoomValue -= 0.1f;
            camera.SetZoom(zoomValue);
            camera.SetOffset({400 - (targetPlayer->getSize().x / 2) * zoomValue,
                              300 - (targetPlayer->getSize().y / 2) * zoomValue});
        }
        if (IsKeyReleased(KEY_EQUAL)) {
            zoomValue += 0.1f;
            camera.SetZoom(zoomValue);
            camera.SetOffset({400 - (targetPlayer->getSize().x / 2) * zoomValue,
                              300 - (targetPlayer->getSize().y / 2) * zoomValue});
        }
    }
}
