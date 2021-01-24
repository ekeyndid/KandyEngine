#ifndef WINDOW_H
#define WINDOW_H

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
	bool OnCreate(std::string name_, int width_, int height_); // initialize the window 
	void OnDestroy();	// deallocate all the variables when the window is destructing
	int GetWidth() const;		// returns the window's width*/
	int GetHeight() const;	// returns the window's height
	SDL_Window* GetWindow() const;	// returns the window

private:
	void SetPreAttributes();
	void SetPostAttributes();

	int width;
	int height;
	SDL_Window* window;
	SDL_GLContext context;
};
#endif
