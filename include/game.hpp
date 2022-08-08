#ifndef JANUS_GAME_HPP
#define JANUS_GAME_HPP

#include <raylib-cpp.hpp>
#include "entity_handler.hpp"
#include "tilemap.hpp"
#include "player.hpp"

namespace Janus {
    class Game {
    public:
        Game();

        void run();

        static int screenWidth;
        static int screenHeight;
    private:
        raylib::Window window{screenWidth, screenHeight, "Janus"};
        EntityHandler entityHandler;
        Player* player;

        void update();
        void render(float dt);

        int FPS = 0;
    };
}

#endif //JANUS_GAME_HPP
