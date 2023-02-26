// =======================================================
// CI411 Sem 2
// Kennedy Sovine UoBGames, 2023
// Date: Febuary 10, 2023
// =======================================================

// Libraries to include
#include <SDL.h>
#include <iostream>

//Function definitions
void createWindow();
void referencesExamples();

void referencesFunctionsEx();
void addBonus(int& scoreSent);

void pointerExample();

// =======================================================
int main(int argc, char* args[]){
	
	referencesExamples();
	referencesFunctionsEx();
	pointerExample();

	return 0;
}
//---

void createWindow() {

	printf("SDL test");
	SDL_Window* gameWindow = NULL;
	//Create window
	gameWindow = SDL_CreateWindow("C411 - SDL Test", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (gameWindow == NULL) printf(" Window Error %s\n", SDL_GetError());
	SDL_Delay(5000);
	SDL_Quit;
}

void referencesExamples() {

	printf("Reference Example\n");

	std::string weapon = "Sword";
	std::string& carrying = weapon;

	std::cout << "\n" << weapon;
	std::cout << "\n" << carrying;

	carrying = "Axe";
	std::cout << "\n" << weapon << std::endl;

}

void addBonus(int& scoreSent) {
	int bonus = 500;
	scoreSent += bonus;
}
void referencesFunctionsEx() {
	
	printf("\nReference Function Example \n");

	int score = 1000;
	std::cout << "\nscore: " << score;
	std::cout << "\nadding bonus";

	addBonus(score);

	std::cout << "\nscore: " << score;

	std::cout << "\nMemory address: " << &score;
}

void pointerExample() {
	printf("\nPointer Example \n");

	std::string weapon = "Sword";
	std::string* weaponPointer = &weapon;

	std::cout << "\n weapon     " << weapon;
	std::cout << "\n pointer:   " << weaponPointer;
	std::cout << "\n weapon Ref " << &weapon;
	std::cout << "\n pointer content: " << *weaponPointer;
}