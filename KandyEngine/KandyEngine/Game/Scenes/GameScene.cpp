#include "GameScene.h"

GameScene::GameScene(){


}

GameScene::~GameScene()
{

}

bool GameScene::OnCreate()
{
	Log::Info("Creating GameScene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(
		glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));
	
Model* diceModel = new Model("./Engine/Resources/Models/Dice.obj", "./Engine/Resources/Materials/Dice.mtl",
	ShaderHandler::GetInstance()->GetShader("basicShader"));
Model* appleModel = new Model("./Engine/Resources/Models/Apple.obj", "./Engine/Resources/Materials/Apple.mtl",
	ShaderHandler::GetInstance()->GetShader("basicShader"));
SceneGraph::GetInstance()->AddModel(diceModel);
SceneGraph::GetInstance()->AddModel(appleModel);

SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(-2.0f, 0.0f, -2.0f)));
SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, glm::vec3(1.5f, 0.0f, 0.0f)),
	"Apple");

diceModel = nullptr;
appleModel = nullptr;

	return true;


}

void GameScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}
