// =======================================================
// CI411_Week9
// Kennedy Sovine UoBGames, 30/11/2022
// =======================================================
// 
// Libraries to include
#include <iostream>
using namespace std;

// =======================================================
// Function Declaration

// =======================================================
// Classes 

class Character {
public:
	string name;
	float health, speed;
	bool isAlive;

	void checkIsAlive() {
		if (health <= 0) {
			isAlive = false;
		}
	}
	void displayStats();

	Character() {
		name = "";
		health = 100;
		speed = 5;
		isAlive = true;

		cout << "Character has been spawned! ";
	}

	Character(string nameSet, float healthSet);
};

class NPC : public Character {
public:
	string faction, message;

	NPC(string factionSet);
};

class PC : public Character {
public:
	string potionCarrying;
	int mana;

	void displayStats();

	PC(string nameSet, float healthSet, string potionSet, int manaSet);
};

// =======================================================
// Global Variables

// =======================================================
int main(){
	
	Character player1;
	Character player2;

	player2.health = 0;

	player1.checkIsAlive();
	player2.checkIsAlive();

	player1.displayStats();
	player2.displayStats();

	Character player3("player3", 80);
	Character player4("player4", 97);

	NPC NPC1("water");
	PC PC1("PC1", 100, "Mana", 20);

	return 0;
}
// =======================================================
// Functions & Class Methods

 void Character::displayStats() {
	cout << "Stats for: " << name << endl;
	cout << "----------" << endl;
	cout << "Health: " << (int)health << " Speed: " << (int)speed << " Alive: " << isAlive << endl << endl;;
}

void PC::displayStats() {
	cout << "Stats for: " << name << endl;
	cout << "----------" << endl;
	cout << "Health: " << (int)health << " Mana: " << mana << " Speed: " << (int)speed << " Potion Carrrying: " << potionCarrying << " Alive: " << isAlive << endl << endl;;
}

Character::Character(string nameSet, float healthSet) {
	name = nameSet;
	health = healthSet;
	speed = 5;
	isAlive = true;

	cout << "Character has been spawned! ";
	cout << "Name: " << name << " Health: " << health << endl << endl;;
}

NPC::NPC(string factionSet) {
	if (factionSet == "water") {
		faction = "water";
		message = "An NPC from the water faction has spawned! ";
	}
	else if (factionSet == "fire") {
		faction = "fire";
		message = "An NPC from the fire faction has spawned! ";
	}
	else if (factionSet == "earth") {
		faction = "earth";
		message = "An NPC from the earth faction has spawned! ";

	}
	else if (factionSet == "air") {
		faction = "air";
		message = "An NPC from the air faction has spawned! ";
	}
	else {
		faction = "nomad";
		message = "An NPC without a faction has spawned! ";
	}
	cout << message << endl;
}

PC::PC(string nameSet, float healthSet, string potionSet, int manaSet) {
	name = nameSet;
	health = healthSet;
	potionCarrying = potionSet;
	mana = manaSet;
	speed = 5;
	isAlive = true;

	cout << "A PC has been spawned! ";
	cout << "Name: " << name << " Health: " << health << " Mana: " << mana << " Potion: " << potionCarrying << endl << endl;
}

// =====================================================