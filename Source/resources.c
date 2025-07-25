// Source/resources.c
#include "resources.h"
#include "main_menu.h"

#define ASSETS_PATH              "Assets/"
#define PICTURE_PATH             ASSETS_PATH "Pictures/"
#define WHOS_THAT_POKEMON_IMG    PICTURE_PATH "whos-that-pokemon.png"
#define BLUE_EXPLOSION_IMG       PICTURE_PATH "blue-explosion-background-for-menu.png"

//─────────────────────────────
// Global texture definitions
//─────────────────────────────
Texture2D 	gBlueExplosionTexture;
Texture2D 	gWhosThatPokemonTexture;
RenderTexture2D gMenuSnapshotTexture;
bool 		gMenuSnapshotValid = false;

void InitResources(void)
{
    gBlueExplosionTexture     = LoadTexture(BLUE_EXPLOSION_IMG);
    gWhosThatPokemonTexture   = LoadTexture(WHOS_THAT_POKEMON_IMG);

    gMenuSnapshotTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    gMenuSnapshotValid = false;
}

void UnloadResources(void)
{
    UnloadTexture(gBlueExplosionTexture);
    UnloadTexture(gWhosThatPokemonTexture);
    UnloadRenderTexture(gMenuSnapshotTexture);
}

void CaptureMenuSnapshot(void)
{
    BeginTextureMode(gMenuSnapshotTexture);
        RunMainMenu(); // draw to the snapshot
    EndTextureMode();

    gMenuSnapshotValid = true;
}

