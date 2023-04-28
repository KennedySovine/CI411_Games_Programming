// Libraries / Headers to include 
#include "Game.h"
#include "GameObjects.h"
#include"Level.h"


// ======================================================= 
// SDL Variables
SDL_Renderer* Game::renderer = nullptr;;
SDL_Event Game::playerInputEvent;
GameInput playerInput;

// Game Objects
GameObject* backGround = nullptr;
PlayerCharacter* pc = nullptr;
GameObject* items[10] = {};
GameObject* health[10] = {};
NPC* npcs[15] = {};
Projectile* bulletsPC[10] = {};
Projectile* bulletsNPC[20] = {};
GameObject* terrainBlocks[200];
Levels* levelMaps = nullptr;

// Text
// Gobal Text Variables
TTF_Font* font = nullptr;
TTF_Font* font2 = nullptr;
SDL_Color textColour = { 255, 255, 200 };
SDL_Surface* textSurface = nullptr;
SDL_Texture* textTexture = nullptr;
int timeLevel = 0;
int previousTime = 0;

// ======================================================= 
void Game::createGameObjects()
{
	// Create Level Object
	levelMaps = new Levels;

	printf("\nCreating Game Objects");
	// Create Background
	backGround = new GameObject("assets/images/BG_Grid_800.png", 0, 0);
	backGround->setSize(800, 600); // as not a standard sprite size

	// Create Game Objects - filename , x and y pos, initial angle
	pc = new PlayerCharacter("assets/images/Pawn_Purple.png", 0, 0, 0);

	// Create an Array of NPCs
	for (int i = 0; i < sizeof(npcs) / sizeof(npcs[0]); i++)
	{
		npcs[i] = new NPC("assets/images/Circle_Red.png", 0, 0, 0);
		npcs[i]->setSpeed(64);
		npcs[i]->setNextShotTime(rand() % 10000); // Set Random shot time upto 10 Secs
	}

	// Create the Array of items
	for (int i = 0; i < sizeof(items) / sizeof(items[0]); i++)
	{
		items[i] = new GameObject("assets/images/Star_Red.png", 0, 0);
	}

	// Create the Array of health
	for (int i = 0; i < sizeof(health) / sizeof(health[0]); i++)
	{
		health[i] = new GameObject("assets/images/Star_Green.png", 0, 0);
	}

	//create PC bullets but do not enable
	for (int i = 0; i < sizeof(bulletsPC) / sizeof(bulletsPC[0]); i++)
	{
		bulletsPC[i] = new Projectile("assets/images/Circle_8.png", -100, -100, 0, 8);
		bulletsPC[i]->setBulletSpeed(300);
		bulletsPC[i]->setDamage(35);
	}

	//create NPC bullets but do not enable
	for (int i = 0; i < sizeof(bulletsNPC) / sizeof(bulletsNPC[0]); i++)
	{
		bulletsNPC[i] = new Projectile("assets/images/Circle_Red_8.png", -100, -100, 90, 8);
		bulletsNPC[i]->setBulletSpeed(250);
		bulletsNPC[i]->setDamage(20);
	}

	// Create Terrain Tiles
	srand(time(NULL)); // seed the random number for variation
	for (int i = 0; i < sizeof(terrainBlocks) / sizeof(terrainBlocks[0]); i++)
	{
		terrainBlocks[i] = new GameObject("assets/images/Square_Cross_Grey.png", 0, 0);
	}
	// Load Map  
	loadMap(1);
	currentLevel = 1;
}//----


