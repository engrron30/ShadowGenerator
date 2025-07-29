#ifndef MAIN_MENU_H
#define MAIN_MENU_H

typedef enum {
    MENU_START,
    MENU_CREDITS,
    MENU_EXIT,
    MENU_COUNT
} MenuOption;

extern const char *gMenuItems[MENU_COUNT];
extern MenuOption gSelectedMenu;

void RunMainMenu(void);

#endif

