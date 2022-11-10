// CI411_Week5.cpp
// Kennedy Sovine UoB
//

#include <iostream>
using namespace std;

double pi = 3.14;
bool gameOver;

double circleArea(int radius);
double circleCircumference(int radius);
double hypotenuse(double a, double b);


void startScreen();
void endScreen();
void mainMenu();
void forLoopEx();
void combatWhileEx();
void switchRPG();

int main(){
	cout << circleArea(10) << endl;
	cout << circleCircumference(10) << endl;

	cout << hypotenuse(3.0, 4.0) << endl;

	gameOver = false;

    startScreen();

    while (!gameOver) {
        mainMenu();
    }

    endScreen();

}

double circleArea(int radius) {
	double area = pi * (radius * radius);
	
	return area;
}

double circleCircumference(int radius) {
	double circumference = 2 * pi * radius;

	return circumference;
}

double hypotenuse(double a, double b) {
	a = a * a;
	b = b * b;

	a = (double)sqrt(a);
	b = (double)sqrt(b);

	double c = a + b;

	return c;
}

void startScreen() {
	cout << "Welcome to the Game!" << endl;
}

void endScreen(){
    cout << "\nThanks for playing!";
	exit(0);
}

void mainMenu() {

	int select;
	cout << "\n\n========== Option Menu ==========" << endl;
	cout << " 1. Combat Example\n 2. RPG Example \n 3. For Loop\n 4. Exit\n";
	cin >> select;

	switch (select) {
	case 1:
		combatWhileEx();
		break;
	case 2:
		switchRPG();
		break;
	case 3: 
		forLoopEx();
		break;
	case 4:
		gameOver = true;
		break;
	default:
		break;
	}
}

void forLoopEx() {
	for (int i = 1; i <= 20; i++) {
		cout << i << " ";
	}

	cout << "\n\n";
	for (int i = 100; i >= 0; i -= 5) {
		cout << i << " ";
	}

	cout << "\n====== Times Table =====" << endl;
	int num;
	cout << "Input a Number" << endl;
	cin >> num;

	cout << "\n";

	for (int row = 1; row <= 12; row++) {
		for (int col = 1; col <= 12; col++) {
			cout << (num * row) * col << " ";
		}
		cout << endl;
	}
}

void combatWhileEx() {
    cout << "========== Simple Combat Loop ==========\n" << endl;

    //conditionals
    bool gameOver = false;
    int playerChoice;

    //player stats
    double pcHP = 100.0;
    int pcATK = 40;
    double pcATKMod;
    double newPAtk;

    //npc stats
    double npcHP = 100.0;
    int npcATK = 40;
    double npcATKMod;
    double newNAtk;

    while (!gameOver) {

        //Setup
        srand(time(NULL));
        cout << "\n======= Please Select an Action =======";
        cout << "\n 1: Attack\n 2: Defend\n 3: Evade\n\n Choice: ";
        cin >> playerChoice;

        //Attack Modifier
        switch (playerChoice) {
        case 1:
            pcATKMod = rand() % 6 + 1;
            break;

        case 2:
            pcATKMod = rand() % 5 + 1;
            break;

        case 3:
            pcATKMod = rand() % 4 + 1;
            break;
        default:
            cout << "\n Not a Valid Option";
            pcATKMod = 100;
        }

        npcATKMod = rand() % 5 + 1;

        newNAtk = npcATK * 1 / npcATKMod;
        newPAtk = pcATK * 1 / pcATKMod;

        cout << "\n\nYour Attack = " << int(newNAtk) << endl;
        cout << "NPC Attack = " << int(newPAtk) << endl;

        npcHP -= newPAtk;
        pcHP -= newNAtk;

        //If HP < 0, HP = 0
        if (pcHP < 0) {
            pcHP = 0;
        }
        if (npcHP < 0) {
            npcHP = 0;
        }

        //Say new HP
        cout << "\n\n\n PC Health : " << int(pcHP) << endl;
        cout << " New NPC Health : " << int(npcHP) << endl;

        if (pcHP == 0 || npcHP == 0) {
            gameOver = true;
        }
    }

    cout << "\n\n========== GAME OVER ==========";
    if (pcHP == 0) {
        cout << "\n           YOU LOST" << endl;
    }
    else {
        cout << "\n           YOU WON" << endl;
    }
}

void switchRPG() {
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
	atk = dmg * (rand() % 5) * 1 / cd;

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
	cout << "On your way to do your task, you run into " << opName << " who just really doesn't like you :/ He attacks!" << endl;

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
		}
	}

	cout << "\nYou continue to the next town" << endl;
	cout << "\n========== Game Over ==========";
}