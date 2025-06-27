#include "start_screen.h"
#include "resources.h"
#include "main_menu.h"

#include <unistd.h>


void RunStartScreen(void)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    float boxWidth  = 600;
    float boxHeight = 600;

    Rectangle leftBox  = {
        screenWidth / 4.0f - boxWidth / 2,
        screenHeight / 2.0f - boxHeight / 2,
        boxWidth,
        boxHeight
    };

    Rectangle rightBox = {
        3 * screenWidth / 4.0f - boxWidth / 2,
        screenHeight / 2.0f - boxHeight / 2,
        boxWidth,
        boxHeight
    };

    Rectangle generateBtn = {
        screenWidth / 2.0f - 100,
        screenHeight - 150,
        200,
        50
    };

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
            DrawText("Generate Your Shadow here", screenWidth/2 - MeasureText("Generate your Shadow here", 60)/2, 80, 60, YELLOW);

            DrawRectangleRec(leftBox, hoverLeft ? (Color){ 200, 200, 255, 180 } : (Color){ 150, 150, 150, 150 });
            DrawRectangleLinesEx(leftBox, 4, WHITE);
            DrawText("Your Image", leftBox.x + 20, leftBox.y + leftBox.height + 10, 25, LIGHTGRAY);

            DrawRectangleRec(rightBox, hoverRight ? (Color){ 200, 200, 255, 180 } : (Color){ 150, 150, 150, 150 });
            DrawRectangleLinesEx(rightBox, 4, WHITE);
            DrawText("Generated Shadow", rightBox.x + 20, rightBox.y + rightBox.height + 10, 25, LIGHTGRAY);

	    // Generate Button
    	    Color btnColor;
	    if (clickGenerate) { 
		btnColor = GRAY;
	    } else {
	    	btnColor = WHITE;
	    }

    	    DrawRectangleRec(generateBtn, btnColor);
    	    DrawRectangleLinesEx(generateBtn, 2, BLACK);
    	    const char *btnText = "Generate";
    	    int btnFontSize = 25;
    	    int textWidth = MeasureText(btnText, btnFontSize);
    	    DrawText(btnText, generateBtn.x + generateBtn.width/2 - textWidth/2, generateBtn.y + 12, btnFontSize, BLACK);


            // Tooltip or Debug (optional)
            if (hoverLeft)  DrawText("Click to upload image", 20, screenHeight - 60, 20, WHITE);

        EndDrawing();
    }
}
