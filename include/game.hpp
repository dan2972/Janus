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
        Tilemap tilemap;
        Player* player;

        void update();
        void render(float dt);
    };
}

#endif //JANUS_GAME_HPP
