#include "nicetea/nicetea.h"

#if defined(PLATFORM_WEB)
	#include <emscripten.h>
#endif

int main() {
	InitWindow(1280, 720, "Game Title");
	SetExitKey(KEY_NULL);
	bool Quit = false;

	//Variable definitions

	auto UpdateDrawFrame = [&]() {
		float dt = GetFrameTime();	  //delta time

		BeginDrawing();

		ClearBackground({ 20, 20, 30, 255 });
		DrawText("Hello there.", 530, 320, 40, BLACK);
		EndDrawing();
	};

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop_arg(
		[](void* arg) {
			auto* fn = static_cast<decltype(UpdateDrawFrame)*>(arg);
			(*fn)();
		},
		&UpdateDrawFrame,
		60,
		1
	);
#else
	SetTargetFPS(60);
	while (!Quit) {
		if (WindowShouldClose()) Quit = true;
		UpdateDrawFrame();
	}
#endif

	CloseWindow();
	return 0;
}
