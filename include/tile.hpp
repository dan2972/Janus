#ifndef JANUS_TILE_HPP
#define JANUS_TILE_HPP

#include <raylib-cpp.hpp>
#include <random>
#include "game_object.hpp"

namespace Janus {
    class Tile : public GameObject {
    public:
        const static int TILE_SIZE = 32;
        Tile() {
            position = {0, 0};
            size = {TILE_SIZE, TILE_SIZE};
        }

        Tile(float x, float y) {
            position = {x, y};
            size = {TILE_SIZE, TILE_SIZE};
        }

        void tick(float deltaTIme) override {

        }

        void render() override {
            DrawRectangle((int)position.x, (int)position.y, (int)size.x, (int)size.y, GRAY);
        }
    };
}

#endif //JANUS_TILE_HPP
