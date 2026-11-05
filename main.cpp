#include "functions.h"
#include "raylib.h"

int main() {
    InitWindow(1920, 1080, "Game Title");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawGameUI();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}