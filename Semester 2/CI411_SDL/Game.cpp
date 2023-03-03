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
GameObject* npcs[5] = {};


// ======================================================= 
void Game::createGameObjects()
{
	printf("\n creating Game Objects");
	// Create Background
	backGround = new GameObject("assets/images/BG_Grid_800.png", 0, 0);
	backGround->setSize(800, 600); // as not a standard sprite size

	// Create Game Objects - filename , start  x and y position
	pc = new PlayerCharacter("assets/images/Star_Blue.png", 64, 64);

	// Create thg Array of NPCs
	for (int i = 0; i < sizeof(npcs) / sizeof(npcs[0]); i++)
	{
		int xPos = 320 + i * SPRITE_SIZE;
		int yPos = 480;
		npcs[i] = new GameObject("assets/images/Star_Yellow.png", xPos, yPos);
		npcs[i]->setAlive(true);
	}
}//----

// ======================================================= 
void Game::update(float frameTime)
{
	//Update PC
	pc->movePCStep(playerInput.keyPressed);
	//	pc->movePCSmooth(playerInput.keyPressed, frameTime);	
	pc->updatePC();

	// NPCs
	for (int i = 0; i < sizeof(npcs) / sizeof(npcs[0]); i++)
	{
		npcs[i]->update();
	}

}//---

// ======================================================= 
void Game::render()
{
	SDL_RenderClear(renderer);
	// render Objects
	backGround->render();	
	pc->renderPC();
	
	// Render All NPCs
	for (int i = 0; i < sizeof(npcs) / sizeof(npcs[0]); i++)
	{
		if (npcs[i]->getAliveState() == true)  npcs[i]->render();
	}

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
		std::cout << "\n" << playerInputEvent.key.keysym.sym;
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
	SDL_Delay(2000);
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