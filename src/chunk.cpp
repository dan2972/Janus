#include "chunk.hpp"
#include "random_generator.hpp"

namespace Janus {
    Chunk::Chunk(int chunkX, int chunkY, Tilemap* tilemap) : chunkX{chunkX}, chunkY(chunkY){
        for (unsigned char i = 0; i < CHUNK_SIZE; ++i) {
            for (unsigned char j = 0; j < CHUNK_SIZE; ++j) {
                tileChunk[CHUNK_SIZE*i + j] = new Tile((j+chunkX*CHUNK_SIZE)*Tile::TILE_SIZE, (i+chunkY*CHUNK_SIZE)*Tile::TILE_SIZE, tilemap);
            }
        }
    }
    Chunk::~Chunk() {
        for (unsigned char i = 0; i < CHUNK_SIZE; ++i) {
            for (unsigned char j = 0; j < CHUNK_SIZE; ++j) {
                delete tileChunk[CHUNK_SIZE*i + j];
            }
        }
    }

    void Chunk::tick() {
        for (unsigned char i = 0; i < CHUNK_SIZE; ++i) {
            for (unsigned char j = 0; j < CHUNK_SIZE; ++j) {
                tileChunk[CHUNK_SIZE*i + j]->tick();
            }
        }
    }

    void Chunk::randomTick(unsigned short randomTickRate) {
        for (unsigned short k = 0; k < randomTickRate; ++k) {
            int row = RandomGenerator::randInt(0, Chunk::CHUNK_SIZE - 1);
            int col = RandomGenerator::randInt(0, Chunk::CHUNK_SIZE - 1);
            tileChunk[CHUNK_SIZE*row + col]->tick();
        }
    }

    void Chunk::render(float dt) {
        for (unsigned char i = 0; i < CHUNK_SIZE; ++i) {
            for (unsigned char j = 0; j < CHUNK_SIZE; ++j) {
                tileChunk[CHUNK_SIZE*i + j]->render(dt);
            }
        }
    }

    Tile& Chunk::getTileAt(unsigned char row, unsigned char col) {
        return *tileChunk[CHUNK_SIZE*row + col];
    }

    std::array<Tile*, Chunk::CHUNK_SIZE*Chunk::CHUNK_SIZE>& Chunk::getMap() {
        return tileChunk;
    }
}