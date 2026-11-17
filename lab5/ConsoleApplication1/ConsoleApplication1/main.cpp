#include <iostream>
#include <vector>
#include "Mammals.h"

using namespace std;

// Helper function to demonstrate late binding via references
void printMammalInfo(const Mammal& m) {
    m.describe();
    cout << "----------------------------------------" << endl;
}

int main() {
    setlocale(LC_ALL, "Ukrainian");

    // INPUT DATASET #1: Working via pointers to the base class Mammal*
    cout << "=== ÊÎÌÏËÅÊÒ ÂÕ²ÄÍÈÕ ÄÀÍÈÕ ¹1 (âêàç³âíèêè Mammal*) ===" << endl << endl;
    vector<Mammal*> set1;
    set1.push_back(new Human("Òàðàñ", 30, "Àðõ³òåêòîð", "Óêðà¿íåöü"));
    set1.push_back(new Horse("Áóðàí", 6, "Ê³ííèé çàâîä", "Îðëîâñüêèé ðèñàê", 52.0));
    set1.push_back(new Cow("Ëàñóíÿ", 4, "Ôåðìà", 22.5, "Ðÿáà"));

    for (const Mammal* ptr : set1) {
        ptr->describe(); // Late binding: calls the method of the actual object
        cout << "----------------------------------------" << endl;
    }

    // INPUT DATASET #2: Working via references to the base class Mammal&
    cout << "\n=== ÊÎÌÏËÅÊÒ ÂÕ²ÄÍÈÕ ÄÀÍÈÕ ¹2 (ïîñèëàííÿ Mammal&) ===" << endl << endl;
    Human h2("Îëåíà", 24, "Ë³êàð", "Óêðà¿íêà");
    Horse hr2("Â³òåð", 4, "²ïîäðîì", "Àðàáñüêèé ñêàêóí", 64.5);
    Cow c2("Êâ³òêà", 5, "Ïðèâàòíå ãîñïîäàðñòâî", 19.0, "Ðóäà");

    printMammalInfo(h2);
    printMammalInfo(hr2);
    printMammalInfo(c2);

    // Freeing dynamic memory (demonstration of virtual destructors)
    cout << "\n=== ÇÂ²ËÜÍÅÍÍß ÄÈÍÀÌ²×ÍÎ¯ ÏÀÌ'ßÒ² (Êîìïëåêò ¹1) ===" << endl;
    for (Mammal* ptr : set1) {
        delete ptr;
        cout << endl;
    }

    cout << "=== ÇÀÂÅÐØÅÍÍß ÏÐÎÃÐÀÌÈ (Çíèùåííÿ îá'ºêò³â Êîìïëåêòó ¹2) ===" << endl;
    return 0;
}