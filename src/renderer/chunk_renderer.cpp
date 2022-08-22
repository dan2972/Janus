#include "renderer/chunk_renderer.hpp"
#include "tile_math_helper.hpp"
#include "renderer/block_tile_renderer.hpp"
#include <iostream>

namespace Janus {
    std::unordered_map<ChunkCoord, Texture2D, HashFunc, EqualsFunc> ChunkRenderer::textureMap;

    void ChunkRenderer::unload() {
        for (auto& it : textureMap) {
            UnloadTexture(it.second);
        }
        textureMap.clear();
    }

    void ChunkRenderer::loadChunk(Tilemap &tilemap, Chunk &chunk, GameCamera &camera) {
        ChunkCoord key = {chunk.getChunkX(), chunk.getChunkY()};
        RenderTexture2D target = LoadRenderTexture(Chunk::CHUNK_SIZE * TILE_SIZE, Chunk::CHUNK_SIZE * TILE_SIZE);

        auto it = textureMap.find(key);
        if (it != textureMap.end()) {
            textureMap.erase(it);
        }

        camera.end();

        BeginTextureMode(target);
        ClearBackground(WHITE);
        for (unsigned short i = 0; i < Chunk::CHUNK_SIZE; ++i) {
            for (unsigned short j = 0; j < Chunk::CHUNK_SIZE; ++j) {
                drawTile(tilemap, chunk.getGroundTileAt(j, i), chunk.getObjectTileAt(j, i));
            }
        }
        EndTextureMode();

        camera.start();

        Image image = LoadImageFromTexture(target.texture);
        textureMap.insert({key, LoadTextureFromImage(image)});
        UnloadImage(image);
        UnloadRenderTexture(target);

        chunk.finishUpdatingTexture();
        chunk.clearWaitingForTextureUpdate();
        chunk.resetTextureUpdatePriority();
    }

    void ChunkRenderer::drawChunk(Tilemap &tilemap, Chunk &chunk, GameCamera &camera) {
        if (chunk.updateTextureRequested()) {
            loadChunk(tilemap, chunk, camera);
        }

        ChunkCoord key = {chunk.getChunkX(), chunk.getChunkY()};
        Texture2D& texture = textureMap.at(key);
        DrawTextureRec(texture, {0, 0, static_cast<float>(texture.width), static_cast<float>(-texture.height)},
                    {static_cast<float>(chunk.getChunkX() * TILE_SIZE * Chunk::CHUNK_SIZE),
                     static_cast<float>(chunk.getChunkY() * TILE_SIZE * Chunk::CHUNK_SIZE)},
                     WHITE);
    }

    void ChunkRenderer::drawTile(Tilemap &tilemap, const GroundTile &gt, const ObjectTile &ot) {
        auto [localX, localY] = TileMathHelper::tileCoordToLocalChunkCoord(ot.tileX, ot.tileY);
        if (ot.id == ObjectTileID::AIR || ot.id == ObjectTileID::NONE) {
            drawGroundTile(tilemap, gt, localX, localY);
        } else {
            drawObjectTile(tilemap, ot, localX, localY);
        }
    }

    void ChunkRenderer::drawGroundTile(Tilemap &tilemap, const GroundTile &gt, int x, int y) {
        x *= TILE_SIZE;
        y *= TILE_SIZE;
        switch (gt.id) {
            case GroundTileID::WATER:
                DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, {80,150,205,255});
                break;
            case GroundTileID::SAND:
                DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, {195,185,120,255});
                break;
            case GroundTileID::GRASS:
                DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, {120,170,100,255});
                break;
            case GroundTileID::STONE:
                DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, GRAY);
                break;
            default:
                break;
        }
    }

    void ChunkRenderer::drawObjectTile(Tilemap &tilemap, const ObjectTile &ot, int x, int y) {
        x *= TILE_SIZE;
        y *= TILE_SIZE;
        switch (ot.id) {
            case ObjectTileID::STONE:
                //DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, DARKGRAY);
                //if(ot.mouseOver)
                    //DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, DARKGRAY);
                BlockTileRenderer::drawBlock(tilemap, ot);
                break;
            case ObjectTileID::AIR:
                //DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, {102, 191, 255, 100});
                break;
            default:
                //DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, {100, 100, 255, 255});
                break;
        }
    }
}