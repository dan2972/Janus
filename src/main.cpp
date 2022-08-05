#include <raylib-cpp.hpp>
#include "entity_handler.hpp"
#include "player.hpp"
#include "texture_manager.hpp"
#include "tilemap.hpp"

using namespace Janus;

int main() {
    int screenWidth = 800;
    int screenHeight = 600;

    raylib::Window window(screenWidth, screenHeight, "Janus");
    //SetTargetFPS(60);
    window.SetState(FLAG_VSYNC_HINT);

    EntityHandler entityHandler;
    TextureManager::LoadTexture("resources/slime.png");
    Player* player = new Player(&entityHandler, 10, 10);
    entityHandler.add(player);
    entityHandler.add(new Actor(&entityHandler, 100, 100));

    Tilemap tilemap;

    while (!window.ShouldClose())
    {
        window.BeginDrawing();

        window.ClearBackground(BLACK);

        int playerChunkX = player->getPos().x > 0 ? (int)player->getPos().x / (Chunk::CHUNK_SIZE*Tile::TILE_SIZE) :
                                                    (int)(player->getPos().x - Chunk::CHUNK_SIZE*Tile::TILE_SIZE)/ (Chunk::CHUNK_SIZE*Tile::TILE_SIZE);
        int playerChunkY = player->getPos().y > 0 ? (int)player->getPos().y / (Chunk::CHUNK_SIZE*Tile::TILE_SIZE) :
                           (int)(player->getPos().y - Chunk::CHUNK_SIZE*Tile::TILE_SIZE)/ (Chunk::CHUNK_SIZE*Tile::TILE_SIZE);

        if (!tilemap.chunkExistsAt(playerChunkX, playerChunkY)) {
            tilemap.addChunk(new Chunk(playerChunkX, playerChunkY));
        }

        for (auto & it : tilemap.getChunkMap()) {
            it.second->render();
        }

        entityHandler.update(GetFrameTime());
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            //entityHandler.add(new Player(&entityHandler, GetMouseX(), GetMouseY()));
        }

        window.DrawFPS(10, 570);
        window.EndDrawing();
    }

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}