void Game::loadMap(int levelNumber)
{
	std::cout << "\nLoading Level " << levelNumber;

	for (int row = 0; row < 18; row++)
	{
		for (int col = 0; col < 25; col++)
		{
			if (levelMaps->getTileContent(levelNumber, col, row) == 1) //  Terrain 
			{
				for (GameObject* block : terrainBlocks)
				{
					if (block->getAliveState() == false)
					{
						block->setAlive(true);
						block->setX(col * SPRITE_SIZE);
						block->setY(row * SPRITE_SIZE);
						break;
					}
				}
			}

			if (levelMaps->getTileContent(levelNumber, col, row) == 2) // PC
			{
				pc->setX(col * SPRITE_SIZE);
				pc->setY(row * SPRITE_SIZE);
			}

			if (levelMaps->getTileContent(levelNumber, col, row) == 3) //  NPC
			{
				for (NPC* npc : npcs)
				{
					if (npc->getAliveState() == false)
					{
						npc->setAlive(true);
						npc->setX(col * SPRITE_SIZE);
						npc->setY(row * SPRITE_SIZE);
						break;
					}
				}
			}

			if (levelMaps->getTileContent(levelNumber, col, row) == 4) //  Items
			{
				for (GameObject* item : health)
				{
					if (item->getAliveState() == false)
					{
						item->setAlive(true);
						item->setX(col * SPRITE_SIZE);
						item->setY(row * SPRITE_SIZE);
						break;
					}
				}
			}

			if (levelMaps->getTileContent(levelNumber, col, row) == 5) //  Items
			{
				for (GameObject* item : items)
				{
					if (item->getAliveState() == false)
					{
						item->setAlive(true);
						item->setX(col * SPRITE_SIZE);
						item->setY(row * SPRITE_SIZE);
						break;
					}
				}
			}
		}
	}
}//---

// ======================================================= 

void Game::resetAllObjects()
{
	// Turn off all objects

	for (GameObject* block : terrainBlocks)
		block->setAlive(false);

	for (NPC* npc : npcs)
	{
		npc->setAlive(false);
		npc->setHP(100); // reset NPC health

	}

	for (Projectile* bullet : bulletsPC)
		bullet->setAlive(false);


	for (Projectile* bullet : bulletsNPC)
		bullet->setAlive(false);

	for (GameObject* item : items) // Pickups items
		item->setAlive(false);

	for (GameObject* item : health) // Pickups items
		item->setAlive(false);

	// Reset PC stats
	pc->setHP(100);
	// anything else that need resetting

}//---

// ======================================================= 

