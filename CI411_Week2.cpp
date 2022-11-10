// CI411_//---------- CI411_Week2
//---------- Kennedy Sovine, UoB 2022

#include <iostream>
using namespace std;

int op() {
    //Math :D
    cout << " 10 + 5 = " << 10 + 5 << endl << endl;
    cout << " 10 - 5 = " << 10 - 5 << endl << endl;
    cout << " 10 * 5 = " << 10 * 5 << endl << endl;

    cout << " 10 / 5 = " << 10 / 5 << endl << endl;
    cout << " 10.0 + 5.0 = " << 10.0 + 5.0 << endl << endl;
    cout << " 11 % 5 = " << 11 % 5 << endl << endl;

    cout << " (10 + 5) * 4 = " << (10 + 5) * 4 << endl << endl;
    cout << " 10 + 5 * 4 = " << 10 + 5 * 4 << endl << endl;

    cout << "---------\n Buh bye" << endl;

    return 0;
}
int circle() {
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

    return 0;
}
int rangeMissile() {
    float speed;
    float range;

    cout << "Please input the missile speed (m/s)" << endl;
    cin >> speed;
    cout << "Please input the missile range (m)" << endl;
    cin >> range;

    cout << "Time taken to travel = " << 1.0 * (range / speed) << " seconds" << endl << endl << endl;

    return 0;
}
int dmgCalc() {
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
    return 0;
}


int main() {
    cout << " Arithmetic Operators\n----------------------" << endl;
    op();

    cout << "\n \n Circle Calculations\n---------------------" << endl;
    circle();

    cout << "\n\n ------- Missile Calculation -------" << endl;
    rangeMissile();

    cout << "\n\n------- Character Damage Calc ------" << endl;
    dmgCalc();
}
