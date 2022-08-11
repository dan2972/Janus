#ifndef JANUS_GROUND_TILE_HPP
#define JANUS_GROUND_TILE_HPP

#include "tile.hpp"

namespace Janus {
    class GroundTile : public Tile{
    public:
        GroundTile(float x, float y, Tilemap* tilemap) : Tile(x, y, tilemap) {
            tileType = TileType::GROUND;
        }
    private:
    };
}

#endif //JANUS_GROUND_TILE_HPP
