#include "chunk.hpp"

namespace Janus {
    Chunk::Chunk(int chunkX, int chunkY) : chunkX{chunkX}, chunkY(chunkY){
        for (unsigned char i = 0; i < CHUNK_SIZE; ++i) {
            for (unsigned char j = 0; j < CHUNK_SIZE; ++j) {
                tileChunk[CHUNK_SIZE*i + j] = new Tile((j+chunkX*CHUNK_SIZE)*Tile::TILE_SIZE, (i+chunkY*CHUNK_SIZE)*Tile::TILE_SIZE);
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