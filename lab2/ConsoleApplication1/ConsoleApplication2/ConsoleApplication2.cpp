#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>

using namespace std;

// Custom exception class for invalid numeric date fields
class InvalidDateException : public invalid_argument {
public:
    explicit InvalidDateException(const string& message) : invalid_argument(message) {}
};

// Helper Date class for processing and validating numeric fields (day, month, year)
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() : day(1), month(1), year(2000) {}

    Date(int d, int m, int y) {
        setDate(d, m, y);
    }

    // Validation of numeric fields with exception throwing (throw)
    void setDate(int d, int m, int y) {
        if (y < 1800 || y > 2026) {
            throw InvalidDateException("Invalid year: " + to_string(y) + ". Valid range: [1800..2026].");
        }
        if (m < 1 || m > 12) {
            throw InvalidDateException("Invalid month: " + to_string(m) + ". Valid range: [1..12].");
        }

        int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        // Leap year check
        bool isLeap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        if (m == 2 && isLeap) {
            daysInMonth[2] = 29;
        }

        if (d < 1 || d > daysInMonth[m]) {
            throw InvalidDateException("Invalid day: " + to_string(d) + " for month " + to_string(m) + ".");
        }

        day = d;
        month = m;
        year = y;
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    friend ostream& operator<<(ostream& os, const Date& d) {
        os << setfill('0') << setw(2) << d.day << "."
            << setw(2) << d.month << "."
            << d.year;
        return os;
    }

    friend istream& operator>>(istream& is, Date& d) {
        int d_val, m_val, y_val;
        if (!(is >> d_val >> m_val >> y_val)) {
            throw InvalidDateException("Input error: integers expected for date.");
        }
        d.setDate(d_val, m_val, y_val);
        return is;
    }
};

// PERSON Class
class Person {
private:
    string lastName;
    string firstName;
    string patronymic;
    string gender;
    Date birthDate;

public:
    // Default constructor
    Person() : lastName(""), firstName(""), patronymic(""), gender(""), birthDate(1, 1, 2000) {}

    // Parameterized constructor
    Person(string lName, string fName, string patr, string g, int d, int m, int y)
        : lastName(lName), firstName(fName), patronymic(patr), gender(g), birthDate(d, m, y) {
    }

    // Getters
    string getLastName() const { return lastName; }
    string getFirstName() const { return firstName; }
    string getPatronymic() const { return patronymic; }
    string getGender() const { return gender; }
    Date getBirthDate() const { return birthDate; }

    // Setters with numeric field validation
    void setBirthDate(int d, int m, int y) {
        birthDate.setDate(d, m, y); // Validates numbers and throws InvalidDateException on error
    }

    void setLastName(const string& lName) { lastName = lName; }
    void setFirstName(const string& fName) { firstName = fName; }
    void setPatronymic(const string& patr) { patronymic = patr; }
    void setGender(const string& g) { gender = g; }

    // Overloading output stream operator (<<)
    friend ostream& operator<<(ostream& os, const Person& p) {
        os << "Full Name: " << p.lastName << " " << p.firstName << " " << p.patronymic
            << " | Gender: " << p.gender
            << " | Date of Birth: " << p.birthDate;
        return os;
    }

    // Overloading input stream operator (>>)
    friend istream& operator>>(istream& is, Person& p) {
        cout << "Enter last name: "; is >> p.lastName;
        cout << "Enter first name: "; is >> p.firstName;
        cout << "Enter patronymic: "; is >> p.patronymic;
        cout << "Enter gender: "; is >> p.gender;
        cout << "Enter date of birth (day month year space-separated): ";
        is >> p.birthDate; // Calls operator>> for Date with proper validation
        return is;
    }
};

// Class for managing person list and implementing overloaded search
class PersonRegistry {
private:
    vector<Person> people;

public:
    void addPerson(const Person& p) {
        people.push_back(p);
    }

    void showAll() const {
        cout << "\n=== PERSON REGISTRY LIST ===" << endl;
        for (size_t i = 0; i < people.size(); ++i) {
            cout << i + 1 << ". " << people[i] << endl;
        }
        cout << "=============================" << endl;
    }

