// ======================================================= 
// Libraries / Headers to include 
#include "GameObjects.h"
#include	"Game.h";

// ======================================================= 
GameObject::GameObject()
{	// default Constructor; 
}

void GameObject::Loadtexture(const char* spriteFileName)
{
	// Load Image from File to create the sprite
	SDL_Surface* tempSurface = IMG_Load(spriteFileName);
	spriteTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	if (spriteTexture == NULL) printf(" Image Load Error  - SDL Error: %s\n", SDL_GetError());
	SDL_FreeSurface(tempSurface);

}//---

// ======================================================= 

GameObject::GameObject(const char* spriteFileName, int xPos, int yPos)
{
	Loadtexture(spriteFileName);	// Load Image from File
	x = xPos; 	y = yPos;
	srcRect.h = srcRect.w = SPRITE_SIZE;
	srcRect.x = srcRect.y = 0;
	destRect.h = destRect.w = SPRITE_SIZE;
	destRect.x = (int)x;	destRect.y = (int)y;
}//---

// ======================================================= 
bool GameObject::getAliveState()
{
	return isActive;
}//---


// ======================================================= 
void GameObject::update()
{	// update the display Rectangle Position
	destRect.x = (int)x;
	destRect.y = (int)y;
}//---

// ======================================================= 
void GameObject::setSize(int width, int height) // if sprite is non standard size
{
	// The image source 
	srcRect.w = width;
	srcRect.h = height;
	// Destination Screen display 
	destRect.w = width;
	destRect.h = height;
}//----


// ======================================================= 
void GameObject::render()
{
	// add the Sprite to the Render Image
	SDL_RenderCopy(Game::renderer, spriteTexture, &srcRect, &destRect);
}//---

// ======================================================= 

void GameObject::disableOffScreen()
{
	// disable if sprite leave the screen area
	if (x > SCREEN_WIDTH || x < 0 || y > SCREEN_HEIGHT || y < 0)
	{
		isActive = false;
	}

}//---



void GameObject::screenLimit()
{
	// Limit to edges
	bool stopMoving = false;
	if (x > SCREEN_WIDTH - SPRITE_SIZE)
	{
		stopMoving = true;
		x = SCREEN_WIDTH - SPRITE_SIZE;
	}
	if (x < 0)
	{
		stopMoving = true;
		x = 0;
	}
	if (y > SCREEN_HEIGHT - SPRITE_SIZE)
	{
		stopMoving = true;
		y = SCREEN_HEIGHT - SPRITE_SIZE;
	}
	if (y < 0)
	{
		stopMoving = true;
		y = 0;
	}

	if (stopMoving)
	{
		xVel = 0;
		yVel = 0;
	}
}//---

void GameObject::screenBounce()
{
	// bounce of edges by reversing velocity
	if (x > SCREEN_WIDTH - SPRITE_SIZE)  xVel = -xVel;
	if (x < 0) xVel = -xVel;
	if (y > SCREEN_HEIGHT - SPRITE_SIZE) yVel = -yVel;
	if (y < 0) yVel = -yVel;
}//---

void GameObject::screenWrap()
{
	// Screen Wrap to opposite side if sprite leaves screen
	if (x > SCREEN_WIDTH - SPRITE_SIZE)  x = 0;
	if (x < 0) x = SCREEN_WIDTH - SPRITE_SIZE;
	if (y > SCREEN_HEIGHT - SPRITE_SIZE) y = 0;
	if (y < 0) y = SCREEN_HEIGHT - SPRITE_SIZE;
}//---


// ======================================================= 
// Projectile Object
// ======================================================= 


Projectile::Projectile(const char* spriteFileName, int xPos, int yPos, float rotation, float spriteSize)
{
	Loadtexture(spriteFileName);	// Load Image from File
	bulletSize = spriteSize;
	x = xPos; 	y = yPos;
	angle = rotation;
	srcRect.h = srcRect.w = bulletSize;
	srcRect.x = srcRect.y = 0;
	destRect.h = destRect.w = bulletSize;
}//---

void Projectile::fire(float xSent, float ySent, float angleSent)
{
	if (!isActive)
	{
		isActive = true;
		x = xSent + SPRITE_SIZE / 2; // center the bullet
		y = ySent + SPRITE_SIZE / 2;
		angle = angleSent;
		xVel = sin(angle * M_PI / 180) * speed;
		yVel = -cos(angle * M_PI / 180) * speed;
	}
}//---


