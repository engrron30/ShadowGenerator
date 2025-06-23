#include "raylib.h"
#include <math.h>

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


// Public Functions
void addControlNotes()
{
    // Heart-beating effect: oscillating font size
    float time = GetTime();
    float scale = 1.0f + 0.1f * sinf(time * 4.0f);  // Faster beat
    int baseSize = 25;
    int fontSize = baseSize * scale;
    int margin = 20;
    int textY = GetScreenHeight()/3 + 500 - fontSize;
    int textX = GetScreenWidth()/1.3 - fontSize * 2 - margin - 150;
    const char *text = "[ Press ENTER to select ]";
    int outlineSize 	= 3;
    Color outlineColor 	= BLACK;

    DrawText(text, textX - outlineSize, textY, fontSize, outlineColor);
    DrawText(text, textX + outlineSize, textY, fontSize, outlineColor);
    DrawText(text, textX, textY - outlineSize, fontSize, outlineColor);
    DrawText(text, textX, textY + outlineSize, fontSize, outlineColor);
    DrawText(text, textX, textY, fontSize, YELLOW);
}

void addVersion()
{
    const char *footer = "ShadowGenv2.0";
    int fontSize	= 20;
    int margin 		= 20;
    int textY 		= GetScreenHeight() - fontSize - margin;
    int textX 		= GetScreenWidth() - fontSize - margin - 150;

    DrawText(footer, textX, textY, fontSize, BLACK);
}


// Main Program
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
		int fontSize 		= (i == selected) ? 100 : 70;
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

    	    addControlNotes();
    	    addVersion();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

