// =======================================================
// CI411_Week10
// Kennedy Sovine UoBGames, 7/12/2022
// =======================================================
// 
// Libraries to include
#include <iostream>
using namespace std;
#include "GameObjects.h"

// =======================================================
// Function Declaration

// =======================================================
// Global Variables

PC PC1("Geoffry", 100, "none", 50);
NPC NPC1("water");
Character Character1("Bob", 100);

// =======================================================
int main() {
	
	cout << "\nCharacter Stats: \n\n";

	PC1.displayStats();
	NPC1.displayStats();
	Character1.displayStats();

	return 0;
}
// =======================================================
// Functions & Class Methods


// =====================================================