// =======================================================
// CI411 Sem 2 - SDL Game
// Kennedy Sovine UoBGames, 2023
// =======================================================

// Libraries / Headers to include 
#include "Game.h" 

// Variables
Game* game = nullptr;

// ======================================================= 
int main(int argc, char* argv[])
{
	// Frame Limit Variables
	const int frameDelay = 1000 / FPS;
	Uint64 frameStart, frameTime;

	// Create the Game Object
	game = new Game;

	// Start SDL & Create the Game Window
	game->startSDL("CI411 SDL Example");	
	game->welcomeScreen();
	game->createGameObjects();

	// Main Game Loop
	while (game->isRunning())
	{
		frameStart = SDL_GetTicks64();

		game->handleEvents();
		game->update();
		game->render();

		// Limit Frame Rate
		frameTime = SDL_GetTicks64() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}

	game->exitScreen();
	game->closeSDL();

	return 0;
}//---







