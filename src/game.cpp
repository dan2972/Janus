#include "game.hpp"
#include "texture_manager.hpp"

namespace Janus {
    int Game::screenWidth = 800;
    int Game::screenHeight = 600;

    Game::Game() {
        //SetTargetFPS(60);
        window.SetState(FLAG_VSYNC_HINT);

        TextureManager::LoadTexture("resources/slime.png");
        player = new Player(10, 10, &entityHandler);
        entityHandler.add(player);
        entityHandler.add(new Actor(100, 100, &entityHandler));
        entityHandler.add(new Actor(132, 100, &entityHandler));

        camera.setTargetPlayer(player);
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
                FPS = frames;
                frames = 0;
            }
        }
    }

    void Game::update() {
        entityHandler.update();
    }

    void Game::render(float dt) {
        camera.update();

        window.BeginDrawing();

            window.ClearBackground(BLACK);
                camera.start();

                    entityHandler.render(dt);

                camera.end();

            DrawText(std::string("FPS: " + std::to_string(FPS)).c_str(), 10, 570, 16, WHITE);

        //window.DrawFPS(10, 570);
        window.EndDrawing();
    }
}