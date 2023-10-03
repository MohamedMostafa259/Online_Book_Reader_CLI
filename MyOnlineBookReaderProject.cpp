#include<iostream>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>
using namespace std;

//////////////////////////////////////// Menu Methods ////////////////////////////////////////
int readMenuChoice(int low, int high) {
    int choice;
    cout << "Enter number in range [" << low << " - " << high <<"] : ";
    cin >> choice;
    
    if (low <= choice && choice <= high)
        return choice;

	cout << "ERROR: invalid number...Try again\n\n";
    return readMenuChoice(low, high);
}
int showReadMenu(const vector<string>& choices) {
    cout << "\nMenu:\n";
    for (int i{0}; i < int(choices.size()); i++)
        cout << "\t" << i+1 << ". " << choices[i] << "\n";
    return readMenuChoice(1, int(choices.size()));
}
/////////////////////////////////////////////////////////////////////////////////////////////

class Customer {
private:
    string userName;
    string password;
    string name;
    string email;
public:
    Customer() = default;
    Customer(const string& userName, const string& password, const string& name, const string& email) : 
            userName(userName), password(password), name(name), email(email) { }
    void print() const {
        cout << "\nName: " << name << "\n"
            << "Email: " << email << "\n"
            << "User Name: " << userName << "\n";
    }
    bool operator<(const Customer& other) const { // a map container needs to compare its keys with each other (I've made a map with Customer keys in the CustomerManager)
        return userName < other.userName;
    }
    void setUserName(const string& userName) {
        // write the below commented code if you want to provide verifications, but I assumed that the user will behave properly.
        /*if (int(userName.find(" ")) != -1) { // userName has a space
            cout << "Spaces are not allowed! ... Try again\n";
            return false;
        } else {
            this->userName = userName;
            return true;            
        }*/
        this->userName = userName;
    }
    
    const string& getUserName() const {return userName;}

    void setPassword(const string& password) {this->password = password;}
    
    const string& getPassword() const {return password;}
    
    void setName(const string& name) {this->name = name;}
    
    const string& getName() const {return name;}
    
    void setEmail(const string& email) {this->email = email;}
    
    const string& getEmail() const {return email;}
    
    void readCustomer() {
        cout << "\n";
        string str;

        cout << "Enter user name (no spaces): ";
        cin >> str;
        setUserName(str);

        cout << "Enter password (no spaces): ";
        cin >> str;
        setPassword(str);
        
        cout << "Enter name (no spaces): ";
        cin >> str;
        setName(str);
        
        cout << "Enter email (no spaces): ";
        cin >> str;
        setEmail(str);
    }
};

class Admin {
private:
    string userName;
    string password;
    string name;
    string email;
public:
    Admin() = default;
    Admin(const string& userName, const string& password, const string& name, const string& email) : 
            userName(userName), password(password), name(name), email(email) { }
    void print() const {
        cout << "\nName: " << name << "\n"
            << "Email: " << email << "\n"
            << "User Name: " << userName << "\n";
    }
    void setUserName(const string& userName) {this->userName = userName;}

    const string& getUserName() const {return userName;}
    
    void setPassword(const string& password) {this->password = password;}
    
    const string& getPassword() const {return password;}
    
    void setName(const string& name) {this->name = name;}
    
    const string& getName() const {return name;}
    
    void setEmail(const string& email) {this->email = email;}
    
    const string& getEmail() const {return email;}
};

class Book {
private:
    string ISBN;
    string title; 
    string authorName;
    int pagesNumber;
    vector<string> pages;
public:
    Book() = default;
    Book(const string& ISBN, const string& title, const string& authorName, int pagesNumber, const vector<string>& pages) : 
        ISBN(ISBN), title(title), authorName(authorName), pagesNumber(pagesNumber), pages(pages) { }
    
    const string& getISBN() const {return ISBN;}

    void setISBN(const string& ISBN) {this->ISBN = ISBN;}

    const string& getTitle() const {return title;}

    void setTitle(const string& title) {this->title = title;}

    const string& getAuthorName() const {return authorName;}

    void setAuthorName(const string& authorName) {this->authorName = authorName;}

    const int& getPagesNumber() const {return pagesNumber;}
    
    const vector<string>& getPages() const {return pages;}

    void setPages(const vector<string>& pages) {this->pages = pages;}

    void readBook() {
        cout << "\n";
        string str;

        cout << "Enter ISBN: ";
        cin >> str;
        setISBN(str);
        
        cout << "Enter Title: ";
        cin >> str;
        setTitle(str);

        cout << "Enter Author Name: ";
        cin >> str;
        setAuthorName(str);

        int pages;
        cout << "How many pages? : ";
        cin >> pages;

        cin.ignore(); // will ignore a single character(the 1st one in the buffer => in this case it is a '\n' character)

        vector<string> content(pages);
        for (int i{0}; i < pages; i++) {
            cout << "Enter Page # " << i+1 << ": ";
            getline(cin, content[i]);
        }
        setPages(content);
    }
};

