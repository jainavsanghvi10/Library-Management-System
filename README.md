# Library-Management-System

This project is a complete library management system developed using a menu-driven approach. The application supports the following functionalities:
* Add book
* Add student
* Delete book
* Delete student
* Issue book
* Search book by ISBN
* Search book by title
* Search student by roll number
* Search student by name
* Exit
Using this system, librarians can easily manage their collection of books and keep track of student borrowing history. The system allows for adding and deleting books and students, issuing books to students, and searching for books or students by various criteria.

## Instructions for this project:
1. rollno_libsys.c : Supports libsys.h implementations
2. rollno_menu.c : Supports menu driven functionality calling functions from roll_libsys.c
3. Use given testcase.in file to test the application. Implement libsys_tester.c referring to testcase.in to test your 
code.
4. Use simple_tester.c referring to sample_output.pdf to test your functions.

## Constraints for this project:
1. All the above functionalities related to Book and Student uses indexing.
2. Delete_book checks the issue data. If the book is already issued then we can not perform delete operation.
3. search_book by isbn and search book by title prints following details :
book details
issue status
and if book is issued then student details holding that book.
4.Issue_book ensures the book and student both values are available. 
