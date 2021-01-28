#ifndef COREENGINE_H
#define COREENGINE_H

#include "Window.h"
#include <memory>
class CoreEngine
{
public:
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(const CoreEngine&&) = delete;

	// gets an pointer to use functions from the engine
	static CoreEngine* GetInstance();
	
	// calls the things in the Window class to set up what's being assigned in CoreEngine's OnCreate
	bool OnCreate(std::string name_, int width_, int height_);
	// gets the engine running and refreshing with Update(), and calls Ondestroy when it checks that it isnt running
	void Run();
	//returns IsRunning once 
	bool GetIsRunning();
private:
	CoreEngine();
	~CoreEngine();
	// updates the engine every 60FPS
	void Update(const float deltaTime_);
	//draws what is in the window such as the RGBA
	void Render();
	// deallocate all the variables when the window is destructing
	void OnDestroy();
	
	static std::unique_ptr<CoreEngine> engineBasket;
	friend std::default_delete<CoreEngine>;
	
	Window* window;
	bool isRunning;
};

#endif