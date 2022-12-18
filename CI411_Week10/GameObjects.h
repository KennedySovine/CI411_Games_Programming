#pragma once
#include <iostream>
using namespace std;

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
	void displayStats();
};

class PC : public Character {
public:
	string potionCarrying;
	int mana;

	void displayStats();

	PC(string nameSet, float healthSet, string potionSet, int manaSet);
};