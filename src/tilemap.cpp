#include "tilemap.hpp"
#include "tile_math_helper.hpp"

namespace Janus {

    void Tilemap::addChunk(Chunk *chunk) {
        chunkMap.insert({ChunkCoord{chunk->getChunkX(), chunk->getChunkY()}, std::unique_ptr<Chunk>(chunk)});
    }

    void Tilemap::loadChunks(int centerChunkX, int centerChunkY, int radius) {
        for (int i = centerChunkY - radius; i <= centerChunkY + radius; ++i) {
            for (int j = centerChunkX - radius; j <= centerChunkX + radius; ++j) {
                if (!chunkExistsAt(j, i)) {
                    addChunk(new Chunk(j, i));
                }
            }
        }
    }

    void Tilemap::replaceGroundTileAt(int x, int y, GroundTileID id) {
        auto[chunkX, chunkY, lx, ly] = TileMathHelper::tileCoordToChunkAndLocalChunkCoord(x, y);
        Chunk* chunk = getChunkAt(chunkX, chunkY);
        if (chunk != nullptr) {
            chunk->replaceGroundTileAt(lx, ly, id);
            chunk->requestTextureUpdate(true);
        }
    }

    void Tilemap::replaceGroundTileAt(int x, int y, GroundTile* gt) {
        auto[chunkX, chunkY, lx, ly] = TileMathHelper::tileCoordToChunkAndLocalChunkCoord(x, y);
        Chunk* chunk = getChunkAt(chunkX, chunkY);
        if (chunk != nullptr) {
            chunk->replaceGroundTileAt(lx, ly, gt);
            chunk->requestTextureUpdate(true);
        }
    }

    void Tilemap::replaceObjectTileAt(int x, int y, ObjectTileID id) {
        auto[chunkX, chunkY, lx, ly] = TileMathHelper::tileCoordToChunkAndLocalChunkCoord(x, y);
        Chunk* chunk = getChunkAt(chunkX, chunkY);
        if (chunk != nullptr) {
            chunk->replaceObjectTileAt(lx, ly, id);
            chunk->requestTextureUpdate(true);
            updateChunkTexturesAroundTile(chunkX, chunkY, lx, ly);
        }
    }

    void Tilemap::replaceObjectTileAt(int x, int y, ObjectTile* ot) {
        auto[chunkX, chunkY, lx, ly] = TileMathHelper::tileCoordToChunkAndLocalChunkCoord(x, y);
        Chunk* chunk = getChunkAt(chunkX, chunkY);
        if (chunk != nullptr) {
            chunk->replaceObjectTileAt(lx, ly, ot);
            chunk->requestTextureUpdate(true);
            updateChunkTexturesAroundTile(chunkX, chunkY, lx, ly);
        }
    }

    bool Tilemap::chunkExistsAt(int chunkX, int chunkY) const {
        auto it = chunkMap.find({chunkX, chunkY});
        if (it != chunkMap.end()) {
            return true;
        }
        return false;
    }

    Chunk* Tilemap::getChunkAt(int chunkX, int chunkY) const {
        auto it = chunkMap.find({chunkX, chunkY});
        if (it != chunkMap.end()) {
            return chunkMap.at({chunkX, chunkY}).get();
        }
        return nullptr;
    }

    GroundTile* Tilemap::getGroundTileAt(int x, int y) const {
        auto[chunkX, chunkY, lx, ly] = TileMathHelper::tileCoordToChunkAndLocalChunkCoord(x, y);
        Chunk* chunk = getChunkAt(chunkX, chunkY);
        if (chunk != nullptr) {
            return &chunk->getGroundTileAt(lx, ly);
        }
        return nullptr;//GroundTileID::NONE;
    }

    ObjectTile* Tilemap::getObjectTileAt(int x, int y) const {
        auto[chunkX, chunkY, lx, ly] = TileMathHelper::tileCoordToChunkAndLocalChunkCoord(x, y);
        Chunk* chunk = getChunkAt(chunkX, chunkY);
        if (chunk != nullptr) {
            return &chunk->getObjectTileAt(lx, ly);
        }
        return nullptr;
    }

    std::vector<std::reference_wrapper<ObjectTile>> Tilemap::getObjectTilesInRange(int x1, int y1, int x2, int y2) const {
        std::vector<std::reference_wrapper<ObjectTile>> output;
        for (int i = y1; i <= y2; ++i) {
            for (int j = x1; j <= x2; ++j) {
                auto [chunkX, chunkY] = TileMathHelper::tileCoordToChunk(j, i);
                Chunk* chunk = getChunkAt(chunkX, chunkY);
                if (chunk != nullptr) {
                    int tileX = j - chunkX*Chunk::CHUNK_SIZE;
                    int tileY = i - chunkY*Chunk::CHUNK_SIZE;
                    output.emplace_back(chunk->getObjectTileAt(tileX, tileY));
                }
            }
        }
        return output;
    }

    void Tilemap::updateChunkTexturesAroundTile(int chunkX, int chunkY, int localX, int localY) {
        if (localX == 0) {
            if(getChunkAt(chunkX-1, chunkY) != nullptr)
                getChunkAt(chunkX-1, chunkY)->requestTextureUpdate(true);
            if (localY == 0) {
                if(getChunkAt(chunkX-1, chunkY-1) != nullptr)
                    getChunkAt(chunkX-1, chunkY-1)->requestTextureUpdate(true);
            } else if (localY == Chunk::CHUNK_SIZE-1) {
                if(getChunkAt(chunkX-1, chunkY+1) != nullptr)
                    getChunkAt(chunkX-1, chunkY+1)->requestTextureUpdate(true);
            }
        } else if (localX == Chunk::CHUNK_SIZE-1) {
            if (getChunkAt(chunkX+1, chunkY) != nullptr)
                getChunkAt(chunkX+1, chunkY)->requestTextureUpdate(true);
            if (localY == 0) {
                if(getChunkAt(chunkX+1, chunkY-1) != nullptr)
                    getChunkAt(chunkX+1, chunkY-1)->requestTextureUpdate(true);
            } else if (localY == Chunk::CHUNK_SIZE-1) {
                if(getChunkAt(chunkX+1, chunkY+1) != nullptr)
                    getChunkAt(chunkX+1, chunkY+1)->requestTextureUpdate(true);
            }
        }
        if (localY == 0) {
            if (getChunkAt(chunkX, chunkY-1) != nullptr)
                getChunkAt(chunkX, chunkY-1)->requestTextureUpdate(true);
        } else if (localY == Chunk::CHUNK_SIZE-1) {
            if (getChunkAt(chunkX, chunkY+1) != nullptr)
                getChunkAt(chunkX, chunkY+1)->requestTextureUpdate(true);
        }
    }

}