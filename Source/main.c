#include "raylib.h"

#define ASSETS_PATH         	"Assets/"
#define PICTURE_PATH        	ASSETS_PATH "Pictures/"
#define WHOS_THAT_POKEMON_LOGO  PICTURE_PATH "whos-that-pokemon.png"

typedef enum {
    MENU_START,
    MENU_CREDITS,
    MENU_EXIT,
    MENU_COUNT
} MenuOption;

int main(void)
{
    InitWindow(0, 0, "Raylib Menu");
    ToggleFullscreen(); // Fullscreen

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    SetTargetFPS(60);

    // Load image (make sure logo.png exists in working directory)
    Texture2D logo_1 = LoadTexture(WHOS_THAT_POKEMON_LOGO);

    const char *menuItems[MENU_COUNT] = { "Start", "Credits", "Exit" };
    MenuOption selected = MENU_START;

    while (!WindowShouldClose())
    {
        // Handle input
        if (IsKeyPressed(KEY_DOWN)) selected = (selected + 1) % MENU_COUNT;
        if (IsKeyPressed(KEY_UP))   selected = (selected - 1 + MENU_COUNT) % MENU_COUNT;

        if (IsKeyPressed(KEY_ENTER)) {
            switch (selected) {
                case MENU_START:
                    TraceLog(LOG_INFO, "Start selected");
                    // TODO: Add your start logic here
                    break;
                case MENU_CREDITS:
                    TraceLog(LOG_INFO, "Credits selected");
                    // TODO: Show credits screen
                    break;
                case MENU_EXIT:
                    CloseWindow();
                    return 0;
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(RED);
	    const char* mainTitle = "Who's That Pokemon!";
            DrawText(mainTitle, screenWidth/4 - MeasureText(mainTitle, 60)/2, 60, 80, WHITE);

            for (int i = 0; i < MENU_COUNT; i++) {
                Color color = (i == selected) ? YELLOW : GRAY;
                int fontSize = 40;
                const char *text = menuItems[i];
                int textWidth = MeasureText(text, fontSize);
                int y = 550 + i * 70;
                DrawText(text, screenWidth/4 - textWidth/2, y, fontSize, color);

		// Draw image on right side, centered vertically
            	int imageX = screenWidth - logo_1.width - 100;
            	int imageY = screenHeight / 2 - logo_1.height / 2;
            	DrawTexture(logo_1, imageX, imageY, WHITE);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

