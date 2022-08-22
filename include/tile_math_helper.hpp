#ifndef JANUS_TILE_MATH_HELPER_HPP
#define JANUS_TILE_MATH_HELPER_HPP

#include <utility>
#include "game_camera.hpp"

namespace Janus {
    class TileMathHelper{
    public:
        static std::pair<int, int> tileCoordToInt(float x, float y);
        static std::pair<int, int> screenCoordToTileCoordInt(int x, int y, const GameCamera& camera);
        static std::pair<int, int> tileCoordToChunk(int tileX, int tileY);
        static std::pair<unsigned char, unsigned char> tileCoordToLocalChunkCoord(int tileX, int tileY);
        static std::tuple<int, int, unsigned char, unsigned char> tileCoordToChunkAndLocalChunkCoord(int tileX, int tileY);
    };
}

#endif //JANUS_TILE_MATH_HELPER_HPP
