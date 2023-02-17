#pragma once
// =======================================================
// Libraries / Headers to include 
#include "Game.h"


class GameObject
{
public:
	GameObject(const char* spriteFileName, int xPos, int yPos);
	void update();
	void render();
	void setSize(int pWidth, int pHeight);
	bool getAliveState();

private:
	bool isActive = false;
	int x, y;	
	SDL_Rect srcRect = { 0,0,0,0 };
	SDL_Rect destRect = { 0,0,0,0 };
	SDL_Texture* spriteTexture = nullptr;
	SDL_Renderer* renderer = nullptr;
};

