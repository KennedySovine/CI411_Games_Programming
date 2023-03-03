// ======================================================= 
// Libraries / Headers to include 
#include "GameObjects.h"


// ======================================================= 
GameObject::GameObject()
{	// default Constructor; 
}

GameObject::GameObject(const char* spriteFileName, int xPos, int yPos)
{
	//Set the Sprite starting Screen Postion
	x = xPos;
	y = yPos;
	// Load Image from File to create the sprite
	SDL_Surface* tempSurface = IMG_Load(spriteFileName);
	spriteTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	if (spriteTexture == NULL) printf(" Image Load Error  - SDL Error: %s\n", SDL_GetError());
	SDL_FreeSurface(tempSurface);
	// Which part of the file to display
	srcRect.h = SPRITE_SIZE;
	srcRect.w = SPRITE_SIZE;
	srcRect.x = 0;
	srcRect.y = 0;
	// Where to display the Sprite
	destRect.h = SPRITE_SCREEN_SIZE;
	destRect.w = SPRITE_SCREEN_SIZE;
	destRect.x = x;
	destRect.y = y;
}//---

// ======================================================= 
bool GameObject::getAliveState()
{
	return isActive;
}//---


// ======================================================= 
void GameObject::update()
{	// update the display Rectangle Position
	destRect.x = x;
	destRect.y = y;
}//---

// ======================================================= 
void GameObject::setSize(int width, int height) // if sprite is non standard size
{
	// The source file
	srcRect.w = width;
	srcRect.h = height;
	// Destination Screen display 
	destRect.w = width * SPRITE_SCREEN_SIZE / SPRITE_SIZE;
	destRect.h = height * SPRITE_SCREEN_SIZE / SPRITE_SIZE;
}//----


// ======================================================= 
 void GameObject::render()
{
	// add the Sprite to the Render Image
	SDL_RenderCopy(Game::renderer, spriteTexture, &srcRect, &destRect);
}//---



// ======================================================= 

PlayerCharacter::PlayerCharacter(const char* spriteFileName, int xPos, int yPos)
{
	//Set the Sprite starting Screen Postion
	x = xPos; 	y = yPos;
	// Load Image from File to create the sprite
	SDL_Surface* tempSurface = IMG_Load(spriteFileName);
	spriteTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	if (spriteTexture == NULL) printf(" Image Load Error  - SDL Error: %s\n", SDL_GetError());
	SDL_FreeSurface(tempSurface);
	// Which part of the file to display
	srcRect.h = SPRITE_SIZE;
	srcRect.w = SPRITE_SIZE;
	srcRect.x = 0;
	srcRect.y = 0;
	// Where to display the Sprite
	destRect.h = SPRITE_SCREEN_SIZE;
	destRect.w = SPRITE_SCREEN_SIZE;
	destRect.x = x;
	destRect.y = y;
}//----


void PlayerCharacter::renderPC()
{
	// add the Sprite to the Render Image
	SDL_RenderCopyEx(Game::renderer, spriteTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
}//---


// ======================================================= 

void PlayerCharacter::updatePC()
{
	//update Drawing Position Rect
	destRect.x = x;
	destRect.y = y;
}//-----

void PlayerCharacter::movePCStep(int keyPressed)
{
	// WSAD
	if (keyPressed == 119) addY(-(SPRITE_SIZE)); //w
	if (keyPressed == 115) addY((SPRITE_SIZE)); //S
	if (keyPressed == 97) addX(-(SPRITE_SIZE * 2)); //A
	if (keyPressed == 100) addX((SPRITE_SIZE * 2)); //D
	
	//Arrow Keys
	if (keyPressed == 1073741906) addY(-(SPRITE_SIZE * 2)); //Up
	if (keyPressed == 1073741905) addY((SPRITE_SIZE * 2)); //Down
	if (keyPressed == 1073741904) addX(-(SPRITE_SIZE * 2)); //Left
	if (keyPressed == 1073741903) addX((SPRITE_SIZE * 2)); //Right
}///---

void PlayerCharacter::movePCSmooth(int keyPressed, float frameTime)
{
	// WSAD /// Add Acceleration
	if (keyPressed == 119) yVel -= acceleration * frameTime;
	if (keyPressed == 115) yVel += acceleration * frameTime;
	if (keyPressed == 97)  xVel -= acceleration * frameTime;
	if (keyPressed == 100) xVel += acceleration * frameTime;

	//Arrow Keys /// Add Acceleration
	if (keyPressed == 1073741906) yVel -= acceleration * frameTime;
	if (keyPressed == 1073741905) yVel += acceleration * frameTime;
	if (keyPressed == 1073741904) xVel -= acceleration * frameTime;
	if (keyPressed == 1073741903) xVel += acceleration * frameTime;

	// apply drag
	if (abs(xVel) > 0.1f) xVel *= drag; else xVel = 0;
	if (abs(yVel) > 0.1f) yVel *= drag; else yVel = 0;


	// Update positions
	x += xVel * frameTime;
	y += yVel * frameTime;

//	screenLimit();
	screenWrap();
}//---

void PlayerCharacter::screenLimit()
{
	// bounce of edges
	if (x > SCREEN_WIDTH - SPRITE_SIZE)  xVel = -xVel;
	if (x < 0) xVel = -xVel;
	if (y > SCREEN_HEIGHT - SPRITE_SIZE) yVel = -yVel;
	if (y < 0) yVel = -yVel;
}//---

void PlayerCharacter::screenWrap()
{
	// Screen Wrap to opposite side if sprite leaves screen
	if (x > SCREEN_WIDTH - SPRITE_SIZE)  x = 0;
	if (x < 0) x = SCREEN_WIDTH - SPRITE_SIZE;
	if (y > SCREEN_HEIGHT - SPRITE_SIZE) y = 0;
	if (y < 0) y = SCREEN_HEIGHT - SPRITE_SIZE;
}//---