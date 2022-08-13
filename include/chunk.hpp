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

        Tile& getTileAt(unsigned char x, unsigned char y);
        std::array<std::unique_ptr<Tile>, CHUNK_SIZE*CHUNK_SIZE>& getMap();

        void requestTextureUpdate() { updateTexture = true; }
        void finishUpdatingTexture() { updateTexture = false; }

        [[nodiscard]] int getChunkX() const { return chunkX; }
        [[nodiscard]] int getChunkY() const { return chunkY; }
        [[nodiscard]] bool updateTextureRequested() const { return updateTexture; }

    private:
        std::array<std::unique_ptr<Tile>, CHUNK_SIZE*CHUNK_SIZE> tileChunk{nullptr};
        int chunkX, chunkY;
        bool updateTexture = false;
    };
}

#endif //JANUS_CHUNK_HPP