void Game::checkCollision()
{
	// Create the Rects for checking what collides
	SDL_Rect pcRect = { pc->getX(), pc->getY(), SPRITE_SIZE, SPRITE_SIZE };
	SDL_Rect objectRect = { -100,-100, SPRITE_SIZE, SPRITE_SIZE };
	SDL_Rect npcRect = { -100,-100, SPRITE_SIZE, SPRITE_SIZE };
	SDL_Rect bulletRect = { 0,0,0,0 };

	// Set the PC's next Position by adding velocity
	SDL_Rect pcNextRect = { pc->getX() + pc->getVelX(), pc->getY() + pc->getVelY(), SPRITE_SIZE, SPRITE_SIZE };

	for (GameObject* block : terrainBlocks)  //  Terrain -----------------
	{
		if (block->getAliveState())
		{
			objectRect.x = block->getX();
			objectRect.y = block->getY();

			if (SDL_HasIntersection(&pcNextRect, &objectRect))  // PC -----
			{
				pc->stop(); // Stop the PC moving
			}

			for (NPC* npc : npcs) // NPCs ---------
			{
				if (npc->getAliveState() == true)
				{
					npcRect.x = npc->getX(); // Update the rect
					npcRect.y = npc->getY();

					if (SDL_HasIntersection(&npcRect, &objectRect))
					{
						npc->changeDirection();
					}
				}
			}

			for (Projectile* bullet : bulletsPC)  // PC  Bullets -----------------
			{
				if (bullet->getAliveState() == true)
				{
					bulletRect.x = bullet->getX(); // Update the rect
					bulletRect.y = bullet->getY();
					bulletRect.w = bulletRect.h = bullet->getSize();

					if (SDL_HasIntersection(&objectRect, &bulletRect))
					{
						bullet->setAlive(false); // disable bullet
					}
				}
			}
		}
	}


	for (Projectile* bullet : bulletsNPC)  //  NPC Bullets -----------------
	{
		if (bullet->getAliveState() == true)
		{
			bulletRect.x = bullet->getX(); // Update the rect
			bulletRect.y = bullet->getY();
			bulletRect.w = bulletRect.h = bullet->getSize();

			if (SDL_HasIntersection(&pcRect, &bulletRect))  //  PC ------
			{
				pc->changeHP(-bullet->getDamage()); // Apply damage
				bullet->setAlive(false); // disable bullet
			}

			for (GameObject* block : terrainBlocks)  //  Terrain ------
			{
				if (block->getAliveState())
				{
					objectRect.x = block->getX();
					objectRect.y = block->getY();

					if (SDL_HasIntersection(&objectRect, &bulletRect))
					{
						bullet->setAlive(false); // disable bullet
					}
				}
			}
		}
	}

	for (GameObject* item : health) // Health Pickups 
	{
		// Only check Alive Items
		if (item->getAliveState() == true)
		{
			objectRect.x = item->getX();
			objectRect.y = item->getY();

			if (SDL_HasIntersection(&pcRect, &objectRect))
			{
				item->setAlive(false); // Disable the item hit
				pc->changeHP(50);
			}
		}
	}

	for (GameObject* item : items) // Health Pickups 
	{
		// Only check Alive Items
		if (item->getAliveState() == true)
		{
			objectRect.x = item->getX();
			objectRect.y = item->getY();

			if (SDL_HasIntersection(&pcRect, &objectRect))
			{
				item->setAlive(false); // Disable the item hit
			}
		}
	}


	// check what alive NPCs hit -
	for (NPC* npc : npcs)
	{
		if (npc->getAliveState() == true)
		{
			npcRect.x = npc->getX(); // Update the rect
			npcRect.y = npc->getY();

			for (Projectile* bullet : bulletsPC)  // PC  Bullets -----------------
			{
				if (bullet->getAliveState() == true)
				{
					bulletRect.x = bullet->getX(); // Update the rect
					bulletRect.y = bullet->getY();
					bulletRect.w = bulletRect.h = bullet->getSize();

					if (SDL_HasIntersection(&npcRect, &bulletRect)) // NPC
					{
						//npc->setAlive(false); // Disable the NPC 						
						npc->changeHP(-bullet->getDamage()); // Apply damage

						bullet->setAlive(false); // disable bullet
					}
				}
			}
		}
	}

}//---

// ======================================================= 

void Game::checkAttacks()
{
	if (playerInput.keyPressed == 32) // Space 
	{
		// find the first inactive bullet and enable it at the PC Position
		for (Projectile* bullet : bulletsPC)
		{
			if (bullet->getAliveState() == false)
			{	// fire in the direction the pc is facing
				bullet->fire(pc->getX(), pc->getY(), pc->getAngle());
				break; // stop checking the array
			}
		}
	}

	if (playerInput.mouseL) //  L Mouse 
	{
		// find the first inactive bullet and enable it at the PC Position
		for (Projectile* bullet : bulletsPC)
		{
			if (bullet->getAliveState() == false)
			{	// fire at the mouse
				bullet->fireAtTarget(pc->getX(), pc->getY(), playerInput.mouseX, playerInput.mouseY);
				break; // stop checking the array
			}
		}
	}

	// NPC attacks
	for (NPC* npc : npcs)
	{
		if (npc->getAliveState() == true)
		{
			if (npc->getNextShotTime() < SDL_GetTicks())
			{
				// find the first inactive bullet and enable it at the PC Position
				for (Projectile* bullet : bulletsNPC)
				{
					if (bullet->getAliveState() == false)
					{
						// Fire at PC
						bullet->fireAtTarget(npc->getX(), npc->getY(), pc->getX(), pc->getY());

						// fire Down
						//bullet->fireAtTarget(npc->getX(), npc->getY(), npc->getX(), SCREEN_HEIGHT);

						// Set Random shot time - Current time + 3s + random upto 7s
						npc->setNextShotTime(SDL_GetTicks() + 3000 + rand() % 7000);
						break; // stop checking the bullet array
					}
				}
			}
		}
	}
}//---

