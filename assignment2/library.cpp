#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
};

class Library {
public:
    void add_book(int book_id, const char* title, const char* author);
    void remove_book(int book_id);
    void display_books();

private:
    map<int, Book> books;
};

void Library::add_book(int book_id, const char* title, const char* author) {
    // Check if book with the given ID already exists in the library
    if (books.count(book_id) != 0) {
        cout << "Book with ID " << book_id << " is in the library." << endl;
    } 
    else {
        // Create a new Book struct and add it to the map
        Book new_book = {book_id, title, author};
        books[book_id] = new_book;

        // Output a message indicating that the book was added
        cout << "Book with ID " << book_id << " has been added to the library." << endl;
    }
}

void Library::remove_book(int book_id) {
    // Check if book with the given ID exists in the library
    if (books.count(book_id) != 0) {
        // Remove the book from the map
        books.erase(book_id);

        // Output a message indicating that the book was removed
        cout << "Book with ID " << book_id << " has been removed from the library" << endl;
    } else {
        // Output a message indicating that the book was not found
        cout << "Book with ID " << book_id << " is not in the library." << endl;
    }
}

void Library::display_books() {
    // Output a header for the book list
    cout << "Books in the library : "<< endl ;

    // Iterate over the books in the map and output their information
 for (const auto& book : books) {
           cout << "ID: " << book.first << ", Title: " << book.second.title << ", Author: " << book.second.author << endl;
}
}

int main() {
    // Create a Library object
    Library library;

    // Add some books to the library
    library.add_book(1, "Rapunzel", " Wilhelm Grimm");
    library.add_book(2, "Cinderella, or, The little glass slipper", "C Fitzgerald");
    library.add_book(3, "Snow White", "Jacob Grimm");

    // Display all books in the library
    library.display_books();

    // Remove a book from the library
    library.remove_book(3);

    // Display all books in the library again
    library.display_books();

    return 0;
}