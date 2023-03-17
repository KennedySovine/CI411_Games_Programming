// ======================================================= 
// Libraries / Headers to include 
#include "GameObjects.h"


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
	// Load Image from File
	Loadtexture(spriteFileName);
	//Set the Sprite starting Screen Postion
	x = xPos; 	y = yPos;
	// Which part of the file to display
	srcRect.h = srcRect.w = SPRITE_SIZE;
	srcRect.x = srcRect.y = 0;
	// Where to display the Sprite
	destRect.h = destRect.w = SPRITE_SIZE;
	destRect.x = (int)x;	destRect.y = (int)y;
}
//Bullet game object
GameObject::GameObject(const char* spriteFileName, int xPos, int yPos, int anglePos)
{
	// Load Image from File
	Loadtexture(spriteFileName);
	//Set the Sprite starting Screen Postion
	x = xPos; 	y = yPos; angle = anglePos;
	// Which part of the file to display
	srcRect.h = srcRect.w = SPRITE_SIZE;
	srcRect.x = srcRect.y = 0;
	// Where to display the Sprite
	destRect.h = destRect.w = SPRITE_SIZE;
	destRect.x = (int)x;	destRect.y = (int)y;
}
//---

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
// PC Object 
// ======================================================= 

PlayerCharacter::PlayerCharacter(const char* spriteFileName, int xPos, int yPos, float rotation)
{
	// Load Image from File
	Loadtexture(spriteFileName);
	//Set the Sprite starting Screen Postion
	x = xPos; 	y = yPos;
	angle = rotation;
	// Which part of the file to display
	srcRect.h = srcRect.w = SPRITE_SIZE;
	srcRect.x = srcRect.y = 0;
	// Where to display the Sprite
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
	rotateMove(keyPressed, frameTime);

	//update Drawing Position Rect
	destRect.x = (int)x;
	destRect.y = (int)y;
}//-----


// ======================================================= 

void PlayerCharacter::rotateMove(int keyPressed, float frameTime)
{
	// Rotate PC
	if (keyPressed == 97) angle -= rotationSpeed * frameTime;
	if (keyPressed == 100) angle += rotationSpeed * frameTime;
		
	if (keyPressed == 119) // W  - Move Forward
	{
		xVel += sin(angle * M_PI / 180) * acceleration * frameTime;
		yVel -= cos(angle * M_PI / 180) * acceleration * frameTime;
	}
	if (keyPressed == 115) // S	  - Back
	{
		xVel -= sin(angle * M_PI / 180) * acceleration * frameTime;
		yVel += cos(angle * M_PI / 180) * acceleration * frameTime;
	}

	// Limit Speed
	if (xVel > speed) xVel = speed;
	if (yVel > speed) yVel = speed;
	if (xVel < -speed) xVel = -speed;
	if (yVel < -speed) yVel = -speed;

	// apply drag
	if (abs(xVel) > 0.3f) xVel *= drag; else xVel = 0;
	if (abs(yVel) > 0.3f) yVel *= drag; else yVel = 0;

	// Update positions
	x += xVel;
	y += yVel;

	// Limit Movement
	//screenLimit();
	screenWrap();
	//screenBounce();
}//---

// ======================================================= 

void PlayerCharacter::stepMove(int keyPressed)
{
	// WSAD
	if (keyPressed == 119) addY(-SPRITE_SIZE); //w
	if (keyPressed == 115) addY(SPRITE_SIZE); //S
	if (keyPressed == 97) addX(-SPRITE_SIZE); //A
	if (keyPressed == 100) addX(SPRITE_SIZE); //D
}///---

void PlayerCharacter::smoothMove(int keyPressed, float frameTime)
{
	// WSAD /// Add Acceleration
	if (keyPressed == 119) yVel -= acceleration * frameTime;
	if (keyPressed == 115) yVel += acceleration * frameTime;
	if (keyPressed == 97)  xVel -= acceleration * frameTime;
	if (keyPressed == 100) xVel += acceleration * frameTime;

	// Limit Speed
	if (xVel > speed) xVel = speed;
	if (yVel > speed) yVel = speed;
	if (xVel < -speed) xVel = -speed;
	if (yVel < -speed) yVel = -speed;

	// apply drag
	if (abs(xVel) > 0.3f) xVel *= drag; else xVel = 0;
	if (abs(yVel) > 0.3f) yVel *= drag; else yVel = 0;


	// Update positions
	x += xVel;
	y += yVel;

	//	screenLimit();
	screenWrap();
}//---

// ======================================================= 
// NPC Objects 
// ======================================================= 

NPC::NPC(const char* spriteFileName, int xPos, int yPos, float rotation)
{
	// Load Image from File
	Loadtexture(spriteFileName);
	//Set the Sprite starting Screen Postion
	x = xPos; 	y = yPos;
	angle = rotation;
	// Which part of the file to display
	srcRect.h = srcRect.w = SPRITE_SIZE;
	srcRect.x = srcRect.y = 0;
	// Where to display the Sprite
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
	//update Drawing Position Rect
	destRect.x = (int)x;
	destRect.y = (int)y;
}//-----

// ======================================================= 

void NPC::chasePC(float pcX, float pcY)
{
	if (x > pcX) x--;
	if (x < pcX) x++;
	if (y > pcY) y--;
	if (y < pcY) y++;	
}//---

void NPC::fleePC(float pcX, float pcY) {
	if (x > pcX) x++;
	if (x < pcX) x--;
	if (y > pcY) y++;
	if (y < pcY) y--;
}


void NPC::roam(float frameTime)
{
	// Move Forward
	xVel = sin(angle * M_PI / 180) * speed * frameTime ;
	yVel = -cos(angle * M_PI / 180) * speed * frameTime;

	// Randomise direction if NPC reach edges
	if (x > (SCREEN_WIDTH - SPRITE_SIZE) || x < 0 || y > SCREEN_HEIGHT - SPRITE_SIZE || y < 0)
	{
		angle = rand() % 360 + 1;
	}

	screenLimit();

	// Update positions
	x += xVel;
	y += yVel;
}//---


// ======================================================= 