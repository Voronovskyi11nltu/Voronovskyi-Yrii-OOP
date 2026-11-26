#include <iostream>
#include <vector>
#include "Mammals.h"

using namespace std;

// Helper function to demonstrate late binding via a pointer (using ->)
void printMammalInfo(const Mammal* m) {
    if (m != nullptr) {
        m->describe();
        cout << "----------------------------------------" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Ukrainian");

    // INPUT DATASET #1: Dynamic objects in a vector of Mammal* pointers
    cout << "=== КОМПЛЕКТ ВХІДНИХ ДАНИХ №1 (вказівники Mammal*) ===" << endl << endl;
    vector<Mammal*> set1;
    set1.push_back(new Human("Тарас", 30, "Архітектор", "Українець"));
    set1.push_back(new Horse("Буран", 6, "Кінний завод", "Орловський рисак", 52.0));
    set1.push_back(new Cow("Ласуня", 4, "Ферма", 22.5, "Ряба"));

    for (const Mammal* ptr : set1) {
        printMammalInfo(ptr); // Pass the pointer directly
    }

    // INPUT DATASET #2: Passing object addresses (&) to the function via a pointer
    cout << "\n=== КОМПЛЕКТ ВХІДНИХ ДАНИХ №2 (вказівник на існуючі об'єкти) ===" << endl << endl;
    Human h2("Олена", 24, "Лікар", "Українка");
    Horse hr2("Вітер", 4, "Іподром", "Арабський скакун", 64.5);
    Cow c2("Квітка", 5, "Приватне господарство", 19.0, "Руда");

    printMammalInfo(&h2);
    printMammalInfo(&hr2);
    printMammalInfo(&c2);

    // Freeing dynamic memory (Dataset #1)
    cout << "\n=== ЗВІЛЬНЕННЯ ДИНАМІЧНОЇ ПАМ'ЯТІ (Комплект №1) ===" << endl;
    for (Mammal* ptr : set1) {
        delete ptr;
        cout << endl;
    }

    cout << "=== ЗАВЕРШЕННЯ ПРОГРАМИ (Знищення об'єктів Комплекту №2) ===" << endl;
    return 0;
}