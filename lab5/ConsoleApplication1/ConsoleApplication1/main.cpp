#include <iostream>
#include "Mammals.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Ukrainian");

    cout << "=== ÄÅÌÎÍÑÒÐÀÖ²ß ÏÎË²ÌÎÐÔ²ÇÌÓ ÒÀ Ï²ÇÍÜÎÃÎ ÇÂ'ßÇÓÂÀÍÍß ===" << endl << endl;

    // 1. Working with an object of the Human class
    Human* p1 = new Human("Òàðàñ", 30, "Àðõ³òåêòîð", "Óêðà¿íåöü");
    p1->describe(); // Calls Human::describe()
    cout << "----------------------------------------" << endl;

    Mammal* p2 = p1; // Base class pointer is initialized with the derived class address (p1 == p2)
    p2->describe();  // Thanks to virtual, Human::describe() is called (late binding)
    cout << "----------------------------------------" << endl << endl;

    // 2. Working with an object of the Horse class
    Horse* p3 = new Horse("Áóðàí", 6, "Ê³ííèé çàâîä", "Îðëîâñüêèé ðèñàê", 52.0);
    p3->describe(); // Calls Horse::describe()
    cout << "----------------------------------------" << endl;

    Mammal* p4 = p3; // p3 == p4
    p4->describe();  // Calls Horse::describe()
    cout << "----------------------------------------" << endl << endl;

    // 3. Working with an object of the Cow class
    Cow* p5 = new Cow("Ëàñóíÿ", 4, "Ôåðìà", 22.5, "Ðÿáà");
    p5->describe(); // Calls Cow::describe()
    cout << "----------------------------------------" << endl;

    Animal* p6 = p5; // Can also be assigned to the intermediate base class Animal (p5 == p6)
    p6->describe();  // Calls Cow::describe()
    cout << "----------------------------------------" << endl;

    Mammal* p7 = p5; // And to the root abstract class Mammal (p5 == p7)
    p7->describe();  // Calls Cow::describe()
    cout << "----------------------------------------" << endl << endl;

    // Freeing dynamic memory (call delete only once for each created object!)
    cout << "=== ÇÂ²ËÜÍÅÍÍß ÏÀÌ'ßÒ² ===" << endl;
    delete p2; // Destroys the Human object (calls ~Human(), then ~Mammal())
    cout << endl;
    delete p4; // Destroys the Horse object (calls ~Horse(), ~Animal(), ~Mammal())
    cout << endl;
    delete p7; // Destroys the Cow object (calls ~Cow(), ~Animal(), ~Mammal())

    return 0;
}