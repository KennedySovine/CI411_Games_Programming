// CI411_Week3
// Kennedy Sovine, UoB 2022

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void testComp() {

	int x = 20, y = 18;

	if (x == y) {
		cout << "x is equal to y" << endl;
	}
	else {
		cout << "x is not equal to y" << endl;
	}

	if (x > y) {
		cout << "x is greater than y" << endl;
	}
	else {
		cout << "x is less than y" << endl;
	}
}

void scoreCheck() {

	int score = 0;

	cout << "Enter a score value" << endl;
	cin >> score;

	if (score > 1000) {
		cout << "Great Score!" << endl;
	}
	else if (score > 500) {
		cout << "Good Score!" << endl;
	}
	else {
		cout << "You're score is low" << endl;
	}
}

void menuSelect() {
	int choice = 0;
	cout << "=== Option Menu ===" << endl;

	cout << "Please Select the program to run" << endl;
	cout << " 1: Circle Calculator\n 2: Missle Range Calculator\n 3: Attack Damage Calculator\n 4: Exit Programme" << endl;
	cin >> choice;


	if (choice == 1) {
		const float PI = 3.142;
		float radius;

		//User Input
		cout << "Please enter a value for the radius:  ";
		cin >> radius;

		//Math
		float diameter = 2 * radius;
		float circumference = 2 * PI * radius;
		float area = PI * (radius * radius);

		//Output
		cout << "\n\nDiameter: " << diameter << endl << endl;
		cout << "Circumference: " << circumference << endl << endl;
		cout << "Area: " << area << endl << endl;
	}

	else if (choice == 2) {
		float speed;
		float range;

		cout << "Please input the missile speed (m/s)" << endl;
		cin >> speed;
		cout << "Please input the missile range (m)" << endl;
		cin >> range;

		cout << "Time taken to travel = " << 1.0 * (range / speed) << " seconds" << endl << endl << endl;
	}

	else if (choice == 3) {
		//User Inputs
		float hp = 100.0;
		float ap;
		float sp;

		cout << "HP = " << hp << endl << endl;
		cout << "Please input the attack power: " << endl;
		cin >> ap;

		cout << "Please input the shield power: " << endl;
		cin >> sp;

		//Calculations and output
		hp = hp - (ap * ((100 - sp) / 100));
		float attack = ap * ((100 - sp) / 100);
		cout << "\nDamage done: " << attack << endl << endl;
		cout << "Health left: " << hp << endl << endl;
	}

	else {
		exit(0);
	}


}

void characterStory() {
	cout << "===========\n \n Character Select and Equip" << endl;

	//Variables
	string charName;
	string weapon;
	string race;
	int dmg;
	int cd;
	float atk;
	float health = 100.0;
	int cSelect;

	int ranNum;

	string opName;
	int opDmg;
	int opCd;
	float opAtk;
	float opHP = 50.0;
	float opAtkD;


	cout << "\n Please Select a Character" << endl;
	cout << "\n 1: Dwarf\n 2: Elf\n 3: Orc\n 4: Fighter\n 5: Wizard\n";
	cin >> cSelect;

	cout << "What is your name?: ";
	cin >> charName;

	switch (cSelect) {
		//Dwarf
	case 1:
		weapon = "a rusty short sword";
		race = "Dwarf";
		dmg = 20;
		cd = 6;
		break;

		//Elf
	case 2:
		weapon = "a wooden bow";
		race = "Elf";
		dmg = 16;
		cd = 8;
		break;


		//Orc
	case 3:
		weapon = "orcish fists";
		race = "Orc";
		dmg = 15;
		cd = 4;
		break;

		//Fighter
	case 4:
		weapon = "brass knuckles";
		race = "Fighter";
		dmg = 17;
		cd = 3;
		break;

		//Wizard
	case 5:
		weapon = "~magic~";
		race = "Wizard";
		dmg = 30;
		cd = 9;
		break;

	default:
		cout << "You imbecile. You can't even choose properly" << endl;
		exit(0);
	}

	//Random attack power
	srand(time(NULL));
	atk = dmg * (rand()%5) * 1 / cd;

	//Opponent
	srand(time(NULL));
	opName = "Jeffery the Fisherman";
	opDmg = rand() % dmg + 1;
	srand(time(NULL));
	opCd = rand() % cd + 1;
	opAtk = opDmg * 5 * 1 / opCd;

	//The Story itself
	srand(time(NULL));
	ranNum = rand() % 10;

	cout << "\n\n ========== The Encounter ==========\n" << endl;
	cout << charName << " the " << race << " sets out on a quest to";

	switch (ranNum) {
	case 1:
		cout << " avenge their dead father ";
		break;
	case 2:
		cout << " kill the people who burnt down their hometown ";
		break;
	case 3:
		cout << " become stronger because they think they're better than everybody (What a showoff) ";
		break;
	default:
		cout << " cause they can ";
	}

	cout << "with nothing more than " << weapon << endl;
	cout <<"On your way to do your task, you run into " << opName << " who just really doesn't like you :/ He attacks!" << endl;

	//Fight sequence
	bool fight = true;
	int fChoice;
	
	while (fight) {
		srand(time(NULL));
		cout << "\n\nName: " << charName << "   Attack: " << dmg << "   Health: " << health << endl;
		cout << "===== Action Select =====" << endl;
		cout << " 1: Attack\n 2: Defend" << endl;
		cin >> fChoice;

		//Choice results
		if (fChoice == 1) {
			atk = dmg * (rand() % 5) * 1 / cd;
			if (atk <= 0) {
				atk = 8;
			}

			cout << charName << " the " << race << " attacks with " << weapon << endl;
			cout << "You deal " << atk << " damage" << endl;
			opHP -= atk;
			if (opHP < 0) {
				opHP = 0;
			}
		}
		//Defend
		else if (fChoice == 2) {
			cout << "You defend against an oncoming attack!" << endl;
			srand(time(NULL));
			opAtkD = opAtk - (rand() % 6);
			if (opAtkD < 0) {
				opAtkD = 7;
			}
			cout << opName << " attacks and deals " << opAtkD << " damage" << endl;
			health -= opAtkD;
			continue;
		}
		else {
			continue;
		}

		//Default dmg taken
		cout << opName << " attacks and deals " << opAtk << " damage" << endl;
		health -= opAtk;

		//Change health to 0 if below
		if (health < 0) {
			health = 0;
		}

		//Check to see if fight still going
		if (opHP == 0) {
			fight = false;
			cout << opName << " falls to the ground as you land your final strike.\n You were victorious!" << endl;
		}
		else if (health == 0) {
			fight = false;
			cout << opName << " strikes you down and you fall, leaving your journey forever unfinished.\n You lost." << endl;
			exit(0);
		}
	}

	cout << "\nYou continue to the next town" << endl;
	cout << "\n========== Game Over ==========";
	exit(0);

}



int main() {
	testComp();
	cout << "\n\n" << endl;
	scoreCheck();
	cout << "\n\n" << endl;
	menuSelect(); 
	cout << "\n\n" << endl;
	characterStory();
}