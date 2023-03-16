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
	void Loadtexture(const char* spriteFileName );
	void screenLimit();
	void screenBounce();
	void screenWrap();

	float getX() { return x; }
	float getY() { return y; }

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
	PlayerCharacter(const char* spriteFileName, int xPos, int yPos, float rotation );
	void updatePC(int keyPressed, float frameTime);
	void renderPC();
	void stepMove(int keyPressed);
	void smoothMove(int keyPressed, float frameTime);
	void rotateMove(int keyPressed, float frameTime);
	float getX() { return x; }
	float getY() { return y; }
private:	
	float drag = 0.99F;
	float acceleration = 50;
	int rotationSpeed = 360;
};

// =======================================================

class NPC :GameObject {
public:
	NPC(const char* spriteFileName, int xPos, int yPos, float rotation);
	void renderNPC();
	void updateNPC();
	void setAlive(bool state) { isActive = state; }
	bool getAliveState() { return isActive; }
	void roam(float frameTime);
	void chasePC(float pcX, float pcY);
	void setSpeed(float newSpeed) { speed = newSpeed; }

private:
	float drag = 0.99F;
	float acceleration = 50;
};
