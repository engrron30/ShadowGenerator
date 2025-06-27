#include "raylib.h"
#include "start_screen.h"

void RunStartScreen()
{
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Game Started!", 200, 200, 40, GREEN);
            DrawText("Press ESC to return to menu", 200, 300, 20, GRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ESCAPE)) break;
    }
}
