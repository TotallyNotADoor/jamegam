#include "functions.h"
#include "classes.h"
#include <raylib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten.h>
#endif

int main() {
    InitWindow(1920, 1080, "Game Title");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();
    return 0;
}

