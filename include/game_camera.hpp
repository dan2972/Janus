#ifndef JANUS_GAME_CAMERA_HPP
#define JANUS_GAME_CAMERA_HPP

#include <raylib-cpp.hpp>
#include <glm/glm.hpp>

namespace Janus {
    class Player;
    class GameCamera {
    public:
        GameCamera();

        void start() { camera.BeginMode(); }
        void end() { camera.EndMode(); }

        void update(float dt);
        void setTargetPlayer(Player* player);

        [[nodiscard]] glm::vec2 getPos() const { return pos; };
        [[nodiscard]] glm::vec2 getOffset() const { return {camera.GetOffset().x, camera.GetOffset().y}; };
        [[nodiscard]] float getZoom() const { return zoomValue; };

    private:
        raylib::Camera2D camera;

        glm::vec2 pos{};

        Player* targetPlayer = nullptr;

        float zoomValue = 1.0f;
    };
}

#endif //JANUS_GAME_CAMERA_HPP
