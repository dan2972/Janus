#include "game.hpp"
#include "texture_manager.hpp"

namespace Janus {
    int Game::screenWidth = 800;
    int Game::screenHeight = 600;

    Game::Game() {
        //SetTargetFPS(60);
        window.ClearState(FLAG_VSYNC_HINT);

        TextureManager::LoadTexture("resources/slime.png");
        player = new Player(&entityHandler, 10, 10);
        entityHandler.add(player);
        entityHandler.add(new Actor(&entityHandler, 100, 100));
        entityHandler.add(new Actor(&entityHandler, 132, 100));
    }

    void Game::run() {
        double lastTime = GetTime();
        double amountOfTicks = 30.0;
        double tps = 1.0 / amountOfTicks;
        double delta = 0;
        double timer = GetTime();
        int frames = 0;
        while (!window.ShouldClose()) {
            double now = GetTime();
            delta += (now - lastTime) / tps;
            lastTime = now;
            while (delta >= 1) {
                update();
                delta--;
            }
            render((float)delta);
            ++frames;

            if (GetTime() - timer > 1) {
                ++timer;
                std::cout << "FPS: " << frames << std::endl;
                frames = 0;
            }
        }
    }

    void Game::update() {
        entityHandler.update();
    }

    void Game::render(float dt) {
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
            it.second->render(dt);
        }

        entityHandler.render(dt);

        //window.DrawFPS(10, 570);
        window.EndDrawing();
    }
}