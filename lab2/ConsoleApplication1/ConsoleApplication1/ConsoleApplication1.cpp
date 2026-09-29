#include <iostream>
#include <string>

using namespace std;

// ================ BOOK CLASS ================
class Book {
private:
    string author;
    string title;
    string publisher;
    int year;
    int pages;

public:
    // Default constructor
    Book() : author(""), title(""), publisher(""), year(0), pages(0) {}

    // Parameterized constructor
    Book(string a, string t, string p, int y, int pg) {
        set(a, t, p, y, pg);
    }

    // Destructor
    ~Book() {
        // No dynamic memory in this class, so the destructor is empty
    }

    // set() method to assign values
    void set(string a, string t, string p, int y, int pg) {
        author = a;
        title = t;
        publisher = p;
        year = y;
        pages = pg;
    }

    // Getter methods to access private fields (required for searching)
    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    string getPublisher() const { return publisher; }
    int getYear() const { return year; }
    int getPages() const { return pages; }

    // show() method to print book details
    void show() const {
        cout << "Author: " << author
            << " | Title: \"" << title
            << "\" | Publisher: " << publisher
            << " | Year: " << year
            << " | Pages: " << pages << endl;
    }
};

// ================ LIBRARY CLASS ================
class Library {
private:
    Book* books;    // Dynamic array of Book objects
    int count;       // Current number of books
    int capacity;    // Maximum capacity of the library

public:
    // Constructor
    Library(int cap = 100) {
        capacity = cap;
        count = 0;
        books = new Book[capacity]; // Dynamic memory allocation
    }

    // Destructor
    ~Library() {
        delete[] books; // Freeing memory to prevent memory leaks
    }

    // Method to add a book (library equivalent of a setter)
    void addBook(const Book& book) {
        if (count < capacity) {
            books[count] = book;
            count++;
        }
        else {
            cout << "Error: Library is full!" << endl;
        }
    }

    // show() method to print all books
    void show() const {
        if (count == 0) {
            cout << "Library is empty." << endl;
            return;
        }
        cout << "\n--- LIST OF BOOKS IN THE LIBRARY ---" << endl;
        for (int i = 0; i < count; i++) {
            books[i].show();
        }
        cout << "------------------------------------\n" << endl;
    }

    // --- SEARCH METHODS ---

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
        cout << "Search by publication year '" << targetYear << "':" << endl;
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
    // Creating a Library object (capacity of 10 books)
    Library myLib(10);

    // Using the parameterized constructor
    Book b1("Shevchenko", "Kobzar", "Osnova", 1840, 114);
    Book b2("Franko", "Zakhar Berkut", "Dnipro", 1883, 250);
    Book b3("Kostenko", "Marusia Churai", "Radianskyi Pysmennyk", 1979, 160);

    // Creating a book using the default constructor and set() method
    Book b4;
    b4.set("Shevchenko", "Haidamaky", "Osnova", 1841, 150);

    // Adding books to the library array
    myLib.addBook(b1);
    myLib.addBook(b2);
    myLib.addBook(b3);
    myLib.addBook(b4);

    // Displaying all contents
    myLib.show();

    // Testing individual assignment methods
    myLib.searchByAuthor("Shevchenko");
    cout << endl;

    myLib.searchByTitle("Zakhar Berkut");
    cout << endl;

    myLib.searchByPublisher("Radianskyi Pysmennyk");
    cout << endl;

    myLib.searchByYear(1841);

    return 0;
}