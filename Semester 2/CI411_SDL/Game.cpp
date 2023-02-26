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
GameObject* npc_2 = nullptr;
GameObject* tiles[1000];
GameObject* backGround = nullptr;
GameObject* tiles2D[100][100];

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
	splashScreen->setSize(800, 600);
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
	pc = new GameObject("assets/images/Star_Blue.png", 49, 164);
	npc = new GameObject("assets/images/Star_Red.png", 108, 94);
	npc_2 = new GameObject("assets/images/Star_Yellow.png", 80, 100);

	//Make the straight line of objects
	for (int i = 0; i < (sizeof(tiles) / sizeof(tiles[0])); i++) {
		tiles[i] = new GameObject("assets/images/Star_Yellow.png", i, i);
	}

	//Make the 2D array of stuff
	for (int row = 0; row < (sizeof(tiles2D) / sizeof(tiles2D[0])); row++) {
		for (int col = 0; col < (sizeof(tiles2D) / sizeof(tiles2D[0])); col++) {
			for (int i = 0; i < 600; i + 10) {
				tiles2D[row][col] = new GameObject("assets/images/Star_Yellow.png", i, i);
				if (i == 600) {
					break;
				}
			}
		}
	}

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
	npc_2->update();

	for (int i = 0; i < (sizeof(tiles) / sizeof(tiles[0])); i++) {
		tiles[i]->update();
	}


	for (int row = 0; row < (sizeof(tiles2D) / sizeof(tiles2D[0])); row++) {
		for (int col = 0; col < (sizeof(tiles2D) / sizeof(tiles2D[0])); row++) {
			tiles2D[row][col]->update();
		}
	}



}//---

// ======================================================= 
void Game::render()
{
	SDL_RenderClear(renderer);

	// render Objects
	backGround->render();
	pc->render();
	npc->render();
	npc_2->render();
	for (int i = 0; i < (sizeof(tiles) / sizeof(tiles[0])); i += SPRITE_SIZE / 3) {
		tiles[i]->render();
	}
	/*for (int row = 0; row < (sizeof(tiles2D) / sizeof(tiles2D[0])); row += SPRITE_SIZE / 3) {
		for (int col = 0; col < (sizeof(tiles2D) / sizeof(tiles2D[0])); col += SPRITE_SIZE / 3) {
			tiles2D[row][col]->render();
		}
	}*/

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

// ============================================================ 