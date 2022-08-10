#ifndef JANUS_TILEMAP_HPP
#define JANUS_TILEMAP_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include <queue>

namespace Janus {
    class Tile;
    class Chunk;
    class Tilemap {
    public:
        Tilemap() = default;
        ~Tilemap();

        void tick();

        void addChunk(Chunk* chunk);
        void tickChunk(int chunkX, int chunkY);

        void clearRandomTickList();
        void addChunkToRandomTickList(int chunkX, int chunkY);
        void addChunksToRandomTickList(int centerX, int centerY, int radius);
        void randomTick(unsigned short randomTickRate);

        void scheduleTileTick(Tile& tile, unsigned int delay);

        bool chunkExistsAt(int chunkX, int chunkY);
        Chunk* getChunk(int chunkX, int chunkY);
        Chunk* getChunk(const std::string& key);

        std::unordered_map<std::string, Chunk*>& getChunkMap();

        [[nodiscard]] unsigned int getRandomTickChunkSize() const { return randomTickChunks.size(); }

    private:
        std::unordered_map<std::string, Chunk*> chunkMap;
        std::vector<std::string> randomTickChunks;
        struct tileTickSchedulePair {
            Tile* tile;
            int ticksLeft;
        };
        std::vector<tileTickSchedulePair> tileTickSchedule;
        std::queue<tileTickSchedulePair> tileTickScheduleQueue;
    };
}

#endif //JANUS_TILEMAP_HPP
