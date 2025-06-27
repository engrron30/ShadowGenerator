// Source/resources.c
#include "resources.h"

#define ASSETS_PATH              "Assets/"
#define PICTURE_PATH             ASSETS_PATH "Pictures/"
#define WHOS_THAT_POKEMON_IMG    PICTURE_PATH "whos-that-pokemon.png"
#define BLUE_EXPLOSION_IMG       PICTURE_PATH "blue-explosion-background-for-menu.png"

// Global texture definitions
Texture2D gBlueExplosionTexture;
Texture2D gWhosThatPokemonTexture;

void InitResources(void)
{
    gBlueExplosionTexture     = LoadTexture(BLUE_EXPLOSION_IMG);
    gWhosThatPokemonTexture   = LoadTexture(WHOS_THAT_POKEMON_IMG);
}

void UnloadResources(void)
{
    UnloadTexture(gBlueExplosionTexture);
    UnloadTexture(gWhosThatPokemonTexture);
}

