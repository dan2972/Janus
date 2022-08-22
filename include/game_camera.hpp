#ifndef JANUS_GAME_CAMERA_HPP
#define JANUS_GAME_CAMERA_HPP

#include <raylib.h>
#include "glm/vec2.hpp"
#include "components/components.hpp"

namespace Janus {
    class GameCamera{
    public:
        GameCamera();

        void start() { BeginMode2D(camera); }
        void end() { EndMode2D(); }

        void update(float d);
        void setTarget(ActorComponent& actor);

        [[nodiscard]] glm::vec2 getPos() const { return pos; };
        [[nodiscard]] glm::vec2 getOffset() const { return {camera.offset.x, camera.offset.y}; };
        [[nodiscard]] float getZoom() const { return zoomValue; };
    private:
        Camera2D camera = {0};
        glm::vec2 pos{};
        ActorComponent* targetActor = nullptr;
        float zoomValue = 1.0f;
        float rotation = 0.0f;
    };
}

#endif //JANUS_GAME_CAMERA_HPP
