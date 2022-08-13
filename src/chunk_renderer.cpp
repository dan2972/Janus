#include "chunk_renderer.hpp"
#include "ground_tile.hpp"
#include "tile_math_helper.hpp"
#include "game.hpp"

namespace Janus {
    std::unordered_map<std::string, raylib::Texture2D> ChunkRenderer::textureMap;

    void ChunkRenderer::drawChunk(Chunk& chunk, GameCamera& camera) {
        std::string key = std::to_string(chunk.getChunkX()) + "," + std::to_string(chunk.getChunkY());
        if (chunk.updateTextureRequested()) {
            raylib::RenderTexture2D target{Chunk::CHUNK_SIZE * Tile::TILE_SIZE, Chunk::CHUNK_SIZE * Tile::TILE_SIZE};

            auto it = textureMap.find(key);
            if (it != textureMap.end()) {
                textureMap.erase(it);
            }

            camera.end();

            target.BeginMode();
            ClearBackground(WHITE);
            for (auto& tile : chunk.getMap()) {
                drawTile(*tile);
            }
            target.EndMode();

            camera.start();

            raylib::Image image{target.GetTexture()};
            textureMap.insert({key, raylib::Texture2D{image}});
            target.Unload();
        }

        raylib::Texture2D& texture = textureMap.at(key);
        texture.Draw({0, 0, (float)texture.width, -(float)texture.height},
                     {(float)chunk.getChunkX() * Tile::TILE_SIZE * Chunk::CHUNK_SIZE,
                      (float)chunk.getChunkY() * Tile::TILE_SIZE * Chunk::CHUNK_SIZE},
                     WHITE);
        chunk.finishUpdatingTexture();
    }

    void ChunkRenderer::drawTile(const Tile &tile) {
        auto [localX, localY] = TileMathHelper::tileCoordToLocalChunkCoord(tile.getPos().x / Tile::TILE_SIZE,
                                                                           tile.getPos().y / Tile::TILE_SIZE);
        int tileX = (int)localX * Tile::TILE_SIZE;
        int tileY = (int)localY * Tile::TILE_SIZE;
        if (tile.getTileType() == Tile::TileType::GROUND) {
            auto& gt = (GroundTile&) tile;
            if (gt.getGroundTileType() == GroundTile::GRASS)
                DrawRectangle(tileX, tileY, gt.TILE_SIZE, gt.TILE_SIZE, {120,170,100,255});
            else if (gt.getGroundTileType() == GroundTile::WATER)
                DrawRectangle(tileX, tileY, gt.TILE_SIZE, gt.TILE_SIZE, {80,150,205,255});
            else if (gt.getGroundTileType() == GroundTile::SAND)
                DrawRectangle(tileX, tileY, gt.TILE_SIZE, gt.TILE_SIZE, {195,185,120,255});
            else if (gt.getGroundTileType() == GroundTile::STONE)
                DrawRectangle(tileX, tileY, gt.TILE_SIZE, gt.TILE_SIZE, GRAY);
        } else if (tile.getTileType() == Tile::TileType::OBJECT) {
            DrawRectangle(tileX, tileY, tile.TILE_SIZE, tile.TILE_SIZE, DARKGRAY);
        }
    }
}