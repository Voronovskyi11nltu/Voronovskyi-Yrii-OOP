#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

const double PI = 3.14159265358979323846;

// ================= BASE CLASS 1: CIRCLE =================
class Circle {
protected:
    double radius;

public:
    // Base class constructor
    Circle(double r = 0.0) : radius(r) {
        cout << "[Circle Constructor]: Створено об'єкт кола з радіусом R = " << radius << endl;
    }

    // Virtual destructor
    virtual ~Circle() {
        cout << "[Circle Destructor]: Знищено об'єкт Circle." << endl;
    }

    // Calculate area of the circle
    double getCircleArea() const {
        return PI * radius * radius;
    }

    // Calculate circumference of the circle
    double getCircumference() const {
        return 2.0 * PI * radius;
    }

    double getRadius() const {
        return radius;
    }

    // Display circle information
    void showCircleInfo(ostream& os) const {
        os << "--- Інформація про Коло ---" << endl;
        os << "Радіус (R): " << fixed << setprecision(2) << radius << endl;
        os << "Довжина кола (L): " << getCircumference() << endl;
        os << "Площа кола (S_circle): " << getCircleArea() << endl;
    }
};

// ================= BASE CLASS 2: RECTANGLE =================
class Rectangle {
protected:
    double width;
    double height;

public:
    // Base class constructor
    Rectangle(double w = 0.0, double h = 0.0) : width(w), height(h) {
        cout << "[Rectangle Constructor]: Створено прямокутник " << width << " x " << height << endl;
    }

    // Virtual destructor
    virtual ~Rectangle() {
        cout << "[Rectangle Destructor]: Знищено об'єкт Rectangle." << endl;
    }

    // Calculate area of the rectangle
    double getRectangleArea() const {
        return width * height;
    }

    // Calculate perimeter of the rectangle
    double getPerimeter() const {
        return 2.0 * (width + height);
    }

    double getWidth() const { return width; }
    double getHeight() const { return height; }

    // Display rectangle information
    void showRectangleInfo(ostream& os) const {
        os << "--- Інформація про Прямокутник ---" << endl;
        os << "Ширина (w): " << fixed << setprecision(2) << width
            << ", Висота (h): " << height << endl;
        os << "Периметр (P): " << getPerimeter() << endl;
        os << "Площа прямокутника (S_rect): " << getRectangleArea() << endl;
    }
};

// ================= DERIVED CLASS (MULTIPLE INHERITANCE) =================
// Rectangle inscribed in a Circle
class RectangleInCircle : public Circle, public Rectangle {
public:
    // Derived class constructor
    // Passes arguments to the base class constructors.
    // Radius is calculated using the formula for an inscribed rectangle: R = sqrt(w^2 + h^2) / 2
    RectangleInCircle(double w, double h)
        : Circle(sqrt(w* w + h * h) / 2.0), Rectangle(w, h) {
        cout << "[RectangleInCircle Constructor]: Створено комбінований об'єкт." << endl;
    }

    // Derived class destructor
    ~RectangleInCircle() override {
        cout << "[RectangleInCircle Destructor]: Знищено комбінований об'єкт." << endl;
    }

    // Calculate remaining area (Circle area minus Rectangle area)
    double getAreaDifference() const {
        return getCircleArea() - getRectangleArea();
    }

    // Output all information to the specified stream (console or file)
    void showAllInfo(ostream& os) const {
        os << "============================================" << endl;
        os << " ПРЯМОКУТНИК, ВПИСАНИЙ У КОЛО (МНОЖИННЕ УСПАДКУВАННЯ)" << endl;
        os << "============================================" << endl;
        showRectangleInfo(os);
        os << "--------------------------------------------" << endl;
        showCircleInfo(os);
        os << "--------------------------------------------" << endl;
        os << "Діагональ прямокутника (Діаметр кола): " << 2.0 * radius << endl;
        os << "Вільна площа всередині кола: " << getAreaDifference() << endl;
        os << "============================================" << endl << endl;
    }

    // Method to write data to a file using fstream
    void saveToFile(const string& filename) const {
        // ios::app opens the file in append mode
        ofstream outFile(filename, ios::out | ios::app);
        if (!outFile.is_open()) {
            cerr << "Помилка: Не вдалося відкрити файл " << filename << " для запису!" << endl;
            return;
        }

        showAllInfo(outFile); // Write to file stream
        outFile.close();
        cout << "[Файловий потік]: Дані успішно збережено у файл '" << filename << "'." << endl;
    }
};

// ================= MAIN FUNCTION =================
int main() {
    SetConsoleOutputCP(1251);

    cout << "=== ЛАБОРАТОРНА РОБОТА №4: МНОЖИННЕ УСПАДКУВАННЯ ТА ФАЙЛОВІ ПОТОКИ ===" << endl << endl;

    // 1. Create and output the first object (Data set 1: 6 x 8)
    cout << "--> Створення Об'єкта 1 (Прямокутник 6 х 8)..." << endl;
    RectangleInCircle fig1(6.0, 8.0);

    cout << endl << "Виведення Об'єкта 1 у консоль:" << endl;
    fig1.showAllInfo(cout);

    // 2. Create and output the second object (Data set 2: 3 x 4)
    cout << "--> Створення Об'єкта 2 (Прямокутник 3 х 4)..." << endl;
    RectangleInCircle fig2(3.0, 4.0);

    cout << endl << "Виведення Об'єкта 2 у консоль:" << endl;
    fig2.showAllInfo(cout);

    // 3. Write objects to a file
    string filename = "shapes_output.txt";
    cout << "--> Збереження Об'єкта 1 та Об'єкта 2 у файл '" << filename << "'..." << endl;
    fig1.saveToFile(filename);
    fig2.saveToFile(filename);

    // 4. Read data from file to verify file stream operation (ifstream)
    cout << endl << "--> Зчитування вмісту з файлу '" << filename << "':" << endl;
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }
    else {
        cerr << "Помилка відкриття файлу для читання!" << endl;
    }

    return 0;
}