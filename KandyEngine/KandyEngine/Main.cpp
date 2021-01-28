#include "Engine/Core/CoreEngine.h"

CoreEngine* engine;

int main(int argc, char* argv[]) {
	if (!CoreEngine::GetInstance()->OnCreate("GAME258 - KandyEngine", 800, 600)) {

		std::cout << "Engine failed to initalize" << std::endl;
		return 0;
	}
	CoreEngine::GetInstance()->Run();
	return 0;
}