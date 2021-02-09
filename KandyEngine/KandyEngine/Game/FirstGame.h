#ifndef FIRSTGAME_H
#define FIRSTGAME_H

#include "../Engine/Core/CoreEngine.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"

class FirstGame : public NewGame
{
public:
	FirstGame();
	virtual ~FirstGame();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;

private:
	int currentSceneNum;
	Scene* currentScene;
	void BulidScene();
};
#endif // FIRSTGAME_H