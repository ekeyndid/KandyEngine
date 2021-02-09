#ifndef WINDOW_H
#define WINDOW_H

#include "Log.h"

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>

class Window
{
public:
	Window();
	~Window();
	
	// initialize the window with the string of the name and the values for the width and height
	bool OnCreate(std::string name_, int width_, int height_); 
	
	// deallocate all the variables when the window is destructing
	void OnDestroy();	
	
	// returns the window's width*/
	int GetWidth() const;		
	// returns the window's height
	int GetHeight() const;	
	// returns the window
	SDL_Window* GetWindow() const;	

private:
	
	void SetPreAttributes();
	void SetPostAttributes();

	//value for the width of the window
	int width;
	//value for the height of the window
	int height;
	//pointer for the window
	SDL_Window* window;
	//pointer for the context
	SDL_GLContext context;
};
#endif
