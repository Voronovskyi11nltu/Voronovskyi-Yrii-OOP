#include <iostream>
#include <string>

using namespace std;

// ================= BOOK CLASS =================
class Book {
private:
    string* author;
    string* title;
    string* publisher;
    int year;
    int pages;

public:
    // Default Constructor
    Book() {
        author = new string("");
        title = new string("");
        publisher = new string("");
        year = 0;
        pages = 0;
    }

    // Parameterized Constructor
    Book(const string& a, const string& t, const string& p, int y, int pg) {
        author = new string(a);
        title = new string(t);
        publisher = new string(p);
        year = y;
        pages = pg;
    }

    // Copy Constructor (Deep Copy)
    Book(const Book& other) {
        author = new string(*other.author);
        title = new string(*other.title);
        publisher = new string(*other.publisher);
        year = other.year;
        pages = other.pages;
    }

    // Copy Assignment Operator (Deep Copy)
    Book& operator=(const Book& other) {
        if (this != &other) {
            *author = *other.author;
            *title = *other.title;
            *publisher = *other.publisher;
            year = other.year;
            pages = other.pages;
        }
        return *this;
    }

    // Destructor - Explicitly releases dynamic memory
    ~Book() {
        delete author;
        delete title;
        delete publisher;
        cout << "[Book Destructor]: Memory for book successfully released." << endl;
    }

    // Setter method
    void set(const string& a, const string& t, const string& p, int y, int pg) {
        *author = a;
        *title = t;
        *publisher = p;
        year = y;
        pages = pg;
    }

    // Getter methods
    string getAuthor() const { return *author; }
    string getTitle() const { return *title; }
    string getPublisher() const { return *publisher; }
    int getYear() const { return year; }
    int getPages() const { return pages; }

    // Display method
    void show() const {
        cout << "Author: " << *author
            << " | Title: \"" << *title
            << "\" | Publisher: " << *publisher
            << " | Year: " << year
            << " | Pages: " << pages << endl;
    }
};

// ================= LIBRARY CLASS =================
class Library {
private:
    Book* books;     // Dynamic array of Book objects
    int count;       // Current number of books
    int capacity;    // Maximum capacity

public:
    // Constructor
    Library(int cap = 100) {
        capacity = cap;
        count = 0;
        books = new Book[capacity]; // Dynamic memory allocation for array
    }

    // Destructor
    ~Library() {
        delete[] books; // Releases dynamic array memory
        cout << "[Library Destructor]: Memory for library array successfully released." << endl;
    }

    // Method to add a book (uses set / assignment)
    void addBook(const Book& book) {
        if (count < capacity) {
            books[count] = book;
            count++;
        }
        else {
            cout << "Error: Library is full!" << endl;
        }
    }

    // Display all books
    void show() const {
        if (count == 0) {
            cout << "Library is empty." << endl;
            return;
        }
        cout << "\n--- LIBRARY BOOK LIST ---" << endl;
        for (int i = 0; i < count; i++) {
            books[i].show();
        }
        cout << "-------------------------\n" << endl;
    }

    // Search methods
    void searchByAuthor(const string& targetAuthor) const {
        bool found = false;
        cout << "Search by author '" << targetAuthor << "':" << endl;
        for (int i = 0; i < count; i++) {
            if (books[i].getAuthor() == targetAuthor) {
                books[i].show();
                found = true;
            }
        }
        if (!found) cout << "   No books found." << endl;
    }

    void searchByTitle(const string& targetTitle) const {
        bool found = false;
        cout << "Search by title '" << targetTitle << "':" << endl;
        for (int i = 0; i < count; i++) {
            if (books[i].getTitle() == targetTitle) {
                books[i].show();
                found = true;
            }
        }
        if (!found) cout << "   No books found." << endl;
    }

    void searchByPublisher(const string& targetPublisher) const {
        bool found = false;
        cout << "Search by publisher '" << targetPublisher << "':" << endl;
        for (int i = 0; i < count; i++) {
            if (books[i].getPublisher() == targetPublisher) {
                books[i].show();
                found = true;
            }
        }
        if (!found) cout << "   No books found." << endl;
    }

    void searchByYear(int targetYear) const {
        bool found = false;
        cout << "Search by year '" << targetYear << "':" << endl;
        for (int i = 0; i < count; i++) {
            if (books[i].getYear() == targetYear) {
                books[i].show();
                found = true;
            }
        }
        if (!found) cout << "   No books found." << endl;
    }
};

// ================= MAIN FUNCTION =================
int main() {
    // Create library object (capacity = 10)
    Library myLib(10);

    // Using parameterized constructor
    Book b1("Shevchenko", "Kobzar", "Osnova", 1840, 114);
    Book b2("Franko", "Zakhar Berkut", "Dnipro", 1883, 250);
    Book b3("Kostenko", "Marusia Churai", "Soviet Writer", 1979, 160);

    // Using default constructor and set() method
    Book b4;
    b4.set("Shevchenko", "Haidamaky", "Osnova", 1841, 150);

    // Adding books to library
    myLib.addBook(b1);
    myLib.addBook(b2);
    myLib.addBook(b3);
    myLib.addBook(b4);

    // Display all books
    myLib.show();

    // Testing search methods
    myLib.searchByAuthor("Shevchenko");
    cout << endl;

    myLib.searchByTitle("Zakhar Berkut");
    cout << endl;

    myLib.searchByPublisher("Soviet Writer");
    cout << endl;

    myLib.searchByYear(1841);
    cout << endl;

    return 0;
}