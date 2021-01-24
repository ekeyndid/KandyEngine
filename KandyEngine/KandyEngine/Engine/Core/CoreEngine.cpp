#include "CoreEngine.h"

CoreEngine::CoreEngine()
{
	window = nullptr;
	isRunning = false;

}

CoreEngine::~CoreEngine()
{
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {

		std::cout << "Failed to create window" << std::endl;
		OnDestroy();
		return isRunning = false;
	}
	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning) {

		Update(0.016f);
		Render();
	}
	if (!isRunning) {
		OnDestroy();
	}

}

bool CoreEngine::GetIsRunning()
{
	return isRunning;
}

void CoreEngine::Update(const float deltaTime_)
{
}

void CoreEngine::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	SDL_GL_SwapWindow(window->GetWindow());

}

void CoreEngine::OnDestroy()
{
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}
