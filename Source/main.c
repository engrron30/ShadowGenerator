#include "raylib.h"

#define ASSETS_PATH         	"Assets/"
#define PICTURE_PATH        	ASSETS_PATH "Pictures/"
#define WHOS_THAT_POKEMON_IMG	PICTURE_PATH "whos-that-pokemon.png"
#define BLUE_EXPLOSION_IMG	PICTURE_PATH "blue-explosion-background-for-menu.png"

typedef enum {
    MENU_START,
    MENU_CREDITS,
    MENU_EXIT,
    MENU_COUNT
} MenuOption;

int main(void)
{
    InitWindow(0, 0, "Raylib Menu");
    ToggleFullscreen();

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    SetTargetFPS(60);

    // Load image (make sure logo.png exists in working directory)
    Texture2D blue_expl_txtr = LoadTexture(BLUE_EXPLOSION_IMG);
    Texture2D whos_pkmn_txtr = LoadTexture(WHOS_THAT_POKEMON_IMG);

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

	    // Draw images on the background
            int blue_expl_x = screenWidth      - blue_expl_txtr.width - 1100;
            int blue_expl_y = screenHeight / 2 - blue_expl_txtr.height / 2;
            DrawTexture(blue_expl_txtr, blue_expl_x, blue_expl_y, WHITE);

            int whos_pkmn_x = screenWidth      - whos_pkmn_txtr.width - 100;
            int whos_pkmn_y = screenHeight / 2 - whos_pkmn_txtr.height / 2;
            DrawTexture(whos_pkmn_txtr, whos_pkmn_x, whos_pkmn_y, WHITE);

	    // Menu Choices
            for (int i = 0; i < MENU_COUNT; i++) {

                const char *text 	= menuItems[i];
                Color color 		= (i == selected) ? YELLOW : GRAY;
                Color outlineColor 	= (i == selected) ? BLACK  : GREEN;
		int fontSize 		= (i == selected) ? 90 : 70;
		int outline 		= (i == selected) ? 5 : 2;
                int textWidth 		= MeasureText(text, fontSize);
		int textX 		= screenWidth/4 - textWidth/2 + 50;
		int textY 		= i * 120 + 350;

		// Draw text with outline
		DrawText(text, textX - outline, textY, fontSize, outlineColor);
		DrawText(text, textX + outline, textY, fontSize, outlineColor);
		DrawText(text, textX, textY - outline, fontSize, outlineColor);
		DrawText(text, textX, textY + outline, fontSize, outlineColor);
                DrawText(text, screenWidth/4 - textWidth/2 + 50, textY, fontSize, color);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