class CustomerSession {
private:
    string endDate;
    Book book;
    int pageNumber;
public:
    CustomerSession() = default;
    CustomerSession(const Book& book) : book(book), pageNumber(1) { }

    void setEndDate() {
        time_t currentTime{time(nullptr)}; // time() functions takes a pointer to time_t variable to store the current time in this variable(You can pass the nullptr)
        endDate = ctime(&currentTime); // ctime() functions takes a pointer to time_t variable to convert it to a string representation(a human-readable ASCII string.)
        // Note: The ctime() function appends a newline character ('\n') at the end of the string
    }

    const string& getEndDate() const {return endDate;}

    void setBook(const Book& book) {this->book = book;}
    
    const Book& getBook() const {return book;}
    
    void setPageNumber(const int& pageNumber) {this->pageNumber = pageNumber;}
    
    const int& getPageNumber() const {return pageNumber;}
    
    const string getSessionHistory() const {
        ostringstream oss;
        oss << book.getTitle() << " Page: " << pageNumber << "/" << book.getPagesNumber() << " - " << endDate;
        return oss.str();
    }
};

class CustomersManager {
private:
    map<Customer, vector<CustomerSession>> customer_sessions_map;
    Customer currentCustomer;

    void readingMode(CustomerSession& session) { // Also, we can name this function "displaySession".
        vector<string> navigationMenu{"Next Page", "Previous Page", "Stop Reading"};
        int choice;
        int pagesNumber{session.getBook().getPagesNumber()};
        int pageNumber{session.getPageNumber()};
        while (true) {
            cout << "\nCurrent Page: " << pageNumber << "/" << pagesNumber << "\n";
            cout << session.getBook().getPages()[pageNumber-1] << "\n";
            
            choice = showReadMenu(navigationMenu);
            if (choice == 1) {
                if ((pageNumber+1) > pagesNumber)
                    cout << "\nCongratulations! There are no more pages. You've finished this book.\n\n";
                else 
                    pageNumber++;
            }
            else if (choice == 2) {
                if ((pageNumber-1) < 1)
                    cout << "\nThere are no previous pages before this page. This is the 1st page!\n\n";
                else
                    pageNumber--;
            }
            else { // choice = 3 => stopReading
                session.setEndDate();
                session.setPageNumber(pageNumber);
                break;
            }
        }
    }
public:
    CustomersManager() = default;
	CustomersManager(const CustomersManager&) = delete; // No sense for such a class (manager of objects) to be copyable!
	CustomersManager& operator=(const CustomersManager&) = delete; // https://ariya.io/2015/01/c-class-and-preventing-object-copy#:~:text=There%20are%20three%20ways%20to,have%20its%20instance%20copied%20around.

    bool logIn(const string& userName, const string& password) {
        for (const auto& customer_sessions_pair : customer_sessions_map) {
            if (userName == customer_sessions_pair.first.getUserName() && password == customer_sessions_pair.first.getPassword()) {
                currentCustomer = customer_sessions_pair.first;
                return true;
            }
        }
        return false;
    }
    bool signUp(const vector<Admin>& admins) {
        currentCustomer.readCustomer();

       for (const auto& customer_sessions_pair : customer_sessions_map) {
            if (currentCustomer.getUserName() == customer_sessions_pair.first.getUserName())
                return false;
        }
        for (const Admin& admin : admins) {
            if (currentCustomer.getUserName() == admin.getUserName())
                return false;
        }
        customer_sessions_map.insert(make_pair(currentCustomer, vector<CustomerSession>(0)));
        return true;
    }
    void listANDselectFromAvailableBooks(const vector<Book>& availableBooks) {
        vector<string> booksNames;
        for (const auto& book : availableBooks) {
            booksNames.push_back(book.getTitle());
        }
        int choice{showReadMenu(booksNames)};
        
        customer_sessions_map.find(currentCustomer)->second.push_back(CustomerSession(availableBooks[choice-1]));
        CustomerSession& currentSession = customer_sessions_map.find(currentCustomer)->second.back();
        readingMode(currentSession);
    }
    void listANDselectFromReadingHistory() {
        vector<CustomerSession>& sessions{customer_sessions_map.find(currentCustomer)->second};
        if (int(sessions.size()) == 0) {
            cout << "\nYou don't have any sessions in your reading history\n";
            return;
        }
        vector<string> sessionsHistory;
        for (const auto& session : sessions) {
            sessionsHistory.push_back(session.getSessionHistory());
        }
        int choice{showReadMenu(sessionsHistory)};
    /*  (simpler design): if our system allowed to its users to have multiple opened sessions for the same book in their reading history, 
        we would write this code. But currently, we update the chosen session in the reading history (we don't provide another one for the same book).

        sessions.push_back(sessions[choice-1]);
        CustomerSession& currentSession = sessions.back();
        readingMode(currentSession);
    */
        readingMode(sessions[choice-1]);
    }

