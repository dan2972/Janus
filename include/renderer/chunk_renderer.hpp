#ifndef JANUS_CHUNK_RENDERER_HPP
#define JANUS_CHUNK_RENDERER_HPP

#include <raylib.h>
#include <unordered_map>
#include "chunk.hpp"
#include "tilemap.hpp"
#include "game_camera.hpp"

namespace Janus {
    class ChunkRenderer {
    public:
        static void unload();
        static void loadChunk(Tilemap& tilemap, Chunk& chunk, GameCamera& camera);
        static void drawChunk(Tilemap& tilemap, Chunk& chunk, GameCamera& camera);
    private:
        static void drawTile(Tilemap& tilemap, const GroundTile& gt, const ObjectTile& ot);
        static void drawGroundTile(Tilemap& tilemap, const GroundTile& gt, int x, int y);
        static void drawObjectTile(Tilemap& tilemap, const ObjectTile& ot, int x, int y);

        static std::unordered_map<ChunkCoord, Texture2D, HashFunc, EqualsFunc> textureMap;
    };
}

#endif //JANUS_CHUNK_RENDERER_HPP
