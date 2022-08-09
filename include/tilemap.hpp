#ifndef JANUS_TILEMAP_HPP
#define JANUS_TILEMAP_HPP

#include <unordered_map>
#include <string>
#include "tile.hpp"
#include "chunk.hpp"
#include "random_generator.hpp"

namespace Janus {
    class Tilemap {
    public:
        Tilemap() = default;
        ~Tilemap();

        void addChunk(Chunk* chunk);
        void tickChunk(int chunkX, int chunkY);
        void renderChunk(int chunkX, int chunkY, float dt);
        void renderChunkAroundCoord(int centerX, int centerY, int radius, float dt);

        void clearRandomTickList();
        void addChunkToRandomTickList(int chunkX, int chunkY);
        void addChunksToRandomTickList(int centerX, int centerY, int radius);
        void randomTick(unsigned short randomTickRate);

        bool chunkExistsAt(int chunkX, int chunkY);
        Chunk* getChunk(int chunkX, int chunkY);
        Chunk* getChunk(const std::string& key);

        std::unordered_map<std::string, Chunk*>& getChunkMap();

        [[nodiscard]] unsigned int getRandomTickChunkSize() const { return randomTickChunks.size(); }

    private:
        std::unordered_map<std::string, Chunk*> chunkMap;
        std::vector<std::string> randomTickChunks;
    };
}

#endif //JANUS_TILEMAP_HPP