    const Customer& getCurrentCustomer() {return currentCustomer;}
};

class AdminsManager {
private:
    vector<Admin> admins;
    Admin currentAdmin;
public:
    AdminsManager() { // hard-coded
        admins.push_back(Admin("mohamed", "123", "mohamed_mostafa", "mohamed@gmail.com"));
        admins.push_back(Admin("ali", "456", "ali_king", "ali@gmail.com"));
        admins.push_back(Admin("omar", "789", "omar_hero", "omar@gmail.com"));
    }
	AdminsManager(const AdminsManager&) = delete; // No sense for such a class (manager of objects) to be copyable!
	AdminsManager& operator=(const AdminsManager&) = delete; // https://ariya.io/2015/01/c-class-and-preventing-object-copy#:~:text=There%20are%20three%20ways%20to,have%20its%20instance%20copied%20around.
    
    bool logIn(const string& userName, const string& password) {
        for (const auto& admin : admins) {
            if (userName == admin.getUserName() && password == admin.getPassword()) {
                currentAdmin = admin;
                return true;
            }
        }
        return false;
    }
    Book addBook() {
        Book book;
        book.readBook();
        return book;
    }
    
    const vector<Admin>& getAdmins() {return admins;} 

    const Admin& getCurrentAdmin() {return currentAdmin;}
};

class BooksManager {
private:
    vector<Book> books;
public:
    BooksManager() { // hard-coded => for simplicity I put them in the default constructor, but for a better design: ↓↓↓ 
                    // we should implement these lines in a loadDataBase() function that reads from files or any other source
        books.push_back(Book("111-222-333", "C++ How To Program", "Mohamed Mostafa", 6, vector<string>{"C++", "is", "the", "best", "programming", "language"}));
        books.push_back(Book("444-555-666", "Intro To Algorithms", "Mohamed Mostafa", 4, vector<string>{"You", "should", "learn", "algorithms"}));
        books.push_back(Book("777-888-999", "Data Structures in C++", "Mohamed Mostafa", 5, vector<string>{"Data", "structures", "are", "very", "important"}));
    }
	BooksManager(const BooksManager&) = delete; // No sense for such a class (manager of objects) to be copyable!
	BooksManager& operator=(const BooksManager&) = delete; // https://ariya.io/2015/01/c-class-and-preventing-object-copy#:~:text=There%20are%20three%20ways%20to,have%20its%20instance%20copied%20around.

    const vector<Book>& getAvailableBooks() const {return books;}

    void addBook(const Book& book) {books.push_back(book);}
};

class OnlineBookReaderSystem {
private:
    CustomersManager customersManager;
    AdminsManager adminsManager;
    BooksManager booksManager;

    int logIn() { // return 1 for true Admin, -1 for true Customer, and 0 for false
        string userName;
        cout << "Enter user name: ";
        cin >> userName;

        string password;
        cout << "Enter password: ";
        cin >> password;

        if (customersManager.logIn(userName, password))
            return -1;
        else if (adminsManager.logIn(userName, password))
            return 1;
        else
            return 0;
    }
    void accessSystem() {
        vector<string> menu{"Login", "Sign Up"};
        int choice{showReadMenu(menu)};

        if (choice == 1) {
            int entry{logIn()};

            if (entry == 1)
                adminView();
            else if (entry == -1)
                CustomerView();
            else
                cout << "Wrong user name or password!! ... Try again\n\n";
        } 
        else {
            if (customersManager.signUp(adminsManager.getAdmins()))
                CustomerView();
            else
                cout << "\nThis user name exists!! Try again\n";
        }
    }
    void adminView() {
        cout << "\nHello, " << adminsManager.getCurrentAdmin().getName() << " | Admin View\n";
        vector<string> choices{"View Profile", "Add Book", "Logout"};
        while (true) {
            int choice{showReadMenu(choices)};
            if (choice == 1) {
                adminsManager.getCurrentAdmin().print();
            }
            else if (choice == 2) {
                const Book& book{adminsManager.addBook()};
                booksManager.addBook(book);
            }
            else
                break;
        }
    }
    void CustomerView() {
        cout << "\nHello, " << customersManager.getCurrentCustomer().getName() << " | Customer View\n";
        vector<string> choices{"View Profile", "List & Select from My Reading History", "List & Select from Available Books", "Logout"};
        while (true) {
            int choice{showReadMenu(choices)};

            if (choice == 1) 
                customersManager.getCurrentCustomer().print();
            else if (choice == 2)
                customersManager.listANDselectFromReadingHistory();
            else if (choice == 3)
                customersManager.listANDselectFromAvailableBooks(booksManager.getAvailableBooks());
            else
                break;
        }
    }
public:
    OnlineBookReaderSystem() = default;

    void run() {
        while (true)
            accessSystem();
    }
};

int main() {
	OnlineBookReaderSystem system;
    system.run();
	return 0;
}
