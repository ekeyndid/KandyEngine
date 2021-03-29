#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineBasket = nullptr;

CoreEngine::CoreEngine() : fps(30)
{
	window = nullptr;
	isRunning = false;
	timer = nullptr;
	newgame = nullptr;
	CurrentSceneNum = 0;
	

}

CoreEngine::~CoreEngine()
{
}

CoreEngine* CoreEngine::GetInstance()
{
	if (engineBasket.get() == nullptr) {
		engineBasket.reset(new CoreEngine);

	}
	return engineBasket.get();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	Log::OnCreate();
	window = new Window();
	timer = new Timer();
	if (!window->OnCreate(name_, width_, height_)) {

		Log::FatalError("Failed to create window", "Window.cpp", __LINE__);
		OnDestroy();
		return isRunning = false;
	}
	
	if (newgame) {

		if (!newgame->OnCreate()) {

			Log::FatalError("Failed to create Game", "NewGame.cpp", __LINE__);
			OnDestroy();
			return isRunning = false;

		}
	}

	Log::Info("Everything worked","CoreEngine.cpp", __LINE__);
	timer->Start();
	return isRunning = true;
}

void CoreEngine::Run()
{
	
	while (isRunning) {
		timer->UpdateFrameTicks();
		Update(timer->GetDeltaTime());
		Render();
		SDL_Delay(timer->GetSleepTime(fps));
	}
	if (!isRunning) {
		OnDestroy();
	}

}

void CoreEngine::Exit()
{
	isRunning = false;
}

bool CoreEngine::GetIsRunning() const {
	return isRunning;
}

int CoreEngine::GetCurrentScene() const
{
	return CurrentSceneNum;
}

void CoreEngine::SetNewGame(NewGame* newgame_) { newgame = newgame_; }

void CoreEngine::SetCurrentScene(int sceneNum_)
{
	CurrentSceneNum = sceneNum_;
}

void CoreEngine::Update(const float deltaTime_)
{
	if (newgame) {
		newgame->Update(deltaTime_);
		std::cout << deltaTime_ << std::endl;
	}

}

void CoreEngine::Render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (newgame) {
		newgame->Render();
	}
	SDL_GL_SwapWindow(window->GetWindow());

}

void CoreEngine::OnDestroy()
{
	delete newgame;
	newgame = nullptr;
	
	delete timer;
	timer = nullptr;
	
	delete window;
	window = nullptr;
	
	SDL_Quit();
	exit(0);
}
