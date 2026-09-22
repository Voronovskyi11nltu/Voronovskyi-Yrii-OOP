#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>

class FunctionTabulator {
private:
    double y;
    double z;

    // Internal method for calculating the factorial
    double Factorial(int n) const {
        double result = 1.0;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

public:
    // Class constructor
    FunctionTabulator(double y_val, double z_val) : y(y_val), z(z_val) {}

    // Method to calculate b[x, y, z]
    double CalculateB(double x) const {
        double term1 = 1.0;
        double term2 = (x + y) / std::pow(std::abs(z), 0.34);
        double term3 = std::pow(y, 2) / Factorial(3);
        double term4 = std::pow(z, 3) / Factorial(5);
        double term5 = std::exp(x - y) / (z + y);

        return term1 - term2 + term3 + term4 + term5;
    }

    // Method to calculate a[x, y, z, b]
    double CalculateA(double x, double b) const {
        double part1 = y - std::sqrt(std::abs(std::pow(x, 2) - b));
        double part2 = (y - std::pow(x, 2)) / (z + 4 * std::pow(y, 2));
        double inner_expression = part1 * part2;

        return std::log(std::pow(std::abs(inner_expression), 2.0 / 3.0));
    }

    // Tabulation method using a multiline string stream (MultiLine)
    void Tabulate(double x_start, double x_end, double dx) const {
        std::stringstream multilineBuffer; // Buffer for accumulating multiline output

        multilineBuffer << "=======================================\n";
        multilineBuffer << "|   x    |     b(x)     |     a(x)    |\n";
        multilineBuffer << "=======================================\n";

        // Tabulation loop from x_start to x_end with step dx
        for (double x = x_start; x <= x_end + dx / 2.0; x += dx) {
            // Avoid -0.00 due to double floating-point error
            double current_x = (std::abs(x) < 1e-9) ? 0.0 : x;

            double b_val = CalculateB(current_x);
            double a_val = CalculateA(current_x, b_val);

            multilineBuffer << "| " << std::setw(6) << std::fixed << std::setprecision(2) << current_x
                << " | " << std::setw(12) << std::setprecision(5) << b_val
                << " | " << std::setw(11) << std::setprecision(5) << a_val
                << " |\n";
        }

        multilineBuffer << "=======================================\n";

        // Single output of the formed text to the console
        std::cout << multilineBuffer.str();
    }
};

int main() {
    // Fixed parameters from Task 1
    double y = 0.47 * 7;
    double z = -1.32 * 7;

    // Tabulation boundaries according to Task 2
    double x_start = -1.0;
    double x_end = 1.0;
    double dx = 0.2;

    FunctionTabulator tabulator(y, z);
    tabulator.Tabulate(x_start, x_end, dx);

    return 0;
}