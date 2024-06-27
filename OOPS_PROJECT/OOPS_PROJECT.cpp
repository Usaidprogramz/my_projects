#include <iostream>
#include <string>
#include <limits> 

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_ACCOUNTS = 100;
const int MAX_BOOKS = 100;

const int STUDENT_GRADE_MANAGEMENT = 1;
const int BANK_ACCOUNT_MANAGEMENT = 2;
const int LIBRARY_MANAGEMENT = 3;
const int EXIT_PROGRAM = 4;

const int ADD_STUDENT = 1;
const int DISPLAY_ALL_STUDENTS = 2;

const int CREATE_ACCOUNT = 1;
const int DEPOSIT_MONEY = 2;
const int WITHDRAW_MONEY = 3;
const int DISPLAY_ALL_ACCOUNTS = 4;

const int ADD_BOOK = 1;
const int BORROW_BOOK = 2;
const int RETURN_BOOK = 3;
const int DISPLAY_ALL_BOOKS = 4;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class Student {
private:
    string name;
    int rollNumber;
    int grades[3];

public:
    void inputDetails() {
        cout << "Enter name: ";
        cin >> ws; // clear leading whitespace
        getline(cin, name);
        cout << "Enter roll number: ";
        while (!(cin >> rollNumber)) {
            cout << "Invalid input. Enter a valid roll number: ";
            clearInputBuffer();
        }
        cout << "Enter grades for 3 subjects: ";
        for (int i = 0; i < 3; ++i) {
            while (!(cin >> grades[i])) {
                cout << "Invalid input. Enter a valid grade: ";
                clearInputBuffer();
            }
        }
    }

    double calculateAverage() const {
        int total = 0;
        for (int i = 0; i < 3; ++i) {
            total += grades[i];
        }
        return static_cast<double>(total) / 3;
    }

    char getGrade() const {
        double average = calculateAverage();
        if (average >= 90) return 'A';
        else if (average >= 80) return 'B';
        else if (average >= 70) return 'C';
        else if (average >= 60) return 'D';
        else return 'F';
    }

    void displayDetails() const {
        cout << "Name: " << name << "\nRoll Number: " << rollNumber;
        cout << "\nGrades: ";
        for (int i = 0; i < 3; ++i) {
            cout << grades[i] << " ";
        }
        cout << "\nAverage: " << calculateAverage();
        cout << "\nGrade: " << getGrade() << "\n";
    }
};

class StudentManager {
private:
    Student students[MAX_STUDENTS];
    int studentCount;

public:
    StudentManager() : studentCount(0) {}

    void addStudent() {
        if (studentCount < MAX_STUDENTS) {
            students[studentCount].inputDetails();
            ++studentCount;
        } else {
            cout << "Student limit reached. Cannot add more students.\n";
        }
    }

    void displayAllStudents() const {
        clearScreen();
        for (int i = 0; i < studentCount; ++i) {
            students[i].displayDetails();
            cout << "\n";
        }
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
};

class BankAccount {
private:
    string accountHolder;
    int accountNumber;
    double balance;

public:
    BankAccount() : accountHolder(""), accountNumber(0), balance(0) {}

    void createAccount(const string& name, int accNum, double bal) {
        accountHolder = name;
        accountNumber = accNum;
        balance = bal;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << "\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            cout << "Withdrawn: " << amount << "\n";
        }
    }

    void displayAccountDetails() const {
        cout << "Account Holder: " << accountHolder << "\nAccount Number: " << accountNumber << "\nBalance: " << balance << "\n";
    }
};

class BankAccountManager {
private:
    BankAccount accounts[MAX_ACCOUNTS];
    int accountCount;

    BankAccount* findAccount(int accNum) {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].getAccountNumber() == accNum) {
                return &accounts[i];
            }
        }
        return NULL;
    }

public:
    BankAccountManager() : accountCount(0) {}

    void createAccount() {
        if (accountCount < MAX_ACCOUNTS) {
            string name;
            int accNum;
            double initialBalance;

            cout << "Enter account holder's name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Enter account number: ";
            while (!(cin >> accNum)) {
                cout << "Invalid input. Enter a valid account number: ";
                clearInputBuffer();
            }
            cout << "Enter initial balance: ";
            while (!(cin >> initialBalance)) {
                cout << "Invalid input. Enter a valid initial balance: ";
                clearInputBuffer();
            }

            accounts[accountCount].createAccount(name, accNum, initialBalance);
            ++accountCount;
        } else {
            cout << "Account limit reached. Cannot create more accounts.\n";
        }
    }

    void deposit() {
        int accNum;
        double amount;
        cout << "Enter account number: ";
        while (!(cin >> accNum)) {
            cout << "Invalid input. Enter a valid account number: ";
            clearInputBuffer();
        }
        cout << "Enter amount to deposit: ";
        while (!(cin >> amount)) {
            cout << "Invalid input. Enter a valid amount: ";
            clearInputBuffer();
        }

        BankAccount* account = findAccount(accNum);
        if (account != NULL) {
            account->deposit(amount);
        } else {
            cout << "Account not found\n";
        }
    }

    void withdraw() {
        int accNum;
        double amount;
        cout << "Enter account number: ";
        while (!(cin >> accNum)) {
            cout << "Invalid input. Enter a valid account number: ";
            clearInputBuffer();
        }
        cout << "Enter amount to withdraw: ";
        while (!(cin >> amount)) {
            cout << "Invalid input. Enter a valid amount: ";
            clearInputBuffer();
        }

        BankAccount* account = findAccount(accNum);
        if (account != NULL) {
            account->withdraw(amount);
        } else {
            cout << "Account not found\n";
        }
    }

    void displayAllAccounts() const {
        clearScreen();
        for (int i = 0; i < accountCount; ++i) {
            accounts[i].displayAccountDetails();
            cout << "\n";
        }
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
};

