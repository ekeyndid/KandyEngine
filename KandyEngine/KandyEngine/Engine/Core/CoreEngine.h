#ifndef COREENGINE_H
#define COREENGINE_H

#include "Window.h"
class CoreEngine
{
public:
	CoreEngine();
	~CoreEngine();
	bool OnCreate(std::string name_, int width_, int height_); // initialize the window 
	void Run();
	bool GetIsRunning();
private:
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();
	Window* window;
	bool isRunning;
};

#endif