// ======================================================= 

void Game::checkGameStates()
{
	activeItems = 0;
	for (GameObject* item : items)
	{
		if (item->getAliveState()) activeItems++;
	}

	activeNPCs = 0;
	for (NPC* npc : npcs)
	{
		if (npc->getAliveState()) activeNPCs++;
	}

	timeLevel = (SDL_GetTicks64() / 1000) - previousTime;

	// Check NPCs are cleared
	//if (activeNPCs == 0) gameRunning = false;

	// Check Items
	//if (activeItems == 0) gameRunning = false;

	//NPCS and Items cleared
	if (activeNPCs == 0 && activeItems == 0) gameRunning = false;

	//Time limit
	if (timeLevel >= 30) {
		gameRunning = false;
	}


	// Check if PC is alive
	if (pc->getHP() < 0) gameRunning = false;


}//---



// ======================================================= 


void Game::update(float frameTime)
{
	// frametime is fixed at 1 / FPS rate
	frameTime = static_cast<float>(1) / FPS;

	pc->updatePC(playerInput.keyPressed, frameTime);

	// Set NPC Behaviours
	for (NPC* npc : npcs)
	{
		if (npc->getAliveState())
		{
			npc->roam(frameTime);
			npc->updateNPC();		
		}
	}

	for (GameObject* block : terrainBlocks)
	{
		if (block->getAliveState()) block->update();
	}

	for (GameObject* item : items) // Update Items
	{
		if (item->getAliveState() == true) item->update();
	}

	for (GameObject* item : health) // Update Items
	{
		if (item->getAliveState() == true) item->update();
	}

	for (Projectile* bullet : bulletsPC) //--------- New Bullet
	{
		if (bullet->getAliveState()) bullet->update(frameTime);
	}

	for (Projectile* bullet : bulletsNPC) //--------- New Bullet
	{
		if (bullet->getAliveState()) bullet->update(frameTime);
	}

	checkAttacks();
	checkCollision();
	checkGameStates();

}//---


// =======================================================
void Game::updateGUI()
{
	std::string  screenText;
	SDL_Rect textRect = { 8,8,0,0 }; // start position of the text

	// text to be on screen Left Side	
	screenText = "Level: " + std::to_string(currentLevel);
	screenText += "  Items: " + std::to_string(activeItems);
	screenText += "  NPCs: " + std::to_string(activeNPCs);

	textColour = { 255, 255, 0 };

	// render the text to screen
	textSurface = TTF_RenderText_Blended_Wrapped(font, screenText.c_str(), textColour, 0);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	// Clear the memory
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	// text to be on screen Right Side
	textRect = { 400,580,0,0 }; // start position of the text
	screenText = "HP: " + std::to_string(int(pc->getHP()));
	screenText += "      Time: " + std::to_string(timeLevel);
	textColour = { 0, 255, 0 };

	// render the text to screen
	textSurface = TTF_RenderText_Blended_Wrapped(font2, screenText.c_str(), textColour, 0);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	// Clear the memory
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

}//--



// ======================================================= 


