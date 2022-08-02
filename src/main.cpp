#include <iostream>
#include <raylib-cpp.hpp>

int main() {
    int screenWidth = 800;
    int screenHeight = 600;

    raylib::Window window(screenWidth, screenHeight, "Janus");
    //SetTargetFPS(60);
    window.SetState(FLAG_VSYNC_HINT);

    while (!window.ShouldClose())
    {
        window.BeginDrawing();

        window.ClearBackground(RAYWHITE);

        window.DrawFPS(10, 570);

        DrawText("Janus", 190, 200, 20, LIGHTGRAY);

        window.EndDrawing();
    }

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}