// Book Class
class Book {
private:
    string title;
    string author;
    bool isAvailable;

public:
    Book() : title(""), author(""), isAvailable(true) {}

    void addBook(const string& t, const string& a) {
        title = t;
        author = a;
        isAvailable = true;
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    bool checkAvailability() const {
        return isAvailable;
    }

    void borrowBook() {
        if (isAvailable) {
            isAvailable = false;
            cout << "You have borrowed the book: " << title << "\n";
        } else {
            cout << "Book is not available\n";
        }
    }

    void returnBook() {
        isAvailable = true;
        cout << "You have returned the book: " << title << "\n";
    }

    void displayBookDetails() const {
        cout << "Title: " << title << "\nAuthor: " << author << "\nAvailability: " << (isAvailable ? "Available" : "Not Available") << "\n";
    }
};

class Library {
private:
    Book books[MAX_BOOKS];
    int bookCount;

public:
    Library() : bookCount(0) {}

    void addBook() {
        if (bookCount < MAX_BOOKS) {
            string title, author;
            cout << "Enter book title: ";
            cin >> ws;
            getline(cin, title);
            cout << "Enter book author: ";
            cin >> ws;
            getline(cin, author);

            books[bookCount].addBook(title, author);
            ++bookCount;
            cout << "Book added: " << title << "\n";
        } else {
            cout << "Book limit reached. Cannot add more books.\n";
        }
    }

    void borrowBook() {
        string title;
        cout << "Enter book title to borrow: ";
        cin >> ws;
        getline(cin, title);

        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getTitle() == title) {
                books[i].borrowBook();
                return;
            }
        }
        cout << "Book not found\n";
    }

    void returnBook() {
        string title;
        cout << "Enter book title to return: ";
        cin >> ws;
        getline(cin, title);

        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getTitle() == title) {
                books[i].returnBook();
                return;
            }
        }
        cout << "Book not found\n";
    }

    void displayAllBooks() const {
        clearScreen();
        for (int i = 0; i < bookCount; ++i) {
            books[i].displayBookDetails();
            cout << "\n";
        }
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
};

int main() {
    StudentManager studentManager;
    BankAccountManager accountManager;
    Library library;

    int mainChoice;
    do {
        clearScreen();
        cout << "\n1. Student Grade Management\n2. Bank Account Management\n3. Library Management\n4. Exit\nEnter your choice: ";
        cin >> mainChoice;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue;
        }

        switch (mainChoice) {
            case STUDENT_GRADE_MANAGEMENT: {
                int studentChoice;
                cout << "\n1. Add Student\n2. Display All Students\nEnter your choice: ";
                cin >> studentChoice;

                if (cin.fail()) {
                    clearInputBuffer();
                    continue;
                }

                switch (studentChoice) {
                    case ADD_STUDENT:
                        studentManager.addStudent();
                        break;
                    case DISPLAY_ALL_STUDENTS:
                        studentManager.displayAllStudents();
                        break;
                    default:
                        cout << "Invalid choice\n";
                        break;
                }
                break;
            }
            case BANK_ACCOUNT_MANAGEMENT: {
                int accountChoice;
                cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Display All Accounts\nEnter your choice: ";
                cin >> accountChoice;

                if (cin.fail()) {
                    clearInputBuffer();
                    continue;
                }

                switch (accountChoice) {
                    case CREATE_ACCOUNT:
                        accountManager.createAccount();
                        break;
                    case DEPOSIT_MONEY:
                        accountManager.deposit();
                        break;
                    case WITHDRAW_MONEY:
                        accountManager.withdraw();
                        break;
                    case DISPLAY_ALL_ACCOUNTS:
                        accountManager.displayAllAccounts();
                        break;
                    default:
                        cout << "Invalid choice\n";
                        break;
                }
                break;
            }
            case LIBRARY_MANAGEMENT: {
                int libraryChoice;
                cout << "\n1. Add Book\n2. Borrow Book\n3. Return Book\n4. Display All Books\nEnter your choice: ";
                cin >> libraryChoice;

                if (cin.fail()) {
                    clearInputBuffer();
                    continue;
                }

                switch (libraryChoice) {
                    case ADD_BOOK:
                        library.addBook();
                        break;
                    case BORROW_BOOK:
                        library.borrowBook();
                        break;
                    case RETURN_BOOK:
                        library.returnBook();
                        break;
                    case DISPLAY_ALL_BOOKS:
                        library.displayAllBooks();
                        break;
                    default:
                        cout << "Invalid choice\n";
                        break;
                }
                break;
            }
            case EXIT_PROGRAM:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice\n";
                break;
        }
    } while (mainChoice != EXIT_PROGRAM);

    return 0;
}

