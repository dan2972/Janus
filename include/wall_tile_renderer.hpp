#ifndef JANUS_WALL_TILE_RENDERER_HPP
#define JANUS_WALL_TILE_RENDERER_HPP

#include <array>
#include "object_tile.hpp"
#include "tilemap.hpp"
#include "tile_math_helper.hpp"
#include "texture_manager.hpp"

namespace Janus {
    class WallTileRenderer{
    public:
        static void drawWall(Tilemap& tilemap, const ObjectTile& tile);

    private:
        static std::array<bool, 9> getNearbyWalls(Tilemap& tilemap, int tileX, int tileY);

        static void drawTopLeft(int spriteTileX, int spriteTileY, raylib::Texture2D* texture, int localX, int localY);
        static void drawTopRight(int spriteTileX, int spriteTileY, raylib::Texture2D* texture, int localX, int localY);
        static void drawBottomLeft(int spriteTileX, int spriteTileY, raylib::Texture2D* texture, int localX, int localY);
        static void drawBottomRight(int spriteTileX, int spriteTileY, raylib::Texture2D* texture, int localX, int localY);
    };
}

#endif //JANUS_WALL_TILE_RENDERER_HPP
