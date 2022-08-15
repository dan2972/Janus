#ifndef JANUS_GAME_HPP
#define JANUS_GAME_HPP

#include <raylib-cpp.hpp>
#include "entity_handler.hpp"
#include "tilemap.hpp"
#include "player.hpp"
#include "game_camera.hpp"
#include "global_values.hpp"

namespace Janus {
    class Game {
    public:
        Game();

        void run();

    private:
        raylib::Window window{SCREEN_WIDTH, SCREEN_HEIGHT, "Janus"};
        GameCamera camera;
        EntityHandler entityHandler;
        Player* player;

        void update();
        void render(float dt);

        int FPS = 0;
    };
}

#endif //JANUS_GAME_HPP
