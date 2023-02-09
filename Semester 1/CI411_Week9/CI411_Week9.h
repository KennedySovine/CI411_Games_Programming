#pragma once
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
		name = "NPC";
		health = 100;
		speed = 5;
		isAlive = true;
	}

	Character(string nameSet) {
		health = 100;
		speed = 5;
		isAlive = true;
	}
};

