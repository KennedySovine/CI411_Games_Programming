#include <iostream>
using namespace std;
#include "GameObjects.h"

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

void NPC::displayStats() {
	cout << "Stats for: " << name << endl;
	cout << "----------" << endl;
	cout << "Health: " << (int)health << " Faction: " << faction << endl << endl;;
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