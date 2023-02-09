// CI411_Week4
// Kennedy Sovine, UoB 2022
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void forLoop() {
    for (int i = 1; i <= 20; i++) {
        cout << i << " ";
    }

    cout << "\n\n";
    for (int i = 100; i >= 0; i -= 5) {
        cout << i << " ";
    }
}

void inputLoop() {
    cout << "====== Times Table =====" << endl;
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

void whileTable() {
    cout << "====== Times Table =====" << endl;
    int num;
    char playAgain = 'y';

    while (playAgain != 'n') {
        cout << "Input a Number" << endl;
        cin >> num;

        cout << "\n";
        for (int row = 1; row <= 12; row++) {
            for (int col = 1; col <= 12; col++) {
                cout << (num * row) * col << " ";
            }
            cout << endl;
        }

        cout << "\n\nDo you want to go again? (y/n)" << endl;
        cin >> playAgain;

        playAgain = tolower(playAgain);
  
    }
}

void combatLoop() {
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

int main() {
    forLoop();
    cout << "\n\n";
    inputLoop();
    cout << "\n\n";
    whileTable();
    cout << "\n\n";
    combatLoop();
}
