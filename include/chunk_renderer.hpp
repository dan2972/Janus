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
        static void drawChunk(Chunk& chunk, GameCamera& camera);
        static void drawTile(const Tile& tile);

    private:
        static std::unordered_map<std::string, raylib::Texture2D> textureMap;
    };
}

#endif //JANUS_CHUNK_RENDERER_HPP
