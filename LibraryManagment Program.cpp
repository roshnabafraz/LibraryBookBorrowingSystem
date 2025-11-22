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
    
    cout<<"\n\n\n--------------------------------------------";
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
            cout << "Borrower " << currentBorrower.name << " is waiting for " << requestedBook.title << " to be returned.\n";
            borrowerQueue.push(currentBorrower); // Re-add to queue
        } else {
            requestedBook.isBorrowed = true;
            cout << "--> Borrower " << currentBorrower.name << " has borrowed " << requestedBook.title << ".\n";

            // Simulate book being returned after some time
            thread returnThread([&, currentBorrower, &requestedBook]() {
                this_thread::sleep_for(chrono::seconds(5)); // Simulate borrowing duration
                libraryMutex.lock();
                requestedBook.isBorrowed = false;
                cout << requestedBook.title << " has been returned by Borrower " << currentBorrower.name << ".\n";
                libraryMutex.unlock();
            });
            returnThread.detach();
        }

        libraryMutex.unlock();
        this_thread::sleep_for(chrono::seconds(1)); // Simulate some delay
    }
}

// Main function to simulate the library book borrowing system
int main() {
    initializeBooks();
    displayBooks();
    cout<<"\n\n\n\n";

    // Sample borrowers
    borrowerQueue.push({1, "Roshnab", 1, 5});
    borrowerQueue.push({2, "Jannat", 0, 5});
    borrowerQueue.push({3, "Aimn", 2, 10});
    borrowerQueue.push({4, "Fizza", 0, 15});
    borrowerQueue.push({5, "Daniyal", 1, 5});

    // Start processing borrowers
    thread t1(processBorrower);
    thread t2(processBorrower);

    t1.join();
    t2.join();


    return 0;
}
