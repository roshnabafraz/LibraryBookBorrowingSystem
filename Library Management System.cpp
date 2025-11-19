#include <iostream>
#include <queue>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

// Structure to store book details
struct Book {
    int id;
    string title;
    bool isBorrowed;
};

// Structure to store borrower details
struct Borrower {
    int id;
    string name;
    int priority;
    int requestedBookId;
};

// Global variables
Book library[20];
queue<Borrower> borrowerQueue;
mutex libraryMutex;

// Function to initialize sample books
void initializeBooks() {
    for (int i = 0; i < 20; i++) {
        library[i] = {i + 1, "Book " + to_string(i + 1), false};
    }
}

// Function to display all books
void displayBooks() {
    cout << "\nLibrary Books:\n";
    for (const auto& book : library) {
        cout << "ID: " << book.id << ", Title: " << book.title
             << ", Status: " << (book.isBorrowed ? "Borrowed" : "Available") << endl;
    }
}

// Function to process a borrower request
void processBorrower() {
    while (true) {
        libraryMutex.lock();

        if (borrowerQueue.empty()) {
            // Check if all books are returned
            bool allReturned = true;
            for (const auto& book : library) {
                if (book.isBorrowed) {
                    allReturned = false;
                    break;
                }
            }

            if (allReturned) {
                libraryMutex.unlock();
                break;
            }

            libraryMutex.unlock();
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }

        Borrower currentBorrower = borrowerQueue.front();
        borrowerQueue.pop();

        Book& requestedBook = library[currentBorrower.requestedBookId - 1];

        if (requestedBook.isBorrowed) {
            cout << "Borrower " << currentBorrower.name << " is waiting for Book " << requestedBook.title << " to be returned.\n";
            borrowerQueue.push(currentBorrower); // Re-add to queue
        } else {
            requestedBook.isBorrowed = true;
            cout << "Borrower " << currentBorrower.name << " has borrowed Book " << requestedBook.title << ".\n";

            // Simulate book being returned after some time
            thread returnThread([&, currentBorrower, &requestedBook]() {
                this_thread::sleep_for(chrono::seconds(5)); // Simulate borrowing duration
                libraryMutex.lock();
                requestedBook.isBorrowed = false;
                cout << "Book " << requestedBook.title << " has been returned by Borrower " << currentBorrower.name << ".\n";
                libraryMutex.unlock();
            });
            returnThread.detach();
        }

        libraryMutex.unlock();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    initializeBooks();
    displayBooks();

    // Sample borrowers
    borrowerQueue.push({1, "Alice", 1, 5});
    borrowerQueue.push({2, "Bob", 0, 5});
    borrowerQueue.push({3, "Charlie", 2, 10});
    borrowerQueue.push({4, "Dave", 0, 15});
    borrowerQueue.push({5, "Eve", 1, 5});

    // Start processing borrowers
    thread t1(processBorrower);
    thread t2(processBorrower);

    t1.join();
    t2.join();

    displayBooks();

    return 0;
}
