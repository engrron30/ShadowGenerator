#include "raylib.h"
#include "resources.h"          // InitResources();
#include "main_menu.h"          // RunMainMenu();  
#include "start_screen.h"       // RunStartScreen();

static void HandleMenuSelection(void);

int main(void)
{

    InitWindow(0, 0, "Raylib Menu");
    ToggleFullscreen();
    InitResources();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        HandleMenuSelection();
        RunMainMenu();
    }

    UnloadResources();
    CloseWindow();
    return 0;
}

static void HandleMenuSelection(void)
{
    if (IsKeyPressed(KEY_DOWN)) gSelectedMenu = (gSelectedMenu + 1) % MENU_COUNT;
    if (IsKeyPressed(KEY_UP))   gSelectedMenu = (gSelectedMenu - 1 + MENU_COUNT) % MENU_COUNT;
    
    if (IsKeyPressed(KEY_ENTER)) {
        switch (gSelectedMenu) {
    
            case MENU_START:
                TraceLog(LOG_INFO, "Start selected");
                CaptureMenuSnapshot();
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
}