void Game::drawHPBars()
{
	SDL_Rect hpBar{ 0,0,0,0 };

	for (NPC* npc : npcs) //Draw NPC Bars
	{
		if (npc->getAliveState())
		{
			hpBar.h = 2;
			hpBar.w = SPRITE_SIZE * npc->getHP() / 100; ;
			hpBar.x = npc->getX();
			hpBar.y = npc->getY() - 10;

			// Colour of HP Bar
			if (npc->getHP() >= 50) // Green
				SDL_SetRenderDrawColor(Game::renderer, 0, 200, 00, 255);

			else if (npc->getHP() >= 25 && npc->getHP() < 50) // Yellow
				SDL_SetRenderDrawColor(Game::renderer, 250, 250, 0, 255);

			else // Red
				SDL_SetRenderDrawColor(Game::renderer, 250, 0, 0, 255);

			SDL_RenderDrawRect(Game::renderer, &hpBar);
		}
	}

	// Draw PC Bar
	hpBar.w = SPRITE_SIZE * pc->getHP() / 100;
	hpBar.x = pc->getX();
	hpBar.y = pc->getY() - 10;

	// Colour of HP Bar
	if (pc->getHP() >= 50) // Green
		SDL_SetRenderDrawColor(Game::renderer, 0, 200, 00, 255);

	else if (pc->getHP() >= 25 && pc->getHP() < 50) // Yellow
		SDL_SetRenderDrawColor(Game::renderer, 250, 250, 0, 255);

	else // Red
		SDL_SetRenderDrawColor(Game::renderer, 250, 0, 0, 255);

	SDL_RenderDrawRect(Game::renderer, &hpBar);
}//----



// ======================================================= 
void Game::render()
{
	SDL_RenderClear(renderer);
	backGround->render();
	for (GameObject* block : terrainBlocks)
	{
		if (block->getAliveState() == true)  block->render();
	}
	for (GameObject* item : items)
	{
		if (item->getAliveState() == true)  item->render();
	}
	for (GameObject* item : health)
	{
		if (item->getAliveState() == true)  item->render();
	}
	for (NPC* npc : npcs)
	{
		if (npc->getAliveState()) npc->renderNPC();
	}
	for (Projectile* bullet : bulletsPC)
	{
		if (bullet->getAliveState()) bullet->renderProjectile();
	}
	for (Projectile* bullet : bulletsNPC)
	{
		if (bullet->getAliveState()) bullet->renderProjectile();
	}
	pc->renderPC();
	drawHPBars();
	updateGUI();
	SDL_RenderPresent(renderer); 	// Update the screen
}//---

