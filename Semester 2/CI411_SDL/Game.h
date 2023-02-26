#pragma once

// ======================================================= 
// Libraries / Headers to include 
#include <SDL.h>
#include<SDL_Image.h>
#include<iostream>

// Constants
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define SPRITE_SIZE 32
#define FPS 50


// ======================================================= 
class Game
{
public:	
	Game(); // constructor
	bool isRunning() { return gameRunning; }
	void startSDL(const char* title);
	void welcomeScreen();
	void createGameObjects();
	void handleEvents();
	void update();
	void render();
	void closeSDL();
	void exitScreen();

	static SDL_Renderer* renderer;
	static SDL_Event playerInputEvent;

private:
	bool gameRunning = false;
	SDL_Window* gameWindow = nullptr;	
};

