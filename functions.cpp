#include "functions.h"

void UpdateDrawFrame() {
    BeginDrawing();
    DrawText("Hello from functions.cpp!", 190, 200, 20, DARKGRAY);
    ClearBackground(RAYWHITE);
    EndDrawing();
}