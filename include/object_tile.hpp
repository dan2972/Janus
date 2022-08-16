#ifndef JANUS_OBJECT_TILE_HPP
#define JANUS_OBJECT_TILE_HPP

#include "tile.hpp"

namespace Janus {
    class ObjectTile : public Tile{
    public:
        enum ObjectTileType {
            WALL,
            NONE
        };

        ObjectTile(float x, float y, Tilemap* tilemap) : Tile(x, y, tilemap) {
            tileType = TileType::OBJECT;
            objectTileType = ObjectTileType::WALL;
        }

        ObjectTile(float x, float y, ObjectTileType objectTileType, Tilemap* tilemap)
            : Tile(x, y, tilemap), objectTileType{objectTileType} {
            tileType = TileType::OBJECT;
        }

        [[nodiscard]] ObjectTileType getObjectTileType() const { return objectTileType; };
    private:
        ObjectTileType objectTileType;
    };
}

#endif //JANUS_OBJECT_TILE_HPP
