#include <stdio.h>

#include "start_screen.h"
#include "generate_shadow.h"
#include "resources.h"
#include "main_menu.h"
#include "tinyfiledialogs.h"

#define SCRIPTS_DIR                     "Scripts/"
#define GENERATE_SHADOW_PYTHON_FILE     "generate-shadow-image.py"
#define OUTPUT_SHADOW_FILE              "OutputShadow.png"

// ─────────────────────────────
// UI Configuration Constants
// ─────────────────────────────
const int BOX_WIDTH         = 600;
const int BOX_HEIGHT        = 600;
const int BOX_BORDER        = 4;
const int FONT_SIZE_LABEL   = 25;
const int BTN_WIDTH         = 200;
const int BTN_HEIGHT        = 50;

// ─────────────────────────────
// UI Colors
// ─────────────────────────────
Color COLOR_START_BACKGND = { 255, 255, 255, 100 };
Color COLOR_BOX_DEFAULT   = { 150, 150, 150, 150 };
Color COLOR_BOX_HOVER     = { 200, 200, 255, 180 };
Color COLOR_BORDER        = WHITE;
Color COLOR_LABEL         = LIGHTGRAY;
Color COLOR_BTN_TEXT      = BLACK;
Color COLOR_BTN_DEFAULT   = WHITE;
Color COLOR_BTN_CLICK     = GRAY;

// ─────────────────────────────
// UI Strings
// ─────────────────────────────
const char *START_STR      = "Start";
const char *GENERATE_STR   = "Generate";
const char *SAVE_IMG_STR   = "Save Image";
char gImagePath[1024]      = { 0 };

// ─────────────────────────────
// UI Vectors & Textures
// ─────────────────────────────
Vector2 VECTOR_DEFAULT  = { 0, 0 };
Texture2D gUserImage    = { 0 };
Texture2D gShadowImage  = { 0 };

// ─────────────────────────────
// UI Boolean States
// ─────────────────────────────
static bool hoverLeft       = true; 
static bool hoverRight      = true;
static bool hoverGenerate   = true;
static bool hoverSave       = true;
static bool firstLoadStart  = true;

// ─────────────────────────────
// Generate Button Delay
// ─────────────────────────────
double generateClickTime        = 0;
const double generateClickDelay = 0.2;
bool generateClicked            = false;

// ─────────────────────────────
// Static Functions
// ─────────────────────────────
static void DrawLabeledBox(Rectangle box, const char *label, bool isHovered);
static void DrawButton(Rectangle btn, const char *text, bool isClicked);
static void DrawInteractiveButton(Rectangle btn, const char *text, bool isHovered, bool isClicked);
static void DrawUserImage(Rectangle box);
static void DrawPlusSign(Rectangle box);
static void HandleImageSelection(void);
static void HandleGenerateClick(void);

// ─────────────────────────────
// Main Start Screen Logic
// ─────────────────────────────
void RunStartScreen(void) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    Rectangle leftBox       = { screenWidth / 4.0f - BOX_WIDTH / 2,     screenHeight / 2.0f - BOX_HEIGHT / 2, BOX_WIDTH, BOX_HEIGHT                 };
    Rectangle rightBox      = { 3 * screenWidth / 4.0f - BOX_WIDTH / 2, screenHeight / 2.0f - BOX_HEIGHT / 2, BOX_WIDTH, BOX_HEIGHT                 };
    Rectangle generateBtn   = { screenWidth / 2 - BTN_WIDTH / 2,        screenHeight / 2 + rightBox.height / 3 - BTN_HEIGHT, BTN_WIDTH, BTN_HEIGHT  };
    Rectangle saveBtn       = { screenWidth / 2 - BTN_WIDTH / 2,        screenHeight / 2 + rightBox.height / 2 - BTN_HEIGHT, BTN_WIDTH, BTN_HEIGHT  };

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_BACKSPACE)) break;

        Vector2 mouse   = GetMousePosition();
        hoverLeft       = CheckCollisionPointRec(mouse, leftBox);
        hoverRight      = CheckCollisionPointRec(mouse, rightBox);
        hoverGenerate   = CheckCollisionPointRec(mouse, generateBtn);
        hoverSave       = CheckCollisionPointRec(mouse, saveBtn);

        HandleImageSelection();
        HandleGenerateClick();

        BeginDrawing();
            ClearBackground(BLANK);

            if (gMenuSnapshotValid) {
                Rectangle snapshotRect = { 0, 0, (float) screenWidth, -(float) screenHeight };
                DrawTextureRec(gMenuSnapshotTexture.texture, snapshotRect, VECTOR_DEFAULT, COLOR_START_BACKGND);
            }

            DrawText(START_STR, screenWidth / 2 - MeasureText(START_STR, 60) / 2, 80, 60, YELLOW);
            DrawLabeledBox(leftBox, "Your Image", hoverLeft);
            DrawLabeledBox(rightBox, "Generated Shadow", hoverRight);

            if (gUserImage.id > 0) DrawUserImage(leftBox);
            else DrawPlusSign(leftBox);
            if (gShadowImage.id > 0) DrawTexturePro(gShadowImage, (Rectangle){0, 0, gShadowImage.width, gShadowImage.height}, rightBox, VECTOR_DEFAULT, 0.0f, WHITE);

            DrawInteractiveButton(generateBtn, GENERATE_STR, hoverGenerate, generateClicked);
            DrawInteractiveButton(saveBtn, SAVE_IMG_STR, hoverSave, false);

            if (hoverLeft)
                DrawText("Click to upload image", 20, screenHeight - 60, 20, WHITE);

        EndDrawing();
    }
}

