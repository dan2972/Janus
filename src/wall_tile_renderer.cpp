#include "wall_tile_renderer.hpp"

namespace Janus {
    void WallTileRenderer::drawWall(Tilemap &tilemap, const ObjectTile &tile) {
        int tileX = (int)(tile.getPos().x / Tile::TILE_SIZE);
        int tileY = (int)(tile.getPos().y / Tile::TILE_SIZE);
        auto [chunkX, chunkY, localX, localY] = TileMathHelper::tileCoordToChunkAndLocalChunkCoord(tileX, tileY);
        raylib::Texture2D* texture = TextureManager::GetTexture("resources/stone_wall_sheet.png");
        //DrawRectangle(localX*Tile::TILE_SIZE, localY*Tile::TILE_SIZE, Tile::TILE_SIZE, Tile::TILE_SIZE, DARKGRAY);

        std::array<bool, 9> nearbyWalls = getNearbyWalls(tilemap, tileX, tileY);
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

    std::array<bool, 9> WallTileRenderer::getNearbyWalls(Tilemap &tilemap, int tileX, int tileY) {
        std::array<bool, 9> nearbyWalls{false};
        int arrayCounter = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                auto* tile = tilemap.getTileAt(tileX + j, tileY + i);
                if (tile!= nullptr && tile->getTileType() == Tile::OBJECT) {
                    auto& ot = (ObjectTile&) *tile;
                    if (ot.getObjectTileType() == ObjectTile::WALL) {
                        nearbyWalls[arrayCounter] = true;
                    }
                }
                ++arrayCounter;
            }
        }
        return nearbyWalls;
    }

    void WallTileRenderer::drawTopLeft(int spriteTileX, int spriteTileY, raylib::Texture2D *texture, int localX,
                                       int localY) {
        DrawTexturePro(*texture, raylib::Rectangle({(float)spriteTileX*32,(float)spriteTileY*32}, {16, 10}),
                       raylib::Rectangle({(float)localX*Tile::TILE_SIZE, (float)localY*Tile::TILE_SIZE},
                                         {16, 10}), {0, 0}, 0, WHITE);
    }

    void WallTileRenderer::drawTopRight(int spriteTileX, int spriteTileY, raylib::Texture2D *texture, int localX,
                                        int localY) {
        DrawTexturePro(*texture, raylib::Rectangle({(float)spriteTileX*32+16,(float)spriteTileY*32}, {16, 10}),
                       raylib::Rectangle({(float)localX*Tile::TILE_SIZE+16, (float)localY*Tile::TILE_SIZE},
                                         {16, 10}), {0, 0}, 0, WHITE);
    }

    void WallTileRenderer::drawBottomLeft(int spriteTileX, int spriteTileY, raylib::Texture2D *texture, int localX,
                                          int localY) {
        DrawTexturePro(*texture, raylib::Rectangle({(float)spriteTileX*32,(float)spriteTileY*32+10}, {16, 22}),
                       raylib::Rectangle({(float)localX*Tile::TILE_SIZE, (float)localY*Tile::TILE_SIZE+10},
                                         {16, 22}), {0, 0}, 0, WHITE);
    }

    void WallTileRenderer::drawBottomRight(int spriteTileX, int spriteTileY, raylib::Texture2D *texture, int localX,
                                           int localY) {
        DrawTexturePro(*texture, raylib::Rectangle({(float)spriteTileX*32+16,(float)spriteTileY*32+10}, {16, 22}),
                       raylib::Rectangle({(float)localX*Tile::TILE_SIZE+16, (float)localY*Tile::TILE_SIZE+10},
                                         {16, 22}), {0, 0}, 0, WHITE);
    }
}