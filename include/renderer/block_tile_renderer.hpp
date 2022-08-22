#ifndef JANUS_BLOCK_TILE_RENDERER_HPP
#define JANUS_BLOCK_TILE_RENDERER_HPP

#include <raylib.h>
#include "tilemap.hpp"
#include "tile_data.hpp"

namespace Janus {
    class BlockTileRenderer{
    public:
        static void drawBlock(Tilemap& tilemap, const ObjectTile& tile);

    private:
        static std::array<bool, 9> getNearbyWalls(Tilemap& tilemap, int tileX, int tileY);

        static void drawTopLeft(int spriteTileX, int spriteTileY, Texture2D* texture, int localX, int localY);
        static void drawTopRight(int spriteTileX, int spriteTileY, Texture2D* texture, int localX, int localY);
        static void drawBottomLeft(int spriteTileX, int spriteTileY, Texture2D* texture, int localX, int localY);
        static void drawBottomRight(int spriteTileX, int spriteTileY, Texture2D* texture, int localX, int localY);
    };
}

#endif //JANUS_BLOCK_TILE_RENDERER_HPP
