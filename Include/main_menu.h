#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "raylib.h"

typedef enum {
    MENU_START,
    MENU_CREDITS,
    MENU_EXIT,
    MENU_COUNT
} MenuOption;

void RunMainMenu(Texture2D blue_expl_txtr, Texture2D whos_pkmn_txtr,
                 const char *menuItems[], MenuOption selected);

#endif // MAIN_MENU_H

