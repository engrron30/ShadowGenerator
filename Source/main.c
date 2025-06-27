// C Libraries
#include <math.h>


// Local Libraries
#include "raylib.h"
#include "main_menu.h"
#include "start_screen.h"

#define ASSETS_PATH         	"Assets/"
#define PICTURE_PATH        	ASSETS_PATH "Pictures/"
#define WHOS_THAT_POKEMON_IMG	PICTURE_PATH "whos-that-pokemon.png"
#define BLUE_EXPLOSION_IMG	PICTURE_PATH "blue-explosion-background-for-menu.png"


// Main Program
int main(void)
{
    InitWindow(0, 0, "Raylib Menu");
    ToggleFullscreen();

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    SetTargetFPS(60);

    // Image Textures
    Texture2D blue_expl_txtr = LoadTexture(BLUE_EXPLOSION_IMG);
    Texture2D whos_pkmn_txtr = LoadTexture(WHOS_THAT_POKEMON_IMG);

    const char *menuItems[MENU_COUNT] = { "Start", "Credits", "Exit" };
    MenuOption selectedMenu = MENU_START;

    while (!WindowShouldClose())
    {
        // Handle input
        if (IsKeyPressed(KEY_DOWN)) selectedMenu = (selectedMenu + 1) % MENU_COUNT;
        if (IsKeyPressed(KEY_UP))   selectedMenu = (selectedMenu - 1 + MENU_COUNT) % MENU_COUNT;

        if (IsKeyPressed(KEY_ENTER)) {
            switch (selectedMenu) {
                case MENU_START:
                    TraceLog(LOG_INFO, "Start selected");
                    // TODO: Add your start logic here
		    RunStartScreen();
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

	RunMainMenu(blue_expl_txtr, whos_pkmn_txtr, menuItems, selectedMenu);
    }

    CloseWindow();
    return 0;
}

