#include <iostream>
#include <cmath>
#include <iomanip>

class ExpressionCalculator {
private:
    double x;
    double y;
    double z;

    // Допоміжний метод для обчислення факторіала
    static double factorial(int n) {
        double result = 1.0;
        for (int i = 1; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

public:
    ExpressionCalculator(double x_val, double y_val, double z_val)
        : x(x_val), y(y_val), z(z_val) {
    }

    // Обчислення b[x, y, z]
    double calculateB() const {
        double term1 = 1.0;
        double term2 = (x + y) / std::pow(std::abs(z), 0.34);
        double term3 = std::pow(y, 2) / factorial(3);
        double term4 = std::pow(z, 3) / factorial(5);
        double term5 = std::exp(x - y) / (z + y);

        return term1 - term2 + term3 + term4 + term5;
    }

    // Обчислення a[x, y, z, b]
    double calculateA(double b) const {
        double term1 = y - std::sqrt(std::abs(std::pow(x, 2) - b));
        double term2 = (y - std::pow(x, 2)) / (z + 4.0 * std::pow(y, 2));
        double inside = std::abs(term1 * term2);

        return std::log(std::pow(inside, 2.0 / 3.0));
    }
};

int main() {
    double x = 0.48 * 7;
    double y = 0.47 * 7;
    double z = -1.32 * 7;

    ExpressionCalculator calc(x, y, z);

    double b = calc.calculateB();
    double a = calc.calculateA(b);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "z = " << z << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a = " << a << std::endl;

    return 0;
}