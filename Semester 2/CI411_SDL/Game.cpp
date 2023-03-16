// Libraries / Headers to include 
#include "Game.h"
#include "GameObjects.h"

// ======================================================= 
// SDL Variables
SDL_Renderer* Game::renderer = nullptr;;
SDL_Event Game::playerInputEvent;
GameInput playerInput;

// Game Objects
GameObject* backGround = nullptr;
PlayerCharacter* pc = nullptr;
GameObject* items[5] = {};
NPC* npcs[5] = {};



// ======================================================= 
void Game::createGameObjects()
{
	printf("\nCreating Game Objects");
	// Create Background
	backGround = new GameObject("assets/images/BG_Grid_800.png", 0, 0);
	backGround->setSize(800, 600); // as not a standard sprite size

	// Create Game Objects - filename , x and y pos, initial angle
	pc = new PlayerCharacter("assets/images/Pawn_Blue.png", 64, 64, 0);

	// Create an Array of NPCs
	for (int i = 0; i < sizeof(npcs) / sizeof(npcs[0]); i++)
	{
		int xPos = 320 + i * SPRITE_SIZE * 2;
		int yPos = 320;
		npcs[i] = new NPC("assets/images/Pawn_Red.png", xPos, yPos, 0);
		npcs[i]->setAlive(true);		
	}	
	
	// Set Properties for individual npcs
	npcs[2]->setSpeed(48);
	npcs[3]->setSpeed(96);


	// Create the Array of items
	for (int i = 0; i < sizeof(items) / sizeof(items[0]); i++)
	{
		int xPos = 320 + i * SPRITE_SIZE * 2;
		int yPos = 480;
		items[i] = new GameObject("assets/images/Star_Yellow.png", xPos, yPos);
		items[i]->setAlive(true);
	}
}//----


void Game::checkCollision()
{
	// Check if PC hit items
	SDL_Rect objectRect = {-100,-100, SPRITE_SIZE, SPRITE_SIZE};
	SDL_Rect pcRect = { pc->getX(), pc->getY(), SPRITE_SIZE, SPRITE_SIZE};

	for (int i = 0; i < sizeof(items) / sizeof(items[0]); i++)
	{
		// Only check Alive Items
		if (items[i]->getAliveState() == true)
		{	
			objectRect.x = items[i]->getX();
			objectRect.y = items[i]->getY();

			if (SDL_HasIntersection(&pcRect, &objectRect) )
			{
				items[i]->setAlive(false); // Disable the item hit
			}
		}
	}

}//---



// ======================================================= 
void Game::update(float frameTime)
{
	// Ensure Frame rate is at the delay speed and convert to deltaTime
	if (frameTime < 1000 * (float)1 / FPS) frameTime = (float)1 / FPS;		
	
	pc->updatePC(playerInput.keyPressed, frameTime);

	// NPCs
	npcs[1]->chasePC(pc->getX(), pc->getY());
	npcs[2]->roam(frameTime);
	npcs[3]->roam(frameTime);

	for (NPC* npc : npcs) // Update NPCs
	{
		if (npc->getAliveState()) npc->updateNPC();
	}

	for (int i = 0; i < sizeof(items) / sizeof(items[0]); i++) // Update Items
	{
		if (items[i]->getAliveState() == true) items[i]->update();
	}

	checkCollision();
}//---

// ======================================================= 
void Game::render()
{
	SDL_RenderClear(renderer);
		
	backGround->render();	

	for (int i = 0; i < sizeof(items) / sizeof(items[0]); i++)
	{
		if (items[i]->getAliveState() == true)  items[i]->render();
	}

	for (NPC* npc : npcs)
	{
		if(npc->getAliveState()) npc->renderNPC();
	}
	
	pc->renderPC();

	// Update the screen
	SDL_RenderPresent(renderer);
}//---

// ======================================================= 
void Game::handleEvents()
{
	// Reset Inputs
	playerInput.keyPressed = NULL;

	//Check for Events
	SDL_PollEvent(&playerInputEvent);

	switch (playerInputEvent.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;

	case SDL_KEYDOWN:
		//std::cout << "\n" << playerInputEvent.key.keysym.sym;
		playerInput.keyPressed = playerInputEvent.key.keysym.sym;
		break;

	default:
		break;
	}
}//---

// ======================================================= 
void Game::startSDL(const char* title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "\nSDL Initialised  \n";

		gameWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

		if (gameWindow) printf("\nGame Window Created ");

		renderer = SDL_CreateRenderer(gameWindow, -1, 0);

		if (renderer) printf("\nRenderer Created \n");

		gameRunning = true;
	}
	else
	{
		gameRunning = false;
	}
}//---

// ======================================================= 

void Game::welcomeScreen()
{
	GameObject* splashScreen;
	splashScreen = new GameObject("assets/images/Start_Screen_800.png", 0, 0);
	splashScreen->setSize(800, 600);
	splashScreen->render();
	SDL_RenderPresent(renderer);
	SDL_Delay(500);
}//---

// ======================================================= 
void Game::exitScreen()
{
	printf("\n\n ----- Thank you for playing -----");
	SDL_Delay(1000);
}//---

// ======================================================= 
void Game::closeSDL() // Clear Memory and exit SDL
{
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "\nSDL Closed \n";
}//---

// ======================================================= 
Game::Game() // Constructor
{
	printf(" \n\n ----- Game Started ------ \n");
}

// ======================================================= 