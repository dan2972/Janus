#ifndef JANUS_CHUNK_HPP
#define JANUS_CHUNK_HPP

#include <array>
#include <vector>
#include "tile_data.hpp"

namespace Janus {
    struct ChunkCoord{
        ChunkCoord(int x, int y) : x{x}, y{y} {}
        int x, y;
    };

    struct HashFunc{
        size_t  operator()(const ChunkCoord &c) const{
            size_t h1 = std::hash<int>()(c.x);
            size_t h2 = std::hash<int>()(c.y);
            return (h1 ^ (h2 << 1));
        }
    };

    struct EqualsFunc{
        bool operator()(const ChunkCoord& lhs, const ChunkCoord& rhs) const {
            return (lhs.x == rhs.x) && (lhs.y == rhs.y);
        }
    };

    struct TextureUpdateData {
        bool requested = false;
        bool waiting = false;
        bool isHighPriority = false;
    };

    class Chunk {
    public:
        static const unsigned short CHUNK_SIZE = 16;

        Chunk(int chunkX, int chunkY);

        std::array<std::unique_ptr<GroundTile>, CHUNK_SIZE*CHUNK_SIZE>& getGroundTileMap() { return groundTileMap; }
        std::array<std::unique_ptr<ObjectTile>, CHUNK_SIZE*CHUNK_SIZE>& getObjectTileMap() { return objectTileMap; }

        void replaceGroundTileAt(unsigned short x, unsigned short y, GroundTileID id);
        void replaceObjectTileAt(unsigned short x, unsigned short y, ObjectTileID id);
        void replaceGroundTileAt(unsigned short x, unsigned short y, GroundTile* groundTile);
        void replaceObjectTileAt(unsigned short x, unsigned short y, ObjectTile* objectTile);

        [[nodiscard]] GroundTile& getGroundTileAt(unsigned short x, unsigned short y) const;
        [[nodiscard]] ObjectTile& getObjectTileAt(unsigned short x, unsigned short y) const;

        [[nodiscard]] int getChunkX() const { return chunkX; }
        [[nodiscard]] int getChunkY() const { return chunkY; }

        [[nodiscard]] bool updateTextureRequested() const { return textureUpdateData.requested; }
        [[nodiscard]] bool isWaitingForTextureUpdate() const { return textureUpdateData.waiting; }
        [[nodiscard]] bool textureUpdateIsHighPriority() const {return textureUpdateData.isHighPriority; }

        void requestTextureUpdate(bool isHighPriority = false);
        void finishUpdatingTexture() { textureUpdateData.requested = false; }
        void waitForTextureUpdate() { textureUpdateData.waiting = true; }
        void clearWaitingForTextureUpdate() { textureUpdateData.waiting = false; }
        void resetTextureUpdatePriority() { textureUpdateData.isHighPriority = false; }

    private:
        std::array<std::unique_ptr<GroundTile>, CHUNK_SIZE*CHUNK_SIZE> groundTileMap{};
        std::array<std::unique_ptr<ObjectTile>, CHUNK_SIZE*CHUNK_SIZE> objectTileMap{};

        int chunkX, chunkY;
        TextureUpdateData textureUpdateData;
    };
}

#endif //JANUS_CHUNK_HPP
