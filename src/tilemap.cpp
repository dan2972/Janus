#include "tilemap.hpp"

namespace Janus {

    Tilemap::~Tilemap() {
        for (auto& it : chunkMap) {
            delete it.second;
        }
    }

    void Tilemap::addChunk(Chunk* chunk) {
        chunkMap.insert({std::to_string(chunk->getChunkX()) + "," + std::to_string(chunk->getChunkY()), chunk});
    }

    void Tilemap::tickChunk(int chunkX, int chunkY) {
        getChunk(chunkX, chunkY)->tick();
    }

    void Tilemap::renderChunk(int chunkX, int chunkY, float dt) {
        getChunk(chunkX, chunkY)->render(dt);
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
            for (unsigned short k = 0; k < randomTickRate; ++k) {
                Chunk *chunk = getChunk(key);
                if (chunk != nullptr) {
                    int row = RandomGenerator::randInt(0, Chunk::CHUNK_SIZE - 1);
                    int col = RandomGenerator::randInt(0, Chunk::CHUNK_SIZE - 1);
                    chunk->getTileAt(row, col).tick();
                }
            }
        }
    }

    void Tilemap::renderChunkAroundCoord(int centerX, int centerY, int radius, float dt) {
        for (int i = centerY - radius; i <= centerY + radius; ++i) {
            for (int j = centerX - radius; j <= centerX + radius; ++j) {
                Chunk* chunk = getChunk(j, i);
                if (chunk != nullptr) chunk->render(dt);
            }
        }
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
            return chunkMap.at(key);
        }
        return nullptr;
    }

    Chunk* Tilemap::getChunk(const std::string& key) {
        auto it = chunkMap.find(key);
        if (it != chunkMap.end()) {
            return chunkMap.at(key);
        }
        return nullptr;
    }

    std::unordered_map<std::string, Chunk*>& Tilemap::getChunkMap(){
        return chunkMap;
    }
}