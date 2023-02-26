// Libraries / Headers to include 
#include "Game.h"
#include "GameObjects.h"

// ======================================================= 
// SDL Variables
SDL_Renderer* Game::renderer = nullptr;;
SDL_Event Game::playerInputEvent;
// Game Objects
GameObject* pc = nullptr;
GameObject* npc = nullptr;
GameObject* backGround = nullptr;

// ======================================================= 
Game::Game() // Constructor
{
	printf(" \n\n ----- Game Started ------ \n");
}


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
	splashScreen->setSize(800,600);
	splashScreen->render();
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
}//---


// ======================================================= 
void Game::createGameObjects()
{
	printf("\n creating Game Objects");
	// Create Background
	backGround = new GameObject("assets/images/BG_Grid_800.png", 0, 0);
	backGround->setSize(800, 600); // as not a standard sprite size

	// Create Game Objects - filename , start  x and y position
	pc = new GameObject("assets/images/Star_Blue.png", 64, 64);
	npc = new GameObject("assets/images/Star_Red.png", 128, 64);

}//----



// ======================================================= 
void Game::handleEvents()
{
	SDL_PollEvent(&playerInputEvent);

	switch (playerInputEvent.type)
	{
	case SDL_QUIT:
	{
		gameRunning = false;
		break;
	}
	default:
		break;
	}
}//---

// ======================================================= 
void Game::update()
{
	//Update Game Objects
	pc->update();
	npc->update();

}//---

// ======================================================= 
void Game::render()
{
	SDL_RenderClear(renderer);

	// render Objects
	backGround->render();
	pc->render();
	npc->render();

	// Update the screen
	SDL_RenderPresent(renderer);
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