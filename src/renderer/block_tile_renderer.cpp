#include "renderer/block_tile_renderer.hpp"
#include "tile_math_helper.hpp"
#include "texture_manager.hpp"

namespace Janus {
    void BlockTileRenderer::drawBlock(Tilemap &tilemap, const ObjectTile &tile) {
        auto [chunkX, chunkY, localX, localY] = TileMathHelper::tileCoordToChunkAndLocalChunkCoord(tile.tileX, tile.tileY);
        Texture2D* texture = TextureManager::GetTexture("resources/stone_wall_sheet.png");
        //DrawRectangle(localX*Tile::TILE_SIZE, localY*Tile::TILE_SIZE, Tile::TILE_SIZE, Tile::TILE_SIZE, DARKGRAY);

        std::array<bool, 9> nearbyWalls = getNearbyWalls(tilemap, tile.tileX, tile.tileY);
        if (nearbyWalls[1]) { // top
            if (nearbyWalls[3]) { // left
                if (nearbyWalls[0]) { // top left
                    drawTopLeft(0, 1, texture, localX, localY);
                } else {
                    drawTopLeft(3, 0, texture, localX, localY);
                }
            } else {
                drawTopLeft(2, 0, texture, localX, localY);
            }
            if (nearbyWalls[5]) { // right
                if (nearbyWalls[2]) { // top right
                    drawTopRight(0, 1, texture, localX, localY);
                } else {
                    drawTopRight(3, 0, texture, localX, localY);
                }
            } else {
                drawTopRight(2, 0, texture, localX, localY);
            }
        } else {
            if (nearbyWalls[3]) { // left
                drawTopLeft(1, 0, texture, localX, localY);
            } else {
                drawTopLeft(0, 0, texture, localX, localY);
            }
            if (nearbyWalls[5]) { // right
                drawTopRight(1, 0, texture, localX, localY);
            } else {
                drawTopRight(0, 0, texture, localX, localY);
            }
        }

        if (nearbyWalls[7]) { // bottom
            if (nearbyWalls[3]) { // left
                if (nearbyWalls[6]) { // bottom left
                    drawBottomLeft(0, 1, texture, localX, localY);
                } else {
                    drawBottomLeft(3, 0, texture, localX, localY);
                }
            } else {
                drawBottomLeft(2, 0, texture, localX, localY);
            }
            if (nearbyWalls[5]) { // right
                if (nearbyWalls[8]) { // bottom right
                    drawBottomRight(0, 1, texture, localX, localY);
                } else {
                    drawBottomRight(3, 0, texture, localX, localY);
                }
            } else {
                drawBottomRight(2, 0, texture, localX, localY);
            }
        } else {
            if (nearbyWalls[3]) { // left
                drawBottomLeft(1, 0, texture, localX, localY);
            } else {
                drawBottomLeft(0, 0, texture, localX, localY);
            }
            if (nearbyWalls[5]) { // right
                drawBottomRight(1, 0, texture, localX, localY);
            } else {
                drawBottomRight(0, 0, texture, localX, localY);
            }
        }
    }

    std::array<bool, 9> BlockTileRenderer::getNearbyWalls(Tilemap &tilemap, int tileX, int tileY) {
        std::array<bool, 9> nearbyWalls{false};
        int arrayCounter = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                auto* tile = tilemap.getObjectTileAt(tileX + j, tileY + i);
                if (tile!= nullptr) {
                    if (tile->id != ObjectTileID::AIR && tile->id != ObjectTileID::NONE) {
                        nearbyWalls[arrayCounter] = true;
                    }
                }
                ++arrayCounter;
            }
        }
        return nearbyWalls;
    }

    void BlockTileRenderer::drawTopLeft(int spriteTileX, int spriteTileY, Texture2D *texture, int localX,
                                       int localY) {
        DrawTexturePro(*texture, {(float)spriteTileX*32,(float)spriteTileY*32, 16, 10},
                       {(float)localX*TILE_SIZE, (float)localY*TILE_SIZE, 16, 10}, {0, 0}, 0, WHITE);
    }

    void BlockTileRenderer::drawTopRight(int spriteTileX, int spriteTileY, Texture2D *texture, int localX,
                                        int localY) {
        DrawTexturePro(*texture, {(float)spriteTileX*32+16,(float)spriteTileY*32, 16, 10},
                       {(float)localX*TILE_SIZE+16, (float)localY*TILE_SIZE, 16, 10}, {0, 0}, 0, WHITE);
    }

    void BlockTileRenderer::drawBottomLeft(int spriteTileX, int spriteTileY, Texture2D *texture, int localX,
                                          int localY) {
        DrawTexturePro(*texture, {(float)spriteTileX*32,(float)spriteTileY*32+10, 16, 22},
                       {(float)localX*TILE_SIZE, (float)localY*TILE_SIZE+10, 16, 22}, {0, 0}, 0, WHITE);
    }

    void BlockTileRenderer::drawBottomRight(int spriteTileX, int spriteTileY, Texture2D *texture, int localX,
                                           int localY) {
        DrawTexturePro(*texture, {(float)spriteTileX*32+16,(float)spriteTileY*32+10, 16, 22},
                       {(float)localX*TILE_SIZE+16, (float)localY*TILE_SIZE+10, 16, 22}, {0, 0}, 0, WHITE);
    }
}