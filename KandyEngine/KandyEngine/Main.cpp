#include "Engine/Core/CoreEngine.h"

CoreEngine* engine;

int main(int argc, char* argv[]) {
	engine = new CoreEngine;
	if (!engine->OnCreate("GAME258 - KandyEngine", 800, 600)) {

		delete engine;
		engine = nullptr;
		return 0;
	}
	engine->Run();
	delete engine;
	engine = nullptr;
	return 0;
}