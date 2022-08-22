#ifndef JANUS_TILEMAP_HPP
#define JANUS_TILEMAP_HPP

#include <unordered_map>
#include "chunk.hpp"

namespace Janus {
    class Tilemap{
    public:
        Tilemap() = default;

        void addChunk(Chunk* chunk);
        void loadChunks(int centerChunkX, int centerChunkY, int radius);
        void replaceGroundTileAt(int x, int y, GroundTileID id);
        void replaceObjectTileAt(int x, int y, ObjectTileID id);
        void replaceGroundTileAt(int x, int y, GroundTile* ot);
        void replaceObjectTileAt(int x, int y, ObjectTile* ot);

        [[nodiscard]] bool chunkExistsAt(int chunkX, int chunkY) const;
        [[nodiscard]] Chunk* getChunkAt(int chunkX, int chunkY) const;
        [[nodiscard]] GroundTile* getGroundTileAt(int x, int y) const;
        [[nodiscard]] ObjectTile* getObjectTileAt(int x, int y) const;
        [[nodiscard]] std::vector<std::reference_wrapper<ObjectTile>>
            getObjectTilesInRange(int x1, int y1, int x2, int y2) const;

    private:
        void updateChunkTexturesAroundTile(int chunkX, int chunkY, int localX, int localY);

        std::unordered_map<ChunkCoord, std::unique_ptr<Chunk>, HashFunc, EqualsFunc> chunkMap;
    };
}

#endif //JANUS_TILEMAP_HPP
