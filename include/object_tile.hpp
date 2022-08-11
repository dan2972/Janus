#ifndef JANUS_OBJECT_TILE_HPP
#define JANUS_OBJECT_TILE_HPP

#include "tile.hpp"

namespace Janus {
    class ObjectTile : public Tile{
    public:
        ObjectTile(float x, float y, Tilemap* tilemap) : Tile(x, y, tilemap) {
            tileType = TileType::OBJECT;
        }
    private:
    };
}

#endif //JANUS_OBJECT_TILE_HPP