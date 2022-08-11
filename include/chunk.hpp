#ifndef JANUS_CHUNK_HPP
#define JANUS_CHUNK_HPP

#include <array>
#include "tile.hpp"
#include "tilemap.hpp"

namespace Janus {
    class Chunk {
    public:
        const static short CHUNK_SIZE = 16;
        Chunk(int chunkX, int chunkY, Tilemap* tilemap);

        void tick();
        void randomTick(unsigned short randomTickRate);

        Tile& getTileAt(unsigned char row, unsigned char col);
        std::array<std::unique_ptr<Tile>, CHUNK_SIZE*CHUNK_SIZE>& getMap();

        [[nodiscard]] int getChunkX() const { return chunkX; }
        [[nodiscard]] int getChunkY() const { return chunkY; }

    private:
        std::array<std::unique_ptr<Tile>, CHUNK_SIZE*CHUNK_SIZE> tileChunk{nullptr};
        int chunkX, chunkY;
    };
}

#endif //JANUS_CHUNK_HPP
