#include "raylib.h"

int main(void)
{
    // Initialize fullscreen window
    InitWindow(0, 0, "Raylib Fullscreen Example");  // Width and height 0 → auto-fullscreen
    ToggleFullscreen();  // Switch to fullscreen mode

    SetTargetFPS(60);  // Set desired frame rate

    // Main game loop
    while (!WindowShouldClose())    // Detect window close or ESC key
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("This is a fullscreen raylib window!", 50, 50, 30, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

