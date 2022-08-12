#include "chunk.hpp"
#include "random_generator.hpp"
#include "ground_tile.hpp"
#include "object_tile.hpp"
#include "noise/perlin_generator.hpp"

namespace Janus {
    Chunk::Chunk(int chunkX, int chunkY, Tilemap* tilemap) : chunkX{chunkX}, chunkY(chunkY){
        for (unsigned char i = 0; i < CHUNK_SIZE; ++i) {
            for (unsigned char j = 0; j < CHUNK_SIZE; ++j) {
                float p = 1.0f-PerlinGenerator::getValueAt(chunkX * CHUNK_SIZE + j, chunkY * CHUNK_SIZE+i, 0.03);
                if (p <= 0.15f) {
                    tileChunk[CHUNK_SIZE * i + j] = std::unique_ptr<Tile>(
                            new GroundTile(
                                    (float) (j + chunkX * CHUNK_SIZE) * Tile::TILE_SIZE,
                                    (float) (i + chunkY * CHUNK_SIZE) * Tile::TILE_SIZE,
                                    GroundTile::GroundTileType::WATER, tilemap)
                    );
                } else if (p <= 0.2f) {
                    tileChunk[CHUNK_SIZE * i + j] = std::unique_ptr<Tile>(
                            new GroundTile(
                                    (float) (j + chunkX * CHUNK_SIZE) * Tile::TILE_SIZE,
                                    (float) (i + chunkY * CHUNK_SIZE) * Tile::TILE_SIZE,
                                    GroundTile::GroundTileType::SAND, tilemap)
                    );
                } else if (p <= 0.6f) {
                    tileChunk[CHUNK_SIZE * i + j] = std::unique_ptr<Tile>(
                            new GroundTile(
                                    (float) (j + chunkX * CHUNK_SIZE) * Tile::TILE_SIZE,
                                    (float) (i + chunkY * CHUNK_SIZE) * Tile::TILE_SIZE,
                                    tilemap)
                    );
                } else if (p <= 0.63f) {
                    tileChunk[CHUNK_SIZE * i + j] = std::unique_ptr<Tile>(
                            new GroundTile(
                                    (float) (j + chunkX * CHUNK_SIZE) * Tile::TILE_SIZE,
                                    (float) (i + chunkY * CHUNK_SIZE) * Tile::TILE_SIZE,
                                    GroundTile::GroundTileType::STONE, tilemap)
                    );
                } else {
                    tileChunk[CHUNK_SIZE * i + j] = std::unique_ptr<Tile>(
                            new ObjectTile(
                                    (float) (j + chunkX * CHUNK_SIZE) * Tile::TILE_SIZE,
                                    (float) (i + chunkY * CHUNK_SIZE) * Tile::TILE_SIZE,
                                    tilemap)
                    );
                }
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

    Tile& Chunk::getTileAt(unsigned char x, unsigned char y) {
        return *tileChunk[CHUNK_SIZE*y + x];
    }

    std::array<std::unique_ptr<Tile>, Chunk::CHUNK_SIZE*Chunk::CHUNK_SIZE>& Chunk::getMap() {
        return tileChunk;
    }
}