void Projectile::fireAtTarget(float startX, float startY, float targetX, float targetY)
{
	if (!isActive)
	{
		isActive = true;
		x = startX + SPRITE_SIZE / 2;
		y = startY + SPRITE_SIZE / 2;
		angle = atan2(targetX - x, targetY - y);
		xVel = sin(angle) * speed;
		yVel = cos(angle) * speed;
	}
}//---


void Projectile::renderProjectile()
{
	SDL_RenderCopyEx(Game::renderer, spriteTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
}//---


void Projectile::update(float frameTime)
{
	// Update Velocity
	x += xVel * frameTime;
	y += yVel * frameTime;

	disableOffScreen();

	//update Drawing Position Rect
	destRect.x = (int)x;
	destRect.y = (int)y;
}//---


// ======================================================= 
// PC Object 
// ======================================================= 

PlayerCharacter::PlayerCharacter(const char* spriteFileName, int xPos, int yPos, float rotation)
{
	Loadtexture(spriteFileName);	// Load Image from File
	x = xPos; 	y = yPos;
	angle = rotation;
	srcRect.h = srcRect.w = SPRITE_SIZE;
	srcRect.x = srcRect.y = 0;
	destRect.h = destRect.w = SPRITE_SIZE;
	destRect.x = (int)x; destRect.y = (int)y;
}//----


void PlayerCharacter::renderPC()
{
	// add the Sprite to the Render Image
	SDL_RenderCopyEx(Game::renderer, spriteTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
}//---


// ======================================================= 

void PlayerCharacter::updatePC(int keyPressed, float frameTime)
{
	// Set old Position for Collision detection
	oldX = x; oldY = y;

	// Limit Health
	if (health > maxHealth) health = maxHealth;	

	// Apply the movement
	stepMove(keyPressed);

	//update Drawing Position Rect
	destRect.x = (int)x;
	destRect.y = (int)y;
}//-----

// ======================================================= 

void PlayerCharacter::stepMove(int keyPressed)
{
	// WSAD
	if (keyPressed == 119) addY(-SPRITE_SIZE); //w
	if (keyPressed == 115) addY(SPRITE_SIZE); //S
	if (keyPressed == 97) addX(-SPRITE_SIZE); //A
	if (keyPressed == 100) addX(SPRITE_SIZE); //D

	screenLimit();
}///---

void PlayerCharacter::stop()
{
	xVel = yVel = 0;
	x = oldX;
	y = oldY;
}//--



// ======================================================= 
// NPC Objects 
// ======================================================= 

NPC::NPC(const char* spriteFileName, int xPos, int yPos, float rotation)
{
	Loadtexture(spriteFileName);
	x = xPos; 	y = yPos;
	angle = rotation;
	srcRect.h = srcRect.w = SPRITE_SIZE;
	srcRect.x = srcRect.y = 0;
	destRect.h = destRect.w = SPRITE_SIZE;
	destRect.x = (int)x; destRect.y = (int)y;
}//----

void NPC::renderNPC()
{
	// add the Sprite to the Render Image
	SDL_RenderCopyEx(Game::renderer, spriteTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);

}//---

void NPC::updateNPC()
{
	if (health < 0) isActive = false;

	//update Drawing Position Rect
	destRect.x = (int)x;
	destRect.y = (int)y;
}//-----

// ======================================================= 

void NPC::changeDirection()
{
	angle = rand() % 360 + 1;
	x = oldX;
	y = oldY;

}//---

void NPC::screenCrawl(float frameTime)
{
	if (xVel == 0) // Set some motion is the object is still
	{
		xVel = speed;
		yVel = -1;
	}

	if (x > SCREEN_WIDTH - (SPRITE_SIZE*3.35)) // hit RHS
	{
		x = SCREEN_WIDTH - (SPRITE_SIZE * 3.35);
		if (yVel < 0)
			y += SPRITE_SIZE;
		else
			y -= SPRITE_SIZE;
		xVel = -xVel;
	}
	if (x < 0 + SPRITE_SIZE * 1.025) // hit LHS
	{	
		x = 0 + (SPRITE_SIZE* 1.025);
		if (yVel < 0) {
			y += SPRITE_SIZE;
		}
		else
			y -= SPRITE_SIZE;
		xVel = -xVel;
	}

	x += xVel * frameTime;
}//---


// ======================================================= 