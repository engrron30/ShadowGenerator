#include "start_screen.h"
#include "resources.h"
#include "main_menu.h"


void RunStartScreen(void)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    Rectangle leftBox  = { screenWidth/4.0f - 150, screenHeight/2.0f - 100, 200, 200 };
    Rectangle rightBox = { 3*screenWidth/4.0f - 50, screenHeight/2.0f - 100, 200, 200 };
    Rectangle generateBtn = { screenWidth/2.0f - 100, screenHeight - 150, 200, 50 };

    while (!WindowShouldClose())
    {
        // Back navigation
        if (IsKeyPressed(KEY_BACKSPACE)) break;

        Vector2 mouse = GetMousePosition();

        bool hoverLeft  = CheckCollisionPointRec(mouse, leftBox);
        bool hoverRight = CheckCollisionPointRec(mouse, rightBox);
        bool clickGenerate = false;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, generateBtn)) {
            clickGenerate = true;
        }

        BeginDrawing();
            ClearBackground(BLANK);  // allow for transparent overlay

            // Draw transparent background from main menu
            if (gMenuSnapshotValid) {
		Rectangle SnapshotRect = { 0, 0, (float) screenWidth, -(float) screenHeight };
		Vector2 SnapshotVector = { 0, 0 };
		Color faded = (Color){255, 255, 255, 100}; // semi-transparent

                DrawTextureRec(gMenuSnapshotTexture.texture, SnapshotRect, SnapshotVector, faded);
            }

            // Title
            DrawText("Generate your Shadow here", screenWidth/2 - MeasureText("Generate your Shadow here", 60)/2, 80, 60, YELLOW);

            // Left Box
            DrawRectangleRec(leftBox, hoverLeft ? (Color){ 200, 200, 255, 180 } : (Color){ 150, 150, 150, 150 });
            DrawRectangleLinesEx(leftBox, 3, WHITE);
            DrawText("Upload Left", leftBox.x + 20, leftBox.y + leftBox.height + 10, 20, LIGHTGRAY);

            // Right Box
            DrawRectangleRec(rightBox, hoverRight ? (Color){ 200, 200, 255, 180 } : (Color){ 150, 150, 150, 150 });
            DrawRectangleLinesEx(rightBox, 3, WHITE);
            DrawText("Upload Right", rightBox.x + 20, rightBox.y + rightBox.height + 10, 20, LIGHTGRAY);

            // Generate Button
            DrawRectangleRec(generateBtn, clickGenerate ? DARKGRAY : GRAY);
            DrawRectangleLinesEx(generateBtn, 2, BLACK);
            DrawText("Generate", generateBtn.x + 40, generateBtn.y + 15, 25, BLACK);

            // Tooltip or Debug (optional)
            if (hoverLeft)  DrawText("Click to upload image", 20, screenHeight - 60, 20, WHITE);

        EndDrawing();
    }
}
