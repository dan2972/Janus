#ifndef JANUS_GROUND_TILE_HPP
#define JANUS_GROUND_TILE_HPP

#include "tile.hpp"

namespace Janus {
    class GroundTile : public Tile{
    public:
        enum GroundTileType {
            GRASS,
            SAND,
            WATER,
            STONE,
            DIRT
        };

        GroundTile(float x, float y, Tilemap* tilemap)
            : Tile(x, y, tilemap) {
            tileType = TileType::GROUND;
            groundTileType = GroundTileType::GRASS;
        }

        GroundTile(float x, float y, GroundTileType type, Tilemap* tilemap)
            : Tile(x, y, tilemap), groundTileType{type}{
            tileType = TileType::GROUND;
        }

        GroundTileType getGroundTileType() {
            return groundTileType;
        }

        void setType(GroundTileType type) {
            groundTileType = type;
        }
    private:
        GroundTileType groundTileType;
    };
}

#endif //JANUS_GROUND_TILE_HPP
