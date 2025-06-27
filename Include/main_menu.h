#ifndef MAIN_MENU_H
#define MAIN_MENU_H

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

void RunMainMenu(Texture2D blue_expl_txtr,
		 Texture2D whos_pkmn_txtr,
                 const char *menuItems[],
		 MenuOption selected);

#endif // MAIN_MENU_H

