#include "main_menu.h"
#include "resources.h"
#include <math.h>

// ─────────────────────────────
// Menu Items
// ─────────────────────────────
const char *gMenuItems[MENU_COUNT] = 
{ 
    "Start", 
    "Credits", 
    "Exit" 
};
MenuOption gSelectedMenu = MENU_START;


static void addControlNotes()
{
    float time = GetTime();
    float scale = 1.0f + 0.1f * sinf(time * 4.0f);
    int baseSize = 25;
    int fontSize = baseSize * scale;
    int margin = 20;
    int textY = GetScreenHeight()/3 + 500 - fontSize;
    int textX = GetScreenWidth()/1.3 - fontSize * 2 - margin - 150;
    const char *text = "[ Press ENTER to select ]";
    int outlineSize = 3;
    Color outlineColor = BLACK;

    DrawText(text, textX - outlineSize, textY, fontSize, outlineColor);
    DrawText(text, textX + outlineSize, textY, fontSize, outlineColor);
    DrawText(text, textX, textY - outlineSize, fontSize, outlineColor);
    DrawText(text, textX, textY + outlineSize, fontSize, outlineColor);
    DrawText(text, textX, textY, fontSize, YELLOW);
}

static void addVersion()
{
    const char *footer = "ShadowGenv2.0";
    int fontSize = 20;
    int margin = 20;
    int textY = GetScreenHeight() - fontSize - margin;
    int textX = GetScreenWidth() - fontSize - margin - 150;

    DrawText(footer, textX, textY, fontSize, BLACK);
}

void RunMainMenu( void )
{

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    BeginDrawing();
        ClearBackground(RED);

        int blue_expl_x = screenWidth - gBlueExplosionTexture.width - 1100;
        int blue_expl_y = screenHeight / 2 - gBlueExplosionTexture.height / 2;
        DrawTexture(gBlueExplosionTexture, blue_expl_x, blue_expl_y, WHITE);

        int whos_pkmn_x = screenWidth - gWhosThatPokemonTexture.width - 100;
        int whos_pkmn_y = screenHeight / 2 - gWhosThatPokemonTexture.height / 2;
        DrawTexture(gWhosThatPokemonTexture, whos_pkmn_x, whos_pkmn_y, WHITE);

        for (int i = 0; i < MENU_COUNT; i++) {
            const char *text = gMenuItems[i];
            Color color = (i == gSelectedMenu) ? YELLOW : GRAY;
            Color outlineColor = (i == gSelectedMenu) ? BLACK : GREEN;
            int fontSize = (i == gSelectedMenu) ? 100 : 70;
            int outline = (i == gSelectedMenu) ? 5 : 2;
            int textWidth = MeasureText(text, fontSize);
            int textX = screenWidth / 4 - textWidth / 2 + 50;
            int textY = i * 120 + 350;

            DrawText(text, textX - outline, textY, fontSize, outlineColor);
            DrawText(text, textX + outline, textY, fontSize, outlineColor);
            DrawText(text, textX, textY - outline, fontSize, outlineColor);
            DrawText(text, textX, textY + outline, fontSize, outlineColor);
            DrawText(text, textX, textY, fontSize, color);
        }

        addControlNotes();
        addVersion();
    EndDrawing();
}

