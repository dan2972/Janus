#include "chunk_renderer.hpp"
#include "ground_tile.hpp"
#include "tile_math_helper.hpp"
#include "game.hpp"
#include "wall_tile_renderer.hpp"

namespace Janus {
    std::unordered_map<std::string, raylib::Texture2D> ChunkRenderer::textureMap;

    void ChunkRenderer::loadChunk(Tilemap &tilemap, Chunk &chunk, GameCamera &camera) {
        std::string key = std::to_string(chunk.getChunkX()) + "," + std::to_string(chunk.getChunkY());
        raylib::RenderTexture2D target{Chunk::CHUNK_SIZE * Tile::TILE_SIZE, Chunk::CHUNK_SIZE * Tile::TILE_SIZE};

        auto it = textureMap.find(key);
        if (it != textureMap.end()) {
            textureMap.erase(it);
        }

        camera.end();

        target.BeginMode();
        ClearBackground(WHITE);
        for (auto& tile : chunk.getMap()) {
            drawTile(tilemap, *tile);
        }
        target.EndMode();

        camera.start();

        raylib::Image image{target.GetTexture()};
        textureMap.insert({key, raylib::Texture2D{image}});
        target.Unload();

        chunk.finishUpdatingTexture();
    }

    void ChunkRenderer::drawChunk(Tilemap& tilemap, Chunk& chunk, GameCamera& camera) {
        if (chunk.updateTextureRequested()) {
            loadChunk(tilemap, chunk, camera);
        }

        std::string key = std::to_string(chunk.getChunkX()) + "," + std::to_string(chunk.getChunkY());

        raylib::Texture2D& texture = textureMap.at(key);
        texture.Draw({0, 0, (float)texture.width, -(float)texture.height},
                     {(float)chunk.getChunkX() * Tile::TILE_SIZE * Chunk::CHUNK_SIZE,
                      (float)chunk.getChunkY() * Tile::TILE_SIZE * Chunk::CHUNK_SIZE},
                     WHITE);
    }

    void ChunkRenderer::drawTile(Tilemap& tilemap, const Tile &tile) {
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
            auto& ot = (ObjectTile&) tile;
            if (ot.getObjectTileType() == ObjectTile::WALL) {
                WallTileRenderer::drawWall(tilemap, ot);
            }
        }
    }
}