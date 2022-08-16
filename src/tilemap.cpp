#include "tilemap.hpp"
#include "chunk.hpp"
#include "tile_math_helper.hpp"

namespace Janus {
    void Tilemap::tick() {
        while(!tileTickScheduleQueue.empty()) {
            tileTickSchedule.push_back(tileTickScheduleQueue.front());
            tileTickScheduleQueue.pop();
        }
        auto it = tileTickSchedule.begin();
        while (it != tileTickSchedule.end()) {
            if (it->second == 0) {
                it->first.get().scheduledTick();
                it = tileTickSchedule.erase(it);
            } else {
                --it->second;
                ++it;
            }
        }
    }

    void Tilemap::addChunk(Chunk* chunk) {
        chunkMap.insert({std::to_string(chunk->getChunkX()) + "," + std::to_string(chunk->getChunkY()), std::unique_ptr<Chunk>(chunk)});
    }

    void Tilemap::tickChunk(int chunkX, int chunkY) {
        getChunk(chunkX, chunkY)->tick();
    }

    void Tilemap::clearRandomTickList() {
        randomTickChunks.clear();
    }

    void Tilemap::addChunkToRandomTickList(int chunkX, int chunkY) {
        std::string key = std::to_string(chunkX) + "," + std::to_string(chunkY);
        if (std::find(randomTickChunks.begin(), randomTickChunks.end(), key) == randomTickChunks.end()) {
            randomTickChunks.push_back(key);
        }
    }

    void Tilemap::addChunksToRandomTickList(int centerX, int centerY, int radius) {
        for (int i = centerY - radius; i <= centerY + radius; ++i) {
            for (int j = centerX - radius; j <= centerX + radius; ++j) {
                std::string key = std::to_string(j) + "," + std::to_string(i);
                if (std::find(randomTickChunks.begin(), randomTickChunks.end(), key) == randomTickChunks.end()) {
                    randomTickChunks.push_back(key);
                }
            }
        }
    }

    void Tilemap::randomTick(unsigned short randomTickRate) {
        for (const std::string& key : randomTickChunks) {
            Chunk *chunk = getChunk(key);
            if (chunk != nullptr) chunk->randomTick(randomTickRate);
        }
    }

    void Tilemap::scheduleTileTick(Tile& tile, unsigned int delay) {
        tileTickScheduleQueue.push({std::ref(tile), (int)delay});
    }

    bool Tilemap::chunkExistsAt(int chunkX, int chunkY) {
        std::string key = std::to_string(chunkX) + "," + std::to_string(chunkY);
        auto it = chunkMap.find(key);
        if (it != chunkMap.end()) {
            return true;
        }
        return false;
    }

    Chunk* Tilemap::getChunk(int chunkX, int chunkY) {
        std::string key = std::to_string(chunkX) + "," + std::to_string(chunkY);
        auto it = chunkMap.find(key);
        if (it != chunkMap.end()) {
            return chunkMap.at(key).get();
        }
        return nullptr;
    }

    Chunk* Tilemap::getChunk(const std::string& key) {
        auto it = chunkMap.find(key);
        if (it != chunkMap.end()) {
            return chunkMap.at(key).get();
        }
        return nullptr;
    }

    Tile* Tilemap::getTileAt(int tileX, int tileY) {
        auto [chunkX, chunkY, localX, localY] = TileMathHelper::tileCoordToChunkAndLocalChunkCoord(tileX, tileY);
        Chunk* chunk = getChunk(chunkX, chunkY);
        if (chunk != nullptr) {
            return &chunk->getTileAt(localX, localY);
        }
        return nullptr;
    }

    void Tilemap::replaceTileAt(int tileX, int tileY, Tile* tile) {
        auto [chunkX, chunkY, localX, localY] = TileMathHelper::tileCoordToChunkAndLocalChunkCoord(tileX, tileY);
        Chunk* chunk = getChunk(chunkX, chunkY);
        if (chunk != nullptr) {
            removeTileFromSchedule(chunk->getTileAt(localX, localY));
            chunk->getMap()[Chunk::CHUNK_SIZE*localY + localX].reset(tile);
            chunk->requestTextureUpdate();

            if (localX == 0) {
                if(getChunk(chunkX-1, chunkY) != nullptr)
                    getChunk(chunkX-1, chunkY)->requestTextureUpdate();
            }
            if (localY == 0) {
                if(getChunk(chunkX, chunkY-1) != nullptr)
                    getChunk(chunkX, chunkY-1)->requestTextureUpdate();
            }
            if (localX == Chunk::CHUNK_SIZE-1) {
                if(getChunk(chunkX+1, chunkY) != nullptr)
                    getChunk(chunkX+1, chunkY)->requestTextureUpdate();
            }
            if (localY == Chunk::CHUNK_SIZE-1) {
                if(getChunk(chunkX, chunkY+1) != nullptr)
                    getChunk(chunkX, chunkY+1)->requestTextureUpdate();
            }
        }
    }

    std::vector<std::reference_wrapper<Tile>> Tilemap::getTilesInRange(int x1, int y1, int x2, int y2) {
        std::vector<std::reference_wrapper<Tile>> output;
        for (int i = y1; i <= y2; ++i) {
            for (int j = x1; j <= x2; ++j) {
                int chunkX = j >= 0 ? j / Chunk::CHUNK_SIZE : (j - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
                int chunkY = i >= 0 ? i / Chunk::CHUNK_SIZE : (i - Chunk::CHUNK_SIZE+1) / Chunk::CHUNK_SIZE;
                Chunk* chunk = getChunk(chunkX, chunkY);
                if (chunk != nullptr) {
                    int tileX = j - chunkX*Chunk::CHUNK_SIZE;
                    int tileY = i - chunkY*Chunk::CHUNK_SIZE;
                    output.emplace_back(chunk->getTileAt(tileX, tileY));
                }
            }
        }
        return output;
    }

    std::unordered_map<std::string, std::unique_ptr<Chunk>>& Tilemap::getChunkMap(){
        return chunkMap;
    }

    void Tilemap::removeTileFromSchedule(Tile& tile) {
        while(!tileTickScheduleQueue.empty()) {
            tileTickSchedule.push_back(tileTickScheduleQueue.front());
            tileTickScheduleQueue.pop();
        }
        auto it = tileTickSchedule.begin();
        while (it != tileTickSchedule.end()) {
            if (&(it->first.get()) == &tile) {
                it = tileTickSchedule.erase(it);
            } else {
                ++it;
            }
        }
    }
}