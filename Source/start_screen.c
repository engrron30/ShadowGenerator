#include "start_screen.h"
#include "resources.h"
#include "main_menu.h"

// ─────────────────────────────
// UI Configuration Constants
// ─────────────────────────────
const int BOX_WIDTH = 600;
const int BOX_HEIGHT = 600;
const int BOX_BORDER = 4;
const int FONT_SIZE_LABEL = 25;
const int BTN_WIDTH = 200;
const int BTN_HEIGHT = 50;

// ─────────────────────────────
// UI Colors
// ─────────────────────────────
Color COLOR_START_BACKGND	= (Color) { 255, 255, 255, 100 };
Color COLOR_BOX_DEFAULT 	= (Color) { 150, 150, 150, 150 };
Color COLOR_BOX_HOVER   	= (Color) { 200, 200, 255, 180 };
Color COLOR_BORDER      	= WHITE;
Color COLOR_LABEL       	= LIGHTGRAY;
Color COLOR_BTN_TEXT    	= BLACK;
Color COLOR_BTN_DEFAULT 	= WHITE;
Color COLOR_BTN_CLICK   	= GRAY;

// ─────────────────────────────
// UI Text
// ─────────────────────────────          
const char *ScreenTitle		= "Generate Your Shadow here";
const char *GenerateBtnText 	= "Generate";

// ─────────────────────────────
// UI Vectors
// ─────────────────────────────
Vector2 VECTOR_DEFAULT	= { 0, 0 };

// ─────────────────────────────
// UI Boolean States
// ─────────────────────────────
static bool hoverLeft;
static bool hoverRight;
static bool hoverGenerate;

// ─────────────────────────────
// Generate Button Delay Handlers
// ─────────────────────────────
double generateClickTime 	= 0;
const double generateClickDelay = 0.2; // 200 milliseconds
bool generateClicked = false;

// ─────────────────────────────
// Draw a hoverable box with a label
// ─────────────────────────────
static void DrawLabeledBox(Rectangle box, const char *label, bool isHovered)
{
    Color boxColor = isHovered ? COLOR_BOX_HOVER : COLOR_BOX_DEFAULT;
    DrawRectangleRec(box, boxColor);
    DrawRectangleLinesEx(box, BOX_BORDER, COLOR_BORDER);
    DrawText(label, box.x + 20, box.y + box.height + 10, FONT_SIZE_LABEL, COLOR_LABEL);
}

// ─────────────────────────────
// Draw a centered button with text
// ─────────────────────────────
static void DrawButton(Rectangle btn, const char *text, bool isClicked)
{
    Color fillColor = isClicked ? COLOR_BTN_CLICK : COLOR_BTN_DEFAULT;
    DrawRectangleRec(btn, fillColor);
    DrawRectangleLinesEx(btn, 2, BLACK);

    int textWidth = MeasureText(text, FONT_SIZE_LABEL);
    DrawText(text, btn.x + btn.width / 2 - textWidth / 2, btn.y + 12, FONT_SIZE_LABEL, COLOR_BTN_TEXT);
}


// ─────────────────────────────
// Main Start Screen UI Logic
// ─────────────────────────────
void RunStartScreen(void)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Layouts
    Rectangle leftBox = {
        screenWidth / 4.0f - BOX_WIDTH / 2,
        screenHeight / 2.0f - BOX_HEIGHT / 2,
        BOX_WIDTH,
        BOX_HEIGHT
    };

    Rectangle rightBox = {
        3 * screenWidth / 4.0f - BOX_WIDTH / 2,
        screenHeight / 2.0f - BOX_HEIGHT / 2,
        BOX_WIDTH,
        BOX_HEIGHT
    };

    Rectangle generateBtn = {
        screenWidth / 2.0f - BTN_WIDTH / 2,
        screenHeight - 150,
        BTN_WIDTH,
        BTN_HEIGHT
    };

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_BACKSPACE)) break;

        Vector2 mouse = GetMousePosition();

        hoverLeft      = CheckCollisionPointRec(mouse, leftBox);
        hoverRight     = CheckCollisionPointRec(mouse, rightBox);
        hoverGenerate  = CheckCollisionPointRec(mouse, generateBtn);

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoverGenerate) {
            generateClickTime = GetTime();
            generateClicked = true;
	}

	if (generateClicked && (GetTime() - generateClickTime >= generateClickDelay)) {
            generateClicked = false;
	}


        BeginDrawing();
            ClearBackground(BLANK);

            // Optional background
            if (gMenuSnapshotValid) {
                Rectangle snapshotRect = { 0, 0, (float) screenWidth, -(float) screenHeight };
                DrawTextureRec(gMenuSnapshotTexture.texture, snapshotRect, VECTOR_DEFAULT, COLOR_START_BACKGND);
            }

            // Title
            DrawText(ScreenTitle, screenWidth / 2 - MeasureText(ScreenTitle, 60) / 2, 80, 60, YELLOW);

            // Left and Right Image Boxes
            DrawLabeledBox(leftBox,  "Your Image",         hoverLeft);
            DrawLabeledBox(rightBox, "Generated Shadow",   hoverRight);

            // Generate Button
	    Color currentBtnColor = COLOR_BTN_DEFAULT;  // default: white

	    if (generateClicked)
    		currentBtnColor = GRAY;
	    else if (hoverGenerate)
    		currentBtnColor = LIGHTGRAY;

	    DrawRectangleRec(generateBtn, currentBtnColor);
	    DrawRectangleLinesEx(generateBtn, 2, BLACK);
	    int textWidth = MeasureText(GenerateBtnText, FONT_SIZE_LABEL);
	    DrawText(GenerateBtnText, generateBtn.x + generateBtn.width / 2 - textWidth / 2, generateBtn.y + 12, FONT_SIZE_LABEL, COLOR_BTN_TEXT);

            // Tooltip
            if (hoverLeft)
                DrawText("Click to upload image", 20, screenHeight - 60, 20, WHITE);

        EndDrawing();
    }
}

