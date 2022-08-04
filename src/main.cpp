#include <raylib-cpp.hpp>
#include "entity_handler.hpp"
#include "player.hpp"
#include "texture_manager.hpp"

using namespace Janus;

int main() {
    int screenWidth = 800;
    int screenHeight = 600;

    raylib::Window window(screenWidth, screenHeight, "Janus");
    //SetTargetFPS(60);
    window.SetState(FLAG_VSYNC_HINT);

    EntityHandler entityHandler;
    TextureManager::LoadTexture("resources/slime.png");
    entityHandler.add(new Player(&entityHandler, 10, 10));
    entityHandler.add(new Actor(&entityHandler, 100, 100));

    while (!window.ShouldClose())
    {
        window.BeginDrawing();

        window.ClearBackground(BLACK);

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