    // === OVERLOADED SEARCH METHODS (findPerson) ===

    // Criterion 1: By last name (string)
    void findPerson(const string& targetLastName) const {
        cout << "\n[SEARCH] By last name '" << targetLastName << "':" << endl;
        bool found = false;
        for (const auto& p : people) {
            if (p.getLastName() == targetLastName) {
                cout << "  -> " << p << endl;
                found = true;
            }
        }
        if (!found) cout << "  No persons found with this last name." << endl;
    }

    // Criterion 2: By birth year (int)
    void findPerson(int targetYear) const {
        cout << "\n[SEARCH] By birth year '" << targetYear << "':" << endl;
        bool found = false;
        for (const auto& p : people) {
            if (p.getBirthDate().getYear() == targetYear) {
                cout << "  -> " << p << endl;
                found = true;
            }
        }
        if (!found) cout << "  No persons found with this birth year." << endl;
    }

    // Criterion 3: By exact date (day, month, year)
    void findPerson(int day, int month, int year) const {
        Date targetDate;
        try {
            targetDate.setDate(day, month, year);
        }
        catch (const exception& e) {
            cout << "\n[SEARCH ABORTED] Invalid search parameters: " << e.what() << endl;
            return;
        }

        cout << "\n[SEARCH] By birth date '" << targetDate << "':" << endl;
        bool found = false;
        for (const auto& p : people) {
            if (p.getBirthDate() == targetDate) {
                cout << "  -> " << p << endl;
                found = true;
            }
        }
        if (!found) cout << "  No persons found with this birth date." << endl;
    }
};

int main() {
    PersonRegistry registry;

    cout << "=== 1. POPULATING PERSON REGISTRY ===" << endl;
    try {
        Person p1("Shevchenko", "Taras", "Hryhorovych", "M", 9, 3, 1814);
        Person p2("Kovalenko", "Oleksandr", "Ivanovych", "M", 15, 5, 2000);
        Person p3("Melnyk", "Anna", "Serhiivna", "F", 15, 5, 2000);
        Person p4("Kovalenko", "Olena", "Petrivna", "F", 20, 11, 1995);

        registry.addPerson(p1);
        registry.addPerson(p2);
        registry.addPerson(p3);
        registry.addPerson(p4);
    }
    catch (const exception& e) {
        cout << "Error adding entry: " << e.what() << endl;
    }

    // Output all records using operator<<
    registry.showAll();

    cout << "\n=== 2. DEMONSTRATION OF OVERLOADED SEARCH METHODS ===" << endl;
    // Calls to the same findPerson name with different argument types and counts
    registry.findPerson("Kovalenko");      // Search by last name (string)
    registry.findPerson(2000);              // Search by year (int)
    registry.findPerson(20, 11, 1995);      // Search by date (int, int, int)

    cout << "\n=== 3. DEMONSTRATION OF EXCEPTION HANDLING (TRY/CATCH) ===" << endl;

    // Test dataset #2 (Invalid values):

    // Test A: Invalid month (13)
    try {
        cout << "\n[Test A] Attempting to set month = 13:" << endl;
        Person p;
        p.setBirthDate(10, 13, 1998);
    }
    catch (const InvalidDateException& e) {
        cout << "  [EXCEPTION CAUGHT]: " << e.what() << endl;
    }

    // Test B: February 29 in a non-leap year
    try {
        cout << "\n[Test B] Attempting to set date 29.02.2023 (non-leap year):" << endl;
        Person p;
        p.setBirthDate(29, 2, 2023);
    }
    catch (const InvalidDateException& e) {
        cout << "  [EXCEPTION CAUGHT]: " << e.what() << endl;
    }

    // Test C: Out of allowed year range (2050)
    try {
        cout << "\n[Test C] Attempting to set year = 2050:" << endl;
        Person p;
        p.setBirthDate(1, 1, 2050);
    }
    catch (const InvalidDateException& e) {
        cout << "  [EXCEPTION CAUGHT]: " << e.what() << endl;
    }

    return 0;
}
