#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "generate_shadow.h"

#define SCRIPTS_DIR                     "Scripts/"
#define GENERATE_SHADOW_PYTHON_FILE     "generate-shadow-image.py"
#define OUTPUT_SHADOW_FILE              "OutputShadow.png"

extern char gImagePath[1024];
extern Texture2D gShadowImage;

void generate_shadow()
{
    char generate_shadow_python_cmd[256];
    snprintf(generate_shadow_python_cmd, sizeof(generate_shadow_python_cmd),
             "python3 \"%s/%s\" \"%s\"", SCRIPTS_DIR, GENERATE_SHADOW_PYTHON_FILE, gImagePath);
    int ret = system(generate_shadow_python_cmd);
    
    if (ret != 0) {
        TraceLog(LOG_WARNING, "❌ Python script failed to execute (code: %d)", ret);
        return;
    }
    
    TraceLog(LOG_INFO, "✅ Python script executed successfully");
    
    // Unload old shadow image if any
    if (gShadowImage.id > 0) {
        UnloadTexture(gShadowImage);
    }
    
    // Load new shadow image
    char shadow_file_path[256];
    snprintf(shadow_file_path, sizeof(shadow_file_path), "%s/%s", SCRIPTS_DIR, OUTPUT_SHADOW_FILE);
    
    if (FileExists(shadow_file_path)) {
        Image shadowImg = LoadImage(shadow_file_path);
        gShadowImage = LoadTextureFromImage(shadowImg);
        UnloadImage(shadowImg);
    } else {
        TraceLog(LOG_WARNING, "❌ Shadow image not found: %s", shadow_file_path);
    }
}
