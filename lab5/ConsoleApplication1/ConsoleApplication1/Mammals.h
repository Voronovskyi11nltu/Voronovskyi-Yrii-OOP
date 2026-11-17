#pragma once
#include <iostream>
#include <string>

using namespace std;

// Abstract base class: MAMMALS
class Mammal {
protected:
    string name;
    int age;

public:
    Mammal(const string& n = "Невідомо", int a = 0) : name(n), age(a) {}

    // Virtual destructor for proper memory deallocation in a polymorphic cluster
    virtual ~Mammal() {
        cout << "[Деструктор Mammal]: Видалено ссавця (" << name << ")" << endl;
    }

    // Pure virtual describe function (makes the class abstract)
    virtual void describe() const = 0;

    string getName() const { return name; }
    int getAge() const { return age; }
};

// Derived class from Mammal: HUMANS
class Human : public Mammal {
private:
    string profession;
    string nationality;

public:
    Human(const string& n, int a, const string& prof, const string& nat)
        : Mammal(n, a), profession(prof), nationality(nat) {
    }

    ~Human() override {
        cout << "[Деструктор Human]: Видалено людину (" << name << ")" << endl;
    }

    // Override of the virtual function to describe a human
    void describe() const override {
        cout << "=== ОПИС ЛЮДИНИ ===" << endl;
        cout << "Ім'я: " << name << endl;
        cout << "Вік: " << age << " років" << endl;
        cout << "Професія: " << profession << endl;
        cout << "Національність: " << nationality << endl;
    }
};

// Derived class from Mammal: ANIMALS (intermediate abstract class)
class Animal : public Mammal {
protected:
    string habitat; // Habitat / keeping environment

public:
    Animal(const string& n, int a, const string& hab)
        : Mammal(n, a), habitat(hab) {
    }

    virtual ~Animal() {
        cout << "[Деструктор Animal]: Видалено тварину (" << name << ")" << endl;
    }
};

// Derived class from Animal: HORSES
class Horse : public Animal {
private:
    string breed;      // Breed
    double maxSpeed;   // Maximum speed (km/h)

public:
    Horse(const string& n, int a, const string& hab, const string& br, double speed)
        : Animal(n, a, hab), breed(br), maxSpeed(speed) {
    }

    ~Horse() override {
        cout << "[Деструктор Horse]: Видалено коня (" << name << ")" << endl;
    }

    // Override of the virtual function to describe a horse
    void describe() const override {
        cout << "=== ОПИС КОНЯ ===" << endl;
        cout << "Кличка: " << name << endl;
        cout << "Вік: " << age << " років" << endl;
        cout << "Утримання: " << habitat << endl;
        cout << "Порода: " << breed << endl;
        cout << "Максимальна швидкість: " << maxSpeed << " км/год" << endl;
    }
};

// Derived class from Animal: COWS
class Cow : public Animal {
private:
    double milkYield;  // Milk yield (liters/day)
    string color;      // Coat color

public:
    Cow(const string& n, int a, const string& hab, double milk, const string& col)
        : Animal(n, a, hab), milkYield(milk), color(col) {
    }

    ~Cow() override {
        cout << "[Деструктор Cow]: Видалено корову (" << name << ")" << endl;
    }

    // Override of the virtual function to describe a cow
    void describe() const override {
        cout << "=== ОПИС КОРОВИ ===" << endl;
        cout << "Кличка: " << name << endl;
        cout << "Вік: " << age << " років" << endl;
        cout << "Утримання: " << habitat << endl;
        cout << "Денний надій молока: " << milkYield << " л" << endl;
        cout << "Масть: " << color << endl;
    }
};