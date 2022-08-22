#include "chunk.hpp"

#include <memory>
#include "noise/perlin_generator.hpp"

namespace Janus {
    Chunk::Chunk(int chunkX, int chunkY) : chunkX{chunkX}, chunkY{chunkY} {
        requestTextureUpdate();
        for (unsigned short i = 0; i < CHUNK_SIZE; ++i) {
            for (unsigned short j = 0; j < CHUNK_SIZE; ++j) {
                /*
                float p = 1.0f-PerlinGenerator::getValueAt(chunkX*CHUNK_SIZE+j, chunkY*CHUNK_SIZE+i, 0.03, 4);
                replaceObjectTileAt(j, i, ObjectTileID::AIR);
                if (p <= 0.15f) {
                    replaceGroundTileAt(j, i, GroundTileID::WATER);
                } else if (p <= 0.2f) {
                    replaceGroundTileAt(j, i, GroundTileID::SAND);
                } else if (p <= 0.6f) {
                    replaceGroundTileAt(j, i, GroundTileID::GRASS);
                } else if (p <= 0.63f) {
                    replaceGroundTileAt(j, i, GroundTileID::STONE);
                } else {
                    replaceGroundTileAt(j, i, GroundTileID::STONE);
                    replaceObjectTileAt(j, i, ObjectTileID::STONE);
                }*/
                float p = 1.0f-PerlinGenerator::getValueAt(chunkX*CHUNK_SIZE+j, chunkY*CHUNK_SIZE+i, 0.02, 6);
                replaceObjectTileAt(j, i, ObjectTileID::AIR);
                if (p <= 0.35f) {
                    replaceGroundTileAt(j, i, GroundTileID::WATER);
                } else if (p <= 0.38f) {
                    replaceGroundTileAt(j, i, GroundTileID::SAND);
                } else if (p <= 0.68f) {
                    replaceGroundTileAt(j, i, GroundTileID::GRASS);
                } else if (p <= 0.72f) {
                    replaceGroundTileAt(j, i, GroundTileID::STONE);
                } else {
                    replaceGroundTileAt(j, i, GroundTileID::STONE);
                    replaceObjectTileAt(j, i, ObjectTileID::STONE);
                }
            }
        }
    }

    GroundTile& Chunk::getGroundTileAt(unsigned short x, unsigned short y) const {
        return *groundTileMap[y*CHUNK_SIZE + x];
    }

    ObjectTile& Chunk::getObjectTileAt(unsigned short x, unsigned short y) const {
        return *objectTileMap[y*CHUNK_SIZE + x];
    }

    void Chunk::replaceGroundTileAt(unsigned short x, unsigned short y, GroundTileID id) {
        switch(id) {
            default:
                groundTileMap[y*CHUNK_SIZE + x] = std::make_unique<GroundTile>(GroundTile{id});
        }
    }

    void Chunk::replaceObjectTileAt(unsigned short x, unsigned short y, ObjectTileID id) {
        int tileX = chunkX * CHUNK_SIZE + x;
        int tileY = chunkY * CHUNK_SIZE + y;
        switch(id) {
            default:
                objectTileMap[y*CHUNK_SIZE + x] = std::make_unique<ObjectTile>(ObjectTile{id, tileX, tileY});
        }
    }

    void Chunk::replaceGroundTileAt(unsigned short x, unsigned short y, GroundTile* groundTile) {
        groundTileMap[y*CHUNK_SIZE + x].reset(groundTile);
    }

    void Chunk::replaceObjectTileAt(unsigned short x, unsigned short y, ObjectTile* objectTile) {
        objectTileMap[y*CHUNK_SIZE + x].reset(objectTile);
    }

    void Chunk::requestTextureUpdate(bool isHighPriority) {
        textureUpdateData.requested = true;
        textureUpdateData.isHighPriority = isHighPriority;
    }
}