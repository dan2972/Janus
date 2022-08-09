#ifndef JANUS_CHUNK_HPP
#define JANUS_CHUNK_HPP

#include <array>
#include "tile.hpp"

namespace Janus {
    class Chunk {
    public:
        const static short CHUNK_SIZE = 16;
        Chunk(int chunkX, int chunkY) : chunkX{chunkX}, chunkY(chunkY){
            for (unsigned char i = 0; i < CHUNK_SIZE; ++i) {
                for (unsigned char j = 0; j < CHUNK_SIZE; ++j) {
                    tileChunk[CHUNK_SIZE*i + j] = new Tile((j+chunkX*CHUNK_SIZE)*Tile::TILE_SIZE, (i+chunkY*CHUNK_SIZE)*Tile::TILE_SIZE);
                }
            }
        }
        ~Chunk() {
            for (unsigned char i = 0; i < CHUNK_SIZE; ++i) {
                for (unsigned char j = 0; j < CHUNK_SIZE; ++j) {
                    delete tileChunk[CHUNK_SIZE*i + j];
                }
            }
        }

        void tick() {
            for (unsigned char i = 0; i < CHUNK_SIZE; ++i) {
                for (unsigned char j = 0; j < CHUNK_SIZE; ++j) {
                    tileChunk[CHUNK_SIZE*i + j]->tick();
                }
            }
        }

        void render(float dt) {
            for (unsigned char i = 0; i < CHUNK_SIZE; ++i) {
                for (unsigned char j = 0; j < CHUNK_SIZE; ++j) {
                    tileChunk[CHUNK_SIZE*i + j]->render(dt);
                }
            }
        }

        Tile* getTileAt(unsigned char row, unsigned char col) {
            return tileChunk[CHUNK_SIZE*row + col];
        }

        std::array<Tile*, CHUNK_SIZE*CHUNK_SIZE>& getMap() {
            return tileChunk;
        }

        [[nodiscard]] int getChunkX() const { return chunkX; }

        [[nodiscard]] int getChunkY() const { return chunkY; }

    private:
        std::array<Tile*, CHUNK_SIZE*CHUNK_SIZE> tileChunk{nullptr};
        int chunkX, chunkY;
    };
}

#endif //JANUS_CHUNK_HPP
