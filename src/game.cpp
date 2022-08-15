#include "game.hpp"
#include "texture_manager.hpp"
#include "random_generator.hpp"
#include "noise/perlin_generator.hpp"
#include "drone.hpp"

namespace Janus {
    Game::Game() {
        //SetTargetFPS(60);
        window.ClearState(FLAG_VSYNC_HINT);
        SetTraceLogLevel(LOG_FATAL | LOG_ERROR | LOG_WARNING);

        TextureManager::LoadTexture("resources/slime.png");
        TextureManager::LoadTexture("resources/player.png");
        TextureManager::LoadTexture("resources/stone_wall_sheet.png");
        player = new Player(10, 10, &entityHandler);
        entityHandler.add(player);
        //for (int i = 0; i < 1000; ++i)
        //    entityHandler.add(new Drone(0, 0, &entityHandler));

        camera.setTargetPlayer(player);

        RandomGenerator::setSeed(1);
        PerlinGenerator::initialize(1);

        window.BeginDrawing();
        window.ClearBackground(GRAY);
        raylib::DrawText(std::string("LOADING CHUNKS"), SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 20, WHITE);
        window.EndDrawing();
        entityHandler.loadChunks(0, 0, CHUNK_PRELOAD_DISTANCE);
        entityHandler.preloadTilemapTextures(camera, 0, 0);
    }

    void Game::run() {
        double lastTime = GetTime();
        double amountOfTicks = 40.0;
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
                FPS = frames;
                frames = 0;
            }
        }
    }

    void Game::update() {
        entityHandler.update();
    }

    void Game::render(float dt) {
        camera.update(dt);

        window.BeginDrawing();

            window.ClearBackground(BLACK);

            camera.start();

                entityHandler.render(camera, player->getChunkPos().x, player->getChunkPos().y, dt);

            camera.end();

            DrawText(std::string("FPS: " + std::to_string(FPS)).c_str(), 10, SCREEN_HEIGHT - 30, 16, WHITE);

        //window.DrawFPS(10, 570);
        window.EndDrawing();
    }
}