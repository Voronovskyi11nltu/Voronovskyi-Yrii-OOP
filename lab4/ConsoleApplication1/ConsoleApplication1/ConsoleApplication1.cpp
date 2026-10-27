#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

const double PI = 3.14159265358979323846;

// ================= БАЗОВИЙ КЛАС 1: КОЛО =================
class Circle {
protected:
    double radius;

public:
    // Конструктор базового класу
    Circle(double r = 0.0) : radius(r) {
        cout << "[Circle Constructor]: Створено об'єкт кола з радіусом R = " << radius << endl;
    }

    // Віртуальний деструктор
    virtual ~Circle() {
        cout << "[Circle Destructor]: Знищено об'єкт Circle." << endl;
    }

    // Обчислення площі кола
    double getCircleArea() const {
        return PI * radius * radius;
    }

    // Обчислення довжини кола
    double getCircumference() const {
        return 2.0 * PI * radius;
    }

    double getRadius() const {
        return radius;
    }

    // Виведення інформації про коло
    void showCircleInfo(ostream& os) const {
        os << "--- Інформація про Коло ---" << endl;
        os << "Радіус (R): " << fixed << setprecision(2) << radius << endl;
        os << "Довжина кола (L): " << getCircumference() << endl;
        os << "Площа кола (S_circle): " << getCircleArea() << endl;
    }
};

// ================= БАЗОВИЙ КЛАС 2: ПРЯМОКУТНИК =================
class Rectangle {
protected:
    double width;
    double height;

public:
    // Конструктор базового класу
    Rectangle(double w = 0.0, double h = 0.0) : width(w), height(h) {
        cout << "[Rectangle Constructor]: Створено прямокутник " << width << " x " << height << endl;
    }

    // Віртуальний деструктор
    virtual ~Rectangle() {
        cout << "[Rectangle Destructor]: Знищено об'єкт Rectangle." << endl;
    }

    // Обчислення площі прямокутника
    double getRectangleArea() const {
        return width * height;
    }

    // Обчислення периметра прямокутника
    double getPerimeter() const {
        return 2.0 * (width + height);
    }

    double getWidth() const { return width; }
    double getHeight() const { return height; }

    // Виведення інформації про прямокутник
    void showRectangleInfo(ostream& os) const {
        os << "--- Інформація про Прямокутник ---" << endl;
        os << "Ширина (w): " << fixed << setprecision(2) << width
            << ", Висота (h): " << height << endl;
        os << "Периметр (P): " << getPerimeter() << endl;
        os << "Площа прямокутника (S_rect): " << getRectangleArea() << endl;
    }
};

// ================= ПОХІДНИЙ КЛАС (МНОЖИННЕ УСПАДКУВАННЯ) =================
// Прямокутник, вписаний у Коло
class RectangleInCircle : public Circle, public Rectangle {
public:
    // Конструктор похідного класу
    // Передає аргументи у конструктори базових класів.
    // Радіус обчислюється за формулою вписаного прямокутника: R = sqrt(w^2 + h^2) / 2
    RectangleInCircle(double w, double h)
        : Circle(sqrt(w* w + h * h) / 2.0), Rectangle(w, h) {
        cout << "[RectangleInCircle Constructor]: Створено комбінований об'єкт." << endl;
    }

    // Деструктор похідного класу
    ~RectangleInCircle() override {
        cout << "[RectangleInCircle Destructor]: Знищено комбінований об'єкт." << endl;
    }

    // Обчислення залишку площі (Площа кола мінус Площа прямокутника)
    double getAreaDifference() const {
        return getCircleArea() - getRectangleArea();
    }

    // Виведення всієї інформації у вказаний потік (консоль або файл)
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

    // Метод запису даних у файл за допомогою fstream
    void saveToFile(const string& filename) const {
        // ios::app відкриває файл у режимі допису в кінець
        ofstream outFile(filename, ios::out | ios::app);
        if (!outFile.is_open()) {
            cerr << "Помилка: Не вдалося відкрити файл " << filename << " для запису!" << endl;
            return;
        }

        showAllInfo(outFile); // Запис у файловий потік
        outFile.close();
        cout << "[Файловий потік]: Дані успішно збережено у файл '" << filename << "'." << endl;
    }
};

// ================= ГОЛОВНА ФУНКЦІЯ =================
int main() {
    SetConsoleOutputCP(1251);

    cout << "=== ЛАБОРАТОРНА РОБОТА №4: МНОЖИННЕ УСПАДКУВАННЯ ТА ФАЙЛОВІ ПОТОКИ ===" << endl << endl;

    // 1. Створення та виведення першого об'єкта (Комплект даних 1: 6 х 8)
    cout << "--> Створення Об'єкта 1 (Прямокутник 6 х 8)..." << endl;
    RectangleInCircle fig1(6.0, 8.0);

    cout << endl << "Виведення Об'єкта 1 у консоль:" << endl;
    fig1.showAllInfo(cout);

    // 2. Створення та виведення другого об'єкта (Комплект даних 2: 3 х 4)
    cout << "--> Створення Об'єкта 2 (Прямокутник 3 х 4)..." << endl;
    RectangleInCircle fig2(3.0, 4.0);

    cout << endl << "Виведення Об'єкта 2 у консоль:" << endl;
    fig2.showAllInfo(cout);

    // 3. Запис об'єктів у файл
    string filename = "shapes_output.txt";
    cout << "--> Збереження Об'єкта 1 та Об'єкта 2 у файл '" << filename << "'..." << endl;
    fig1.saveToFile(filename);
    fig2.saveToFile(filename);

    // 4. Зчитування даних із файлу для перевірки файлового потоку (ifstream)
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