// ─────────────────────────────
// Image Selection
// ─────────────────────────────
static void HandleImageSelection(void) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoverLeft) {
        const char *filters[] = { "*.png", "*.jpg", "*.jpeg", "*.bmp" };
        const char *filePath = tinyfd_openFileDialog("Select an Image", "", 4, filters, "Image files", 0);

        if (filePath) {
            if (gUserImage.id > 0) UnloadTexture(gUserImage);
            Image img = LoadImage(filePath);
            gUserImage = LoadTextureFromImage(img);
            UnloadImage(img);
            snprintf(gImagePath, sizeof(gImagePath), "%s", filePath);

            firstLoadStart = false;
        }
    }
}

// ─────────────────────────────
// Generate Button Handler
// ─────────────────────────────
static void HandleGenerateClick(void) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoverGenerate) {
        generateClickTime = GetTime();
        generateClicked = true;
    }

    if (generateClicked && (GetTime() - generateClickTime >= generateClickDelay)) {
        generateClicked = false;
        generate_shadow();
    }
}

// ─────────────────────────────
// Draw Components
// ─────────────────────────────
static void DrawLabeledBox(Rectangle box, const char *label, bool isHovered) {
    Color boxColor = isHovered ? COLOR_BOX_HOVER : COLOR_BOX_DEFAULT;
    DrawRectangleRec(box, boxColor);
    DrawRectangleLinesEx(box, BOX_BORDER, COLOR_BORDER);
    DrawText(label, box.x + 20, box.y + box.height + 10, FONT_SIZE_LABEL, COLOR_LABEL);
}

static void DrawInteractiveButton(Rectangle btn, const char *text, bool isHovered, bool isClicked) {
    Color btnColor = firstLoadStart ? GRAY : (isClicked ? GRAY : (isHovered ? LIGHTGRAY : COLOR_BTN_DEFAULT));
    DrawRectangleRec(btn, btnColor);
    DrawRectangleLinesEx(btn, 2, BLACK);

    int textWidth = MeasureText(text, FONT_SIZE_LABEL);
    DrawText(text, btn.x + btn.width / 2 - textWidth / 2, btn.y + 12, FONT_SIZE_LABEL, COLOR_BTN_TEXT);
}

static void DrawUserImage(Rectangle box) {
    Rectangle src  = { 0, 0, (float) gUserImage.width, (float) gUserImage.height };
    Rectangle dest = box;
    DrawTexturePro(gUserImage, src, dest, VECTOR_DEFAULT, 0.0f, WHITE);
}

static void DrawPlusSign(Rectangle box) {
    const char *plus = "+";
    int fontSize = 100;
    int textWidth = MeasureText(plus, fontSize);
    int textX = box.x + box.width / 2 - textWidth / 2;
    int textY = box.y + box.height / 2 - fontSize / 2;

    DrawText(plus, textX + 5, textY + 5, fontSize + 10, BLACK);
    DrawText(plus, textX, textY, fontSize, GRAY);
}

