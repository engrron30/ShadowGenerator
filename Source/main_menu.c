#include "main_menu.h"
#include <math.h>

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

void RunMainMenu(Texture2D blue_expl_txtr, Texture2D whos_pkmn_txtr,
                 const char *menuItems[], MenuOption selected)
{

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    BeginDrawing();
        ClearBackground(RED);

        int blue_expl_x = screenWidth - blue_expl_txtr.width - 1100;
        int blue_expl_y = screenHeight / 2 - blue_expl_txtr.height / 2;
        DrawTexture(blue_expl_txtr, blue_expl_x, blue_expl_y, WHITE);

        int whos_pkmn_x = screenWidth - whos_pkmn_txtr.width - 100;
        int whos_pkmn_y = screenHeight / 2 - whos_pkmn_txtr.height / 2;
        DrawTexture(whos_pkmn_txtr, whos_pkmn_x, whos_pkmn_y, WHITE);

        for (int i = 0; i < MENU_COUNT; i++) {
            const char *text = menuItems[i];
            Color color = (i == selected) ? YELLOW : GRAY;
            Color outlineColor = (i == selected) ? BLACK : GREEN;
            int fontSize = (i == selected) ? 100 : 70;
            int outline = (i == selected) ? 5 : 2;
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

