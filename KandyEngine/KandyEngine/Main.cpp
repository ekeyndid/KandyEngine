#include "Engine/Core/CoreEngine.h"
#include "Engine/Core/Log.h"
#include "Game/FirstGame.h"

CoreEngine* engine;

int main(int argc, char* argv[]) {
	CoreEngine::GetInstance()->SetNewGame(new FirstGame);
	
	if (!CoreEngine::GetInstance()->OnCreate("GAME258 - KandyEngine", 800, 600)) {

		Log::FatalError("Engine failed to initalize", "CoreEngine.cpp", __LINE__);
		return 0;
	}
	CoreEngine::GetInstance()->Run();
	return 0;
}