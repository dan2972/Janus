#include <raylib.h>
#include <string>
#include "game.hpp"
#include "global_values.hpp"
#include "entities/player_entity.hpp"
#include "systems/actor_render_system.hpp"
#include "systems/tilemap_render_system.hpp"
#include "systems/tilemap_tick_system.hpp"
#include "systems/actor_tick_system.hpp"
#include "systems/player_tick_system.hpp"
#include "systems/movement_system.hpp"
#include "systems/tilemap_preload_system.hpp"
#include "texture_manager.hpp"
#include "input_manager.hpp"

namespace Janus {
    Game::Game() {
        SetTraceLogLevel(LOG_ERROR | LOG_FATAL);

        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Janus");

        ClearWindowState(FLAG_VSYNC_HINT);

        TextureManager::Load("resources/slime.png");
        TextureManager::Load("resources/stone_wall_sheet.png");

        InputManager::Initialize();

        world.registerStartupSystem<TilemapPreloadSystem>();

        world.registerTickSystem<TilemapTickSystem>();
        world.registerTickSystem<MovementSystem>();
        world.registerTickSystem<PlayerTickSystem>();
        world.registerTickSystem<ActorTickSystem>();

        world.registerRenderSystem<TilemapRenderSystem>();
        world.registerRenderSystem<ActorRenderSystem>();

        world.spawnEntity<PlayerEntity>(glm::vec2(10, 10));
        auto view = world.getEntitiesWith<PlayerComponent>();
        for (auto player : view) {
            auto& actor = world.getComponentFromEntity<ActorComponent>(player);
            camera.setTarget(actor);
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Loading Chunks", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 10, 20, WHITE);
        EndDrawing();
        world.initialize();
    }

    void Game::run() {
        double lastTime = GetTime();
        double amountOfTicks = TICKS_PER_SECOND;
        double tps = 1.0 / amountOfTicks;
        double delta = 0;
        double timer = GetTime();
        int frames = 0;
        while (!WindowShouldClose()) {
            double now = GetTime();
            delta += (now - lastTime) / tps;
            lastTime = now;
            while (delta >= 1) {
                update();
                delta--;
            }
            render(static_cast<float>(delta));
            ++frames;

            if (GetTime() - timer > 1) {
                ++timer;
                FPS = frames;
                frames = 0;
            }
        }

        CloseWindow();
    }

    void Game::update() {
        world.tick();
    }

    void Game::render(float d) {
        camera.update(d);

        BeginDrawing();

            ClearBackground(BLACK);

            camera.start();

                world.render(d);

            camera.end();

            DrawText(std::string("FPS: " + std::to_string(FPS)).c_str(), 10, SCREEN_HEIGHT - 30, 16, WHITE);

        EndDrawing();
    }
}