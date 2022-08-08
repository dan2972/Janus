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
            type = Type::TILE;
        }

        Tile(float x, float y) {
            position = {x, y};
            size = {TILE_SIZE, TILE_SIZE};
            type = Type::TILE;
        }

        void tick() override {

        }

        void render(float dt) override {
            DrawRectangle((int)position.x, (int)position.y, (int)size.x, (int)size.y, GRAY);
        }
    };
}

#endif //JANUS_TILE_HPP
