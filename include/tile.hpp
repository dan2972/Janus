#ifndef JANUS_TILE_HPP
#define JANUS_TILE_HPP

#include <raylib-cpp.hpp>
#include <random>
#include "game_object.hpp"
#include "tilemap.hpp"

namespace Janus {
    class Tile : public GameObject {
    public:
        const static int TILE_SIZE = 32;
        Tile() {
            position = {0, 0};
            size = {TILE_SIZE, TILE_SIZE};
            type = Type::TILE;
        }

        Tile(float x, float y, Tilemap* tilemap) : tilemap{tilemap} {
            position = {x, y};
            size = {TILE_SIZE, TILE_SIZE};
            type = Type::TILE;
        }

        virtual void scheduledTick() {

        }

        void tick() override {
            c = GREEN;
        }

        void render(float dt) override {
            DrawRectangle((int)position.x, (int)position.y, (int)size.x, (int)size.y, c);
        }
    private:
        Tilemap* tilemap = nullptr;
        raylib::Color c = GRAY;
    };
}

#endif //JANUS_TILE_HPP
