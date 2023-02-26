// ======================================================= 
// Libraries / Headers to include 
#include "GameObjects.h"


// ======================================================= 
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
	destRect.h = SPRITE_SIZE;
	destRect.w = SPRITE_SIZE;
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
{
	// update the display Rectangle Position
	destRect.x = x;
	destRect.y = y;
 }//---

// ======================================================= 
void GameObject::setSize(int pWidth, int pHeight) // if sprite is non standard size
{
	// The source file
	srcRect.w = pWidth;
	srcRect.h = pHeight;

	// Destination Screen display 
	destRect.w = pWidth;
	destRect.h = pHeight;
}//----


// ======================================================= 
void GameObject::render()
{	
	// add the Sprite to the Render Image
	SDL_RenderCopy(Game::renderer, spriteTexture, &srcRect, &destRect);
}//---