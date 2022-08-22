#ifndef JANUS_GAME_HPP
#define JANUS_GAME_HPP

#include "game_camera.hpp"
#include "world.hpp"

namespace Janus {
    class Game{
    public:
        Game();

        void run();
    private:
        void update();
        void render(float d);

        GameCamera camera{};
        World world{&camera};

        int FPS = 0;
    };
}

#endif //JANUS_GAME_HPP
