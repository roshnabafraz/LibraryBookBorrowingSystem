# Library Book Borrowing System (OS Project – 5th Semester)

## Introduction

This **Library Book Borrowing System** was developed as a 5th-semester Operating Systems project. It simulates the borrowing and returning of books in a library using C++ and demonstrates key OS concepts like **multithreading**, **mutexes**, and **synchronization**. The system manages multiple borrowers concurrently while ensuring data consistency and safe access to shared resources.


## Objectives

* Simulate a real-world library book borrowing system.  
* Handle multiple borrower requests concurrently using threads.  
* Demonstrate thread-safe access to shared resources with mutexes.  
* Apply OS concepts like queues, multithreading, and synchronization in practice.  

## Features

1. **Book Management**: Maintains a collection of 20 books with unique IDs and titles.  
2. **Borrower Queue**: Manages multiple borrowers requesting books.  
3. **Concurrency**: Handles simultaneous borrower requests using threads.  
4. **Synchronization**: Ensures thread-safe operations on shared resources using mutexes.  
5. **Simulation**: Implements borrowing and returning delays to mimic real-world library operations.  
6. **Future Priority Handling**: Can be extended to process borrowers based on priority.  

## Program Flow

1. Initialize the library with books.  
2. Display initial book statuses.  
3. Add borrowers to the queue.  
4. Start threads to process borrower requests concurrently.  
5. Threads manage borrowing, waiting for unavailable books, and returning books.  
6. The program continues until all books are returned.  
7. Display final book statuses.  


## Advantages

* Practical implementation of OS concepts like **threads**, **mutexes**, and **synchronization**.  
* Efficiently manages multiple concurrent borrower requests.  
* Simulates real-world borrowing and returning delays.  
* Scalable for more books and borrowers.  


## Limitations

* Priority-based borrower processing is not fully implemented.  
* Careful thread management is required to avoid potential deadlocks.  
* Simple simulation; real-world library systems are more complex.  


## Future Enhancements

* Implement borrower priority handling.  
* Add a graphical user interface (GUI).  
* Include book reservation functionality.  
* Integrate persistent storage (database) for records.  
* Improve logging and debugging features.  

---

## Conclusion

This project successfully demonstrates a **Library Book Borrowing System** using C++ with OS-level concepts like multithreading and mutex synchronization. It effectively handles multiple borrowers concurrently and simulates real-world library operations while highlighting areas for future improvement.
