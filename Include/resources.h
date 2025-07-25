// Include/resources.h
#ifndef RESOURCES_H
#define RESOURCES_H

#include "raylib.h"

extern Texture2D gBlueExplosionTexture;
extern Texture2D gWhosThatPokemonTexture;
extern RenderTexture2D gMenuSnapshotTexture;
extern bool gMenuSnapshotValid;

void InitResources(void);
void UnloadResources(void);
void CaptureMenuSnapshot(void);

#endif // RESOURCES_H

