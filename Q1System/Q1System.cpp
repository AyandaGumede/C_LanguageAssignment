#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Resource class
class Resource {
protected:
    string title;
    string author;
    int isbn; 
    string type;

public:
    // Constructor
    Resource(string title, string author, int isbn, string type) {
        this->title = title;
        this->author = author;
        this->isbn = isbn;
        this->type = type;
    }

    string getTitle() const {
        return title;
    }
    string getAuthor() const {
        return author;
    }
    int getISBN() const {
        return isbn;
    }
    string getType() const {
        return type;
    }

    void details() const {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << isbn << ", Type: " << type << endl;
    }
};

//Book, Journa, and DigitalResource class and Inherited class
class Book : public Resource {
public:
    Book(string title, string author, int isbn) : Resource(title, author, isbn, "Book") {}
};

class Journal : public Resource {
public:
    Journal(string title, string author, int isbn) : Resource(title, author, isbn, "Journal") {}
};

class DigitalResource : public Resource { 
public:
    DigitalResource(string title, string author, int isbn) : Resource(title, author, isbn, "Digital Resource") {}
};

class Catalog {
private:
    vector<Resource*> shelf;

public:
    ~Catalog() { 
        for (auto resource : shelf) {
            delete resource; 
        }
    }

    // Add method
    void addResource(Resource* resource) {
        shelf.push_back(resource);
        cout << "- - - - - - - - - - - - - - - - - - - - - - - -  - - - - - " << endl;
        cout << "The following resource was successfully added: " << endl;
        resource->details();
    }

    // Report method
    void report() {
        if (shelf.empty()) {
            cout << "Shelf is currently empty" << endl;
        }
        else {
            vector<Resource*> books, journals, digitalResources;

            for (const Resource* item : shelf) {
                if (item->getType() == "Book") {
                    books.push_back((Resource*)item);
                }
                else if (item->getType() == "Journal") {
                    journals.push_back((Resource*)item);
                }
                else if (item->getType() == "Digital Resource") {
                    digitalResources.push_back((Resource*)item);
                }
            }

            if (!books.empty()) {
                cout << "Books: " << endl;
                for (Resource* item : books) {
                    item->details();
                }
            }

            if (!journals.empty()) {
                cout << "Journals: " << endl;
                for (Resource* item : journals) {
                    item->details();
                }
            }

            if (!digitalResources.empty()) {
                cout << "Digital Resources: " << endl;
                for (Resource* item : digitalResources) {
                    item->details();
                }
            }
        }
    }

    // Removing method
    void removeResource(int isbn) {
        auto it = remove_if(shelf.begin(), shelf.end(), [isbn](Resource* resource) {
            return resource->getISBN() == isbn;
            });

        if (it != shelf.end()) {
            delete* it; 
            shelf.erase(it, shelf.end()); 
            cout << "Resource with ISBN " << isbn << " was successfully removed." << endl;
        }
        else {
            cout << "Resource with ISBN " << isbn << " not found." << endl;
        }
    }

    //Searching method
    void searchResource(string title, string author, int isbn, string type) {
        for (const auto& item : shelf) {
            if ((item->getTitle() == title || title.empty()) &&
                (item->getAuthor() == author || author.empty()) &&
                (item->getISBN() == isbn || isbn == 0) && 
                (item->getType() == type || type.empty())) {
                item->details();
                return;
            }
        }
        cout << "Resource not found!" << endl;
    }
};

int main() {
    Catalog librarySystem;
    int choice;

    do {
        cout << "\n1. Add Resource" << endl;
        cout << "2. Report" << endl;
        cout << "3. Remove Resource" << endl; 
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); 

        if (choice == 1) {
            string type;

            cout << "Enter type (Book/Journal/DigitalResource): ";
            getline(cin, type);

            string title;
            cout << "Enter title: ";
            getline(cin, title);

            string author;
            cout << "Enter author: ";
            getline(cin, author);

            int isbn; 
            cout << "Enter ISBN: ";
            cin >> isbn;
            cin.ignore(); 

            if (type == "Book" || type == "book") {
                librarySystem.addResource(new Book(title, author, isbn));
            }
            else if (type == "Journal" || type == "journal") {
                librarySystem.addResource(new Journal(title, author, isbn));
            }
            else if (type == "DigitalResource" || type == "digitalresource" || type == "Digital Resource") {
                librarySystem.addResource(new DigitalResource(title, author, isbn));
            }
            else {
                cout << "Resource type is unknown." << endl;
            }
        }
        else if (choice == 2) {
            librarySystem.report();
        }
        else if (choice == 3) { /
            int isbn;
            cout << "Enter ISBN of the resource to remove: ";
            cin >> isbn;
            librarySystem.removeResource(isbn);
        }
        else if (choice != 4) {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 4); 

    cout << "Goodbye!" << endl;
    return 0;
}
