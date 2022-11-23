// =======================================================
// CI411_Week8
// Kennedy Sovine UoBGames, 23 November 2022
// =======================================================

// Libraries to include
#include <iostream>
using namespace std;

// =======================================================
// Function Declaration

int getAtr(int max);

// =======================================================
// Classes
class Circle {
public:
    float radius;
    double getArea() {
        return pi * (radius * radius);
    }
    double getCircumference() {
        return 2 * pi * radius;
    }
private:
    double pi = 3.14;
};

class Square {
    public:
        float sideLength;
        double getArea() {
            return sideLength * sideLength;
        }
        double getPerimeter() {
            return sideLength + sideLength + sideLength + sideLength;
        }
};

class Character {
    public:
        int health, speed, stamina, strength;
        int xp;
        string name, weapon;
        bool armed, isAlive;
        //Creates PC
        Character(string cname, string cweapon) {
            name = cname;
            weapon = cweapon;
            health = 100;
            speed = getAtr(10);
            stamina = getAtr(10);
            strength = getAtr(10);
            xp = getAtr(100);
            armed = true;
            isAlive = true;
        }
        Character(string cname) {
            name = cname;
            weapon = "";
            health = 100;
            speed = getAtr(10);
            stamina = getAtr(10);
            strength = getAtr(10);
            xp = getAtr(100);
            armed = false;
            isAlive = true;
        }
        //Creates NPC
        Character() {
            name = "NPC";
            health = 100;
            speed = getAtr(5);
            stamina = getAtr(5);
            strength = getAtr(5);
            xp = 0;
            armed= true;
            isAlive = true;
        }
};

// =======================================================
// Global Variables

// =======================================================
int main() {
    cout << "===== Circles =====" << endl;
    Circle circle1;
    circle1.radius = 2;

    Circle circle2;
    circle2.radius = 4;

    cout << circle1.getArea() << endl;
    cout << circle2.getCircumference() << endl;

    cout << "===== Squares =====" << endl;

    Square square1;
    square1.sideLength = 2;

    Square square2;
    square2.sideLength = 4;

    cout << square1.getArea() << endl;
    cout << square2.getPerimeter() << endl;

    cout << "===== Characters =====" << endl;
    Character PC1("Kennedy", "Bow and Arrow");
    srand(time(NULL));
    Character PC2("Harry");

    srand(time(NULL));
    Character NPC1;

    cout << "Player Character 1: " + PC1.name << endl;
    cout << "HP: "; cout << PC1.health;
    cout << " Stamina: "; cout << PC1.stamina;
    cout << " Speed: "; cout << PC1.speed;
    cout << " XP: "; cout << PC1.xp << endl;
    cout << "Alive = "; cout << PC1.isAlive;
    cout << " : Armed = "; cout << PC1.armed;

    cout << "\n\n";

    cout << "Player Character 2: " + PC2.name << endl;
    cout << "HP: "; cout << PC2.health;
    cout << " Stamina: "; cout << PC2.stamina;
    cout << " Speed: "; cout << PC2.speed;
    cout << " XP: "; cout << PC2.xp << endl;
    cout << "Alive = "; cout << PC2.isAlive;
    cout << " : Armed = "; cout << PC2.armed;

    cout << "\n\n\n";

    cout << "NPC: " + NPC1.name << endl;
    cout << "HP: "; cout << NPC1.health;
    cout << " Stamina: "; cout << NPC1.stamina;
    cout << " Speed: "; cout << NPC1.speed;
    cout << " XP: "; cout << NPC1.xp << endl;
    cout << "Alive = "; cout << NPC1.isAlive;
    cout << " : Armed = "; cout << NPC1.armed;

    cout << "\n";

    


    return 0;
}

// =======================================================
// Functions

int getAtr(int max) {
    return (rand() % max);
}

// =====================================================