#include "functions.h"
#include <raylib.h>

void UpdateDrawFrame() {
    //variable stuff

    BeginDrawing();
    DrawText("Hello from functions.cpp!", 190, 200, 20, DARKGRAY);
    ClearBackground(RAYWHITE);
    EndDrawing();
}