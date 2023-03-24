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
NPC* npcs[10] = {};
Projectile* bulletsPC[10] = {};
Projectile* bulletsNPC[20] = {};


// ======================================================= 
void Game::createGameObjects()
{
	printf("\nCreating Game Objects");
	// Create Background
	backGround = new GameObject("assets/images/BG_Grid_800.png", 0, 0);
	backGround->setSize(800, 600); // as not a standard sprite size

	// Create Game Objects - filename , x and y pos, initial angle
	pc = new PlayerCharacter("assets/images/Triangle_Purple.png", 320, 520, 0);

	// Create an Array of NPCs
	for (int i = 0; i < sizeof(npcs) / sizeof(npcs[0]); i++)
	{
		int xPos = 32 + i * SPRITE_SIZE * 2;
		int yPos = 96;
		npcs[i] = new NPC("assets/images/Circle_Red.png", xPos, yPos, 0);
		npcs[i]->setAlive(true);
		npcs[i]->setSpeed(256);
		npcs[i]->setNextShotTime(rand() % 10000); // Set Random shot time upto 10 Secs
	}

	// Create the Array of items
	for (int i = 0; i < sizeof(items) / sizeof(items[0]); i++)
	{
		int xPos = 96 + rand() & 700;
		int yPos = 96 + rand() & 500;
		items[i] = new GameObject("assets/images/Star_Green.png", xPos, yPos);
		items[i]->setAlive(true);
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
		bulletsNPC[i] = new Projectile("assets/images/Circle_Red.png", -100, -100, 0, 8);
		bulletsNPC[i]->setBulletSpeed(250);
		bulletsNPC[i]->setDamage(20);
	}

}//----

// ======================================================= 

void Game::checkCollision()
{
	// Create the Rects for checking what collides
	SDL_Rect pcRect = { pc->getX(), pc->getY(), SPRITE_SIZE, SPRITE_SIZE };
	SDL_Rect objectRect = { -100,-100, SPRITE_SIZE, SPRITE_SIZE };
	SDL_Rect npcRect = { -100,-100, SPRITE_SIZE, SPRITE_SIZE };
	SDL_Rect bulletRect = { 0,0,0,0 };

	// Check if PC hits
	for (Projectile* bullet : bulletsNPC)  //  NPC Bullets -----------------
	{
		if (bullet->getAliveState() == true)
		{
			bulletRect.x = bullet->getX(); // Update the rect
			bulletRect.y = bullet->getY();
			bulletRect.w = bulletRect.h = bullet->getSize();

			if (SDL_HasIntersection(&pcRect, &bulletRect))
			{
				//npc->setAlive(false); // Disable the NPC 							
				pc->changeHP(-bullet->getDamage()); // Apply damage
				bullet->setAlive(false); // disable bullet
			}
		}
	}
		
	for (GameObject* item : items) // Pickups items
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

					if (SDL_HasIntersection(&npcRect, &bulletRect))
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
						bullet->fireAtTarget(npc->getX(), npc->getY(), pc->getX(), pc->getY());

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

void Game::update(float frameTime)
{
	// Ensure Frame rate is at the delay speed and convert to deltaTime
	if (frameTime < 1000 * (float)1 / FPS) frameTime = (float)1 / FPS;

	pc->updatePC(playerInput.keyPressed, frameTime);

	// Set NPC Behaviours
	for (NPC* npc : npcs)
	{
		if (npc->getAliveState())
		{
			//npc->roam(frameTime);
			npc->screenCrawl(frameTime);
			npc->updateNPC();
		}
	}

	for (GameObject* item : items) // Update Items
	{
		if (item->getAliveState() == true) item->update();
	}

	for (Projectile* bullet : bulletsPC) //--------- New Bullet
	{
		bullet->update(frameTime);
	}

	for (Projectile* bullet : bulletsNPC) //--------- New Bullet
	{
		bullet->update(frameTime);
	}

	checkAttacks();
	checkCollision();

	// Check if PC is alive
	if (pc->getHP() < 0) gameRunning = false;
}//---


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
	hpBar.w = SPRITE_SIZE * pc->getHP() / 100; ;
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

	for (GameObject* item : items)
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

	if (pc->getHP() < 0)
	{
		GameObject* splashScreen;
		splashScreen = new GameObject("assets/images/GameOverScreen.png", 0, 0);
		splashScreen->setSize(800, 600);
		splashScreen->render();
		SDL_RenderPresent(renderer);
		SDL_Delay(2000);
	}
	SDL_Delay(500);

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