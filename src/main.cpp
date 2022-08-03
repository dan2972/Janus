#include <raylib-cpp.hpp>
#include "entity_handler.hpp"
#include "player.hpp"

using namespace Janus;

int main() {
    int screenWidth = 800;
    int screenHeight = 600;

    raylib::Window window(screenWidth, screenHeight, "Janus");
    //SetTargetFPS(60);
    window.SetState(FLAG_VSYNC_HINT);

    EntityHandler entityHandler;

    while (!window.ShouldClose())
    {
        window.BeginDrawing();

        window.ClearBackground(BLACK);

        window.DrawFPS(10, 570);
        entityHandler.update(GetFrameTime());
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            entityHandler.add(new Player(&entityHandler, GetMouseX(), GetMouseY()));
        }

        window.EndDrawing();
    }

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}
