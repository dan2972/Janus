#ifndef JANUS_TILE_MATH_HELPER_HPP
#define JANUS_TILE_MATH_HELPER_HPP

#include <utility>
#include "chunk.hpp"
#include "game_camera.hpp"

namespace Janus {
    class TileMathHelper {
    public:
        static std::pair<int, int> tileCoordToInt(float x, float y) {
            return {x < 0 ? x - 1 : x, y < 0 ? y - 1 : y};
        }

        static std::pair<int, int> screenCoordToTileCoordInt(int x, int y, const GameCamera& camera) {
            float mx = x / camera.getZoom();
            float my = y / camera.getZoom();
            mx += camera.getPos().x - camera.getOffset().x / camera.getZoom();
            my += camera.getPos().y - camera.getOffset().y / camera.getZoom();
            mx /= (Tile::TILE_SIZE);
            my /= (Tile::TILE_SIZE);
            return {mx < 0 ? mx - 1 : mx, my < 0 ? my - 1 : my};
        }

        static std::pair<int, int> tileCoordToChunk(int tileX, int tileY) {
            int chunkX = tileX >= 0 ? tileX / Chunk::CHUNK_SIZE : (tileX - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
            int chunkY = tileY >= 0 ? tileY / Chunk::CHUNK_SIZE : (tileY - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
            return {chunkX, chunkY};
        }

        static std::pair<unsigned char, unsigned char> tileCoordToLocalChunkCoord(int tileX, int tileY) {
            int chunkX = tileX >= 0 ? tileX / Chunk::CHUNK_SIZE : (tileX - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
            int chunkY = tileY >= 0 ? tileY / Chunk::CHUNK_SIZE : (tileY - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
            int localX = tileX - chunkX*Chunk::CHUNK_SIZE;
            int localY = tileY - chunkY*Chunk::CHUNK_SIZE;
            return {localX, localY};
        }

        static std::tuple<int, int, unsigned char, unsigned char> tileCoordToChunkAndLocalChunkCoord(int tileX, int tileY) {
            int chunkX = tileX >= 0 ? tileX / Chunk::CHUNK_SIZE : (tileX - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
            int chunkY = tileY >= 0 ? tileY / Chunk::CHUNK_SIZE : (tileY - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
            int localX = tileX - chunkX*Chunk::CHUNK_SIZE;
            int localY = tileY - chunkY*Chunk::CHUNK_SIZE;
            return {chunkX, chunkY, localX, localY};
        }

    };
}

#endif //JANUS_TILE_MATH_HELPER_HPP
