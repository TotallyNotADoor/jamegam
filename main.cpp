#include "functions.h"
#include "nicetea.h"
#include <raylib.h>
#include <raymath.h>

#if defined(PLATFORM_WEB)
    #include <emscripten.h>
#endif

int main() {
    InitWindow(1280, 720, "Game Title");
    SetExitKey(KEY_NULL);
    bool quit = false;

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);
    while (!quit) {
        if (WindowShouldClose()) quit = true;
        UpdateDrawFrame();
    }
#endif

    CloseWindow();
    return 0;
}

