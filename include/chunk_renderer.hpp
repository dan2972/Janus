#ifndef JANUS_CHUNK_RENDERER_HPP
#define JANUS_CHUNK_RENDERER_HPP

#include <unordered_map>
#include <raylib-cpp.hpp>
#include <string>
#include "chunk.hpp"
#include "game_camera.hpp"

namespace Janus {
    class ChunkRenderer {
    public:
        static void loadChunk(Tilemap& tilemap, Chunk& chunk, GameCamera& camera);
        static void drawChunk(Tilemap& tilemap, Chunk& chunk, GameCamera& camera);
        static void drawTile(Tilemap& tilemap, const Tile& tile);

    private:
        static std::unordered_map<std::string, raylib::Texture2D> textureMap;
    };
}

#endif //JANUS_CHUNK_RENDERER_HPP
