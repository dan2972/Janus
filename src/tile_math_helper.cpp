#include "tile_math_helper.hpp"
#include "tile_data.hpp"
#include "chunk.hpp"

namespace Janus {
    std::pair<int, int> TileMathHelper::tileCoordToInt(float x, float y) {
        return {x < 0 ? x - 1 : x, y < 0 ? y - 1 : y};
    }

    std::pair<int, int> TileMathHelper::screenCoordToTileCoordInt(int x, int y, const GameCamera &camera) {
        float mx = x / camera.getZoom();
        float my = y / camera.getZoom();
        mx += camera.getPos().x - camera.getOffset().x / camera.getZoom();
        my += camera.getPos().y - camera.getOffset().y / camera.getZoom();
        mx /= (TILE_SIZE);
        my /= (TILE_SIZE);
        return {mx < 0 ? mx - 1 : mx, my < 0 ? my - 1 : my};
    }

    std::pair<int, int> TileMathHelper::tileCoordToChunk(int tileX, int tileY) {
        int chunkX = tileX >= 0 ? tileX / Chunk::CHUNK_SIZE : (tileX - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
        int chunkY = tileY >= 0 ? tileY / Chunk::CHUNK_SIZE : (tileY - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
        return {chunkX, chunkY};
    }

    std::pair<unsigned char, unsigned char> TileMathHelper::tileCoordToLocalChunkCoord(int tileX, int tileY) {
        int chunkX = tileX >= 0 ? tileX / Chunk::CHUNK_SIZE : (tileX - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
        int chunkY = tileY >= 0 ? tileY / Chunk::CHUNK_SIZE : (tileY - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
        int localX = tileX - chunkX*Chunk::CHUNK_SIZE;
        int localY = tileY - chunkY*Chunk::CHUNK_SIZE;
        return {localX, localY};
    }

    std::tuple<int, int, unsigned char, unsigned char>
    TileMathHelper::tileCoordToChunkAndLocalChunkCoord(int tileX, int tileY) {
        int chunkX = tileX >= 0 ? tileX / Chunk::CHUNK_SIZE : (tileX - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
        int chunkY = tileY >= 0 ? tileY / Chunk::CHUNK_SIZE : (tileY - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
        int localX = tileX - chunkX*Chunk::CHUNK_SIZE;
        int localY = tileY - chunkY*Chunk::CHUNK_SIZE;
        return {chunkX, chunkY, localX, localY};
    }
}