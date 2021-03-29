#include "FirstGame.h"

FirstGame::FirstGame() : NewGame(){
	currentSceneNum = 0;
	currentScene = nullptr;

}

FirstGame::~FirstGame()
{
	delete currentScene;
	currentScene = nullptr;
}

bool FirstGame::OnCreate()
{
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Log::FatalError("Engine's scene is nto initalzed to 0", "CoreEngine.cpp", __LINE__);
	return false;
}

void FirstGame::Update(const float deltaTime_)
{
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene()) {

		BulidScene();
	}
	currentScene->Update(deltaTime_);
}

void FirstGame::Render()
{
	currentScene->Render();
}

void FirstGame::BulidScene()
{
	delete currentScene;
	currentScene = nullptr;
	
	switch (CoreEngine::GetInstance()->GetCurrentScene()) {
	
	case 1:
		currentScene = new GameScene();
		break;
	
	default: // case 0
		currentScene = new StartScene();
		break;
	
	}

	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) {
		Log::FatalError("Scene Failed to be created", "FirstGame.cpp", __LINE__);
		CoreEngine::GetInstance()->Exit();
	}

}
