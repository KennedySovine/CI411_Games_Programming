#pragma once
// =======================================================
// Libraries / Headers to include 
#include "Game.h"

class GameObject
{
public:
	GameObject();
	GameObject(const char* spriteFileName, int xPos, int yPos);
	void update();
	void render();
	void setSize(int width, int height);
	bool getAliveState();
	void setAlive(bool state) { isActive = state; }
	void addX(float xAmount) { x+= xAmount; }
	void addY(float yAmount) { y+= yAmount; }		

protected: // derived classes can access
	bool isActive = false;
	float x = -100, y = -100;	 // off the screen by default
	float xVel = 0, yVel = 0;
	float speed = 6;
	float angle = 0;

	SDL_Rect srcRect = { 0,0,0,0 };
	SDL_Rect destRect = { 0,0,0,0 };
	SDL_Texture* spriteTexture = nullptr;
};

// =======================================================

class PlayerCharacter:GameObject
{
public:
	PlayerCharacter(const char* spriteFileName, int xPos, int yPos);
	void updatePC();
	void renderPC();
	void movePCStep(int keyPressed);
	void movePCSmooth(int keypressed, float frameTime);
	void screenLimit();
	void screenWrap();

private:	
	float drag = 0.99F;
	float acceleration = 1;
};

// =======================================================

class NPC :GameObject {
public:
	void moveNPCSmooth(float frameTime);
	void screenLimit();
	void screenWrap();
private:
	float drag = .99F;
	float acceleration = 1.5;
};
