#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	Log::Info("Start scene", __FILE__, __LINE__);
	CoreEngine::GetInstance()->SetCurrentScene(1);
	return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}
