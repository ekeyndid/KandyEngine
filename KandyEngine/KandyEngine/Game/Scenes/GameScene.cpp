#include "GameScene.h"

GameScene::GameScene() :square(nullptr){


}

GameScene::~GameScene()
{
	delete square;
	square = nullptr;
}

bool GameScene::OnCreate()
{
	Log::Info("Creating GameScene", "GameScene.cpp", __LINE__);

	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(6);
	// element 1
	v.position = glm::vec3(-0.2f, 0.0f, 0.0f);
	vertexList.push_back(v);
	// element 2
	v.position = glm::vec3(0.2f, 0.0f, 0.0f);
	vertexList.push_back(v);
	// element 3
	v.position = glm::vec3(0.2f, 0.3f, 0.0f);
	vertexList.push_back(v);
	
	// element 4
	v.position = glm::vec3(-0.2f, 0.3f, 0.0f);
	vertexList.push_back(v);
	// element 5
	v.position = glm::vec3(0.2f, 0.3f, 0.0f);
	vertexList.push_back(v);
	// element 6
	v.position = glm::vec3(-0.2f, 0.0f, 0.0f);
	vertexList.push_back(v);
	Model* model = new Model();
	model->AddMesh(new Mesh(vertexList));
	square = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
}

void GameScene::Render()
{
	square->Render();
}