// ======================================================= 
void Game::handleEvents()
{
	// Reset Inputs
	playerInput.keyPressed = NULL;
	playerInput.mouseL = false;
	playerInput.mouseR = false;

	//Check for Events
	SDL_PollEvent(&playerInputEvent);

	switch (playerInputEvent.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		replay = false;
		break;

	case SDL_MOUSEMOTION: //--------- New Input
		int mouseXpos, mouseYpos;
		SDL_GetMouseState(&mouseXpos, &mouseYpos);
		playerInput.mouseX = mouseXpos;
		playerInput.mouseY = mouseYpos;

	case SDL_MOUSEBUTTONDOWN: //--------- New Input
		if (playerInputEvent.button.button == SDL_BUTTON_LEFT) playerInput.mouseL = true;
		if (playerInputEvent.button.button == SDL_BUTTON_RIGHT) playerInput.mouseR = true;

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

		// Initialise Fonts
		TTF_Init();
		font = TTF_OpenFont("assets/fonts/arial.ttf", 22); // size is the last value
		font2 = TTF_OpenFont("assets/fonts/bubble_pixel-7_dark.ttf", 18); // size is the last value
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

	// Load a Background to cover the sprites
	GameObject* background;
	background = new GameObject("assets/images/Square_grey.png", 0, 0);
	background->setSize(800, 600);
	background->render();
	SDL_RenderPresent(renderer);

	// text Variables
	std::string screenText;
	textColour = { 0, 0, 0 };
	SDL_Rect textRect = { 100, 150,0,0 }; // start position of the text	

	screenText = "Welcome to CI411 example Game";
	screenText += "\n \n \n\n Collect all the Red Stars to complete a level";
	screenText += "\n \n Watch out for the Angry Tomatoes";
	screenText += "\n \n WASD to Move and Mouse to shoot";
	screenText += "\n \n \n\n\n Press any key to start";

	// render the text to screen
	textSurface = TTF_RenderText_Blended_Wrapped(font2, screenText.c_str(), textColour, 0);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_RenderPresent(renderer);
	// Clear the memory
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	// Wait for key press or mouse click
	bool exitLoop = false;
	while (!exitLoop)
	{
		SDL_PollEvent(&playerInputEvent);
		if (playerInputEvent.type == SDL_MOUSEBUTTONDOWN || playerInputEvent.type == SDL_KEYDOWN)
		{
			exitLoop = true;
		}
	}

}//---

// ======================================================= 
void Game::levelCompleteScreen()
{
	// Load a Background to cover the sprites
	GameObject* background;
	background = new GameObject("assets/images/Square_grey.png", 0, 0);
	background->setSize(800, 600);
	background->render();
	SDL_RenderPresent(renderer);
	// text Variables
	std::string screenText;
	textColour = { 0, 0, 0 };
	SDL_Rect textRect = { 200, 250,0,0 }; // start position of the text		

	if (pc->getHP() < 0) // PC Died - replay current level
	{
		// Display Retry Message
		screenText = "    Your Character Died \n \nPress any key to try again";
		previousTime += timeLevel;
		resetAllObjects();
		// reload the same map
		if (currentLevel == 1) loadMap(1);
		if (currentLevel == 2) loadMap(2);
		if (currentLevel == 3) loadMap(3);
	}
	else if (timeLevel >= 30) // Ran out of time
	{
		// Display Retry Message
		screenText = "    You ran out of time \n \nPress any key to try again";
		previousTime += timeLevel;
		resetAllObjects();
		// reload the same map
		if (currentLevel == 1) loadMap(1);
		if (currentLevel == 2) loadMap(2);
		if (currentLevel == 3) loadMap(3);
	}
	else // level complete move on
	{
		// Display Continue Message
		screenText = "             Well Done\n \nPress any key to try next level";	
		previousTime += timeLevel;
		resetAllObjects();
		// load the next map
		if (currentLevel == 1)
		{
			loadMap(2);
			currentLevel = 2;
		}
		else if (currentLevel == 2)
		{
			loadMap(3);
			currentLevel = 3;
		}
		else if (currentLevel == 3)
		{
			screenText = "Well Done, You completed the game \n\nPress any key to play again";
			loadMap(1);
			currentLevel = 1;
		}
	}
	// render the text to screen
	textSurface = TTF_RenderText_Blended_Wrapped(font2, screenText.c_str(), textColour, 0);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_RenderPresent(renderer);
	// Clear the memory
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	// Pause to ensure game actions have stopped
	SDL_Delay(2000);
	// Wait for key press or mouse click
	bool exitLoop = false;
	while (!exitLoop)
	{
		SDL_PollEvent(&playerInputEvent);
		if (playerInputEvent.type == SDL_MOUSEBUTTONDOWN || playerInputEvent.type == SDL_KEYDOWN)
		{
			exitLoop = true;
		}
	}
	gameRunning = true;
}//---



// ======================================================= 
void Game::exitScreen()
{
	// Load a Background to cover the sprites
	GameObject* background;
	background = new GameObject("assets/images/Square_grey.png", 0, 0);
	background->setSize(800, 600);
	background->render();
	SDL_RenderPresent(renderer);

	// text Variables
	std::string screenText;
	textColour = { 0, 0, 0 };
	SDL_Rect textRect = { 250, 250,0,0 }; // start position of the text	

	screenText = "Thanks for Playing\n \n     Good Bye";

	// render the text to screen
	textSurface = TTF_RenderText_Blended_Wrapped(font2, screenText.c_str(), textColour, 0);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_RenderPresent(renderer);
	// Clear the memory
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	SDL_Delay(1000);

}//---




// ======================================================= 
void Game::closeSDL() // Clear Memory and exit SDL
{
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(font);
	TTF_CloseFont(font2);
	TTF_Quit();
	SDL_Quit();
	std::cout << "\nSDL Closed \n";
}//---

// ======================================================= 
Game::Game() // Constructor
{
	printf(" \n\n ----- Game Started ------ \n");
}

// ======================================================= 