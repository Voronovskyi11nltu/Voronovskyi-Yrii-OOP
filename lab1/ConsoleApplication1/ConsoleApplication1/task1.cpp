#include <iostream>
#include <cmath>

class FunctionEvaluator {
private:
    double x, y, z;

    // Helper private method for calculating the factorial
    double Factorial(int n) {
        double result = 1.0;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

public:
    // Constructor to initialize input parameters
    FunctionEvaluator(double x_val, double y_val, double z_val) {
        x = x_val;
        y = y_val;
        z = z_val;
    }

    // Method to calculate the function b[x, y, z]
    double CalculateB() {
        double term1 = 1.0;
        double term2 = (x + y) / std::pow(std::abs(z), 0.34);
        double term3 = std::pow(y, 2) / Factorial(3);
        double term4 = std::pow(z, 3) / Factorial(5);
        double term5 = std::exp(x - y) / (z + y);

        return term1 - term2 + term3 + term4 + term5;
    }

    // Method to calculate the function a[x, y, z, b]
    double CalculateA(double b) {
        // Break the expression into parts for convenience
        double part1 = y - std::sqrt(std::abs(std::pow(x, 2) - b));
        double part2 = (y - std::pow(x, 2)) / (z + 4 * std::pow(y, 2));
        double inner_expression = part1 * part2;

        // Calculating ln(|inner_expression|^(2/3))
        return std::log(std::pow(std::abs(inner_expression), 2.0 / 3.0));
    }
};

int main() {
    // Initial values as given in the condition
    double x = 0.48 * 7;
    double y = 0.47 * 7;
    double z = -1.32 * 7;

    // Creating an instance of the class
    FunctionEvaluator evaluator(x, y, z);

    // Sequential calculation of b and a
    double b_val = evaluator.CalculateB();
    double a_val = evaluator.CalculateA(b_val);

    // Displaying the results
    std::cout << "Initial data:" << std::endl;
    std::cout << "x = " << x << "\ny = " << y << "\nz = " << z << "\n\n";
    std::cout << "Calculation results:" << std::endl;
    std::cout << "b = " << b_val << std::endl;
    std::cout << "a = " << a_val << std::endl;

    return 0;
}