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
            tileType = TileType::NONE;
        }

        Tile(float x, float y, Tilemap* tilemap) : tilemap{tilemap} {
            position = {x, y};
            size = {TILE_SIZE, TILE_SIZE};
            type = Type::TILE;
            tileType = TileType::NONE;
        }

        virtual void scheduledTick() {

        }

        void tick() override { }

        enum TileType {
            GROUND,
            OBJECT,
            NONE
        };

        TileType getTileType() { return tileType; }
    protected:
        Tilemap* tilemap = nullptr;
        TileType tileType;
    };
}

#endif //JANUS_TILE_HPP
