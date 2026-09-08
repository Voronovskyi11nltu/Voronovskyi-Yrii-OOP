#include <cmath>

// ООП-клас для обчислення функцій
public ref class FunctionTabulator {
private:
    double y;
    double z;

    static double factorial(int n) {
        double res = 1.0;
        for (int i = 1; i <= n; ++i) res *= i;
        return res;
    }

public:
    FunctionTabulator(double y_val, double z_val) : y(y_val), z(z_val) {}

    double calculateB(double x) {
        double term1 = 1.0;
        double term2 = (x + y) / std::pow(std::abs(z), 0.34);
        double term3 = std::pow(y, 2) / factorial(3);
        double term4 = std::pow(z, 3) / factorial(5);
        double term5 = std::exp(x - y) / (z + y);
        return term1 - term2 + term3 + term4 + term5;
    }

    double calculateA(double x, double b) {
        double term1 = y - std::sqrt(std::abs(std::pow(x, 2) - b));
        double term2 = (y - std::pow(x, 2)) / (z + 4.0 * std::pow(y, 2));
        double inside = std::abs(term1 * term2);
        return std::log(std::pow(inside, 2.0 / 3.0));
    }
};

// Обробник натискання кнопки на формі
private: System::Void btnTabulate_Click(System::Object^ sender, System::EventArgs^ e) {
    double x_start = -1.0;
    double x_end = 1.0;
    double dx = 0.2;
    double y = 0.47 * 7;
    double z = -1.32 * 7;

    FunctionTabulator^ tabulator = gcnew FunctionTabulator(y, z);

    // Очищення та налаштування текстового поля
    txtResult->Clear();
    txtResult->AppendText("   x\t\t   b[x,y,z]\t\t   a[x,y,z,b]\r\n");
    txtResult->AppendText("------------------------------------------------------\r\n");

    // Цикл табулювання
    for (double x = x_start; x <= x_end + 1e-9; x += dx) {
        double b = tabulator->calculateB(x);
        double a = tabulator->calculateA(x, b);

        // Форматований вивід у MultiLine TextBox
        System::String^ line = System::String::Format("{0,6:F1}\t\t{1,10:F6}\t\t{2,10:F6}\r\n", x, b, a);
        txtResult->AppendText(line);
    }
}