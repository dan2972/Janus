#include <glm/glm.hpp>
#include "game_camera.hpp"
#include "global_values.hpp"

namespace Janus {
    GameCamera::GameCamera() {
        camera.zoom = zoomValue;
        camera.rotation = 0.0f;
        camera.offset = {0, 0};
    }

    void GameCamera::update(float d) {
        if (targetActor != nullptr) {
            pos = glm::mix(targetActor->lastPos, targetActor->position, d);
            pos += glm::vec2{targetActor->size.x / 2, targetActor->size.y / 2};
            camera.target = {pos.x, pos.y};
            camera.offset = {static_cast<float>(SCREEN_WIDTH / 2),static_cast<float>(SCREEN_HEIGHT / 2)};

            if (IsKeyReleased(KEY_MINUS)) {
                zoomValue -= 0.1f;
                camera.zoom = zoomValue;
                camera.offset = {static_cast<float>(SCREEN_WIDTH / 2),static_cast<float>(SCREEN_HEIGHT / 2)};
            }
            if (IsKeyReleased(KEY_EQUAL)) {
                zoomValue += 0.1f;
                camera.zoom = zoomValue;
                camera.offset = {static_cast<float>(SCREEN_WIDTH / 2),static_cast<float>(SCREEN_HEIGHT / 2)};
            }
        }
    }

    void GameCamera::setTarget(ActorComponent& actor) {
        targetActor = &actor;
        camera.offset = {static_cast<float>(SCREEN_WIDTH / 2),static_cast<float>(SCREEN_HEIGHT / 2)};
    }
}