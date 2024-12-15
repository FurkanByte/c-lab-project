//
// Created by Furkan on 15.12.2024.
// This file created for EENG212 Lab Project
// Library Management System with Structers and Arrays
//

#include <stdio.h>
#include <string.h>

//Book Structer
typedef struct {
    int bookID;
    char title[100];
    char author[100]; 
    int yearPublished;
    int isAvailable; // 1 available: 0 not available
} book;

//User Structer
typedef struct {
    int userID;
    char name[100];
    int checkedOutBooks[10]; //IDs of the books borrowed by the user.
    int borrowedBooksCount;
} user;

//Function Prototypes
void addBook();
void deleteBook();
int searchBookByTitle();
int searchBookByAuthor();
void checkOutBook();
void returnBook();
void listBooks();
void listBorrowedBooks(); //by a user
int menu();

//Global Variables
book books[100];
int bookCount = 0;
user users[50];
int userCount = 0;


void main(){
    //Users definitions
    users[0].userID = 1;
    strcpy(users[0].name, "Furkan");
    users[0].borrowedBooksCount = 0;

    users[1].userID = 2;
    strcpy(users[1].name, "Albert");
    users[1].borrowedBooksCount = 0;

    users[2].userID = 3;
    strcpy(users[2].name, "Trump");
    users[2].borrowedBooksCount = 0;

    int option;

    do {
        option = menu();
        if (option == 1) addBook();
        else if (option == 2) deleteBook();
        else if (option == 3) searchBookByTitle();
        else if (option == 4) searchBookByAuthor();
        else if (option == 5) checkOutBook();
        else if (option == 6) returnBook();
        else if (option == 7) listBooks();
        else if (option == 8) listBorrowedBooks();
        else if (option == 9) break;
    }while(1);

  }

int menu() {
    int option;
    printf("----------------------------\n"
           "  Library Management System\n"
           "----------------------------\n"
           "1. Add New Book\n"
           "2. Delete Book\n"
           "3. Search Book by Title\n"
           "4. Search Book by Author\n"
           "5. Check out Book (to a user)\n"
           "6. Return Book (from a user)\n"
           "7. List All Books\n"
           "8. List Borrowed Books of User\n"
           "0. Exit\n"
           "----------------------------\n\n"
           "Enter your choice : ");
    scanf("%d", &option);
    return option;
}

void addBook() {
    if (bookCount == 100) {
        printf("Too many books! Cannot add another.\n");
        return;
    }
    printf("Enter book ID: ");
    scanf("%d", &books[bookCount].bookID);
    printf("Enter title (Do not use spaces): ");
    scanf("%s", books[bookCount].title);
    printf("Enter author (Do not use spaces): ");
    scanf("%s", books[bookCount].author);
    printf("Enter year published: ");
    scanf("%d", &books[bookCount].yearPublished);
    books[bookCount].isAvailable = 1;
    printf("Book '%s' added successfully.\n\n", books[bookCount].title);

    bookCount++;
}

void deleteBook() {
    int bookIDtoDelete;
    if (bookCount == 0) {
        printf("There is no books in this system.\n");
        return;
    }
    printf("Enter book ID to delete: ");
    scanf("%d", &bookIDtoDelete);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookID == bookIDtoDelete) {
            printf(
                   "Book ID: %d\n"
                   "Book title: %s\n"
                   "Author: %s\n"
                   "Year published: %d\n"
                   "Are you sure you want to delete the book (Y/n)?\n", bookIDtoDelete, books[i].title, books[i].author, books[i].yearPublished);
            char option;
            scanf(" %c", &option);
            if (option == 'n') {
                return;
            }
            else if (option == 'Y') {
                for (int j = i; j < bookCount; j++) {
                    books[j] = books[j + 1];
                }
                printf("Book succesfully deleted.\n");
                bookCount--;
                return;
            }
            else {
                printf("Invalid option.\n");
                return;
            }
        }
    }
    printf("There is no books with that ID in this system.\n");
}

void listBooks() {
    if (bookCount == 0) {
        printf("There is no books in this system.\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        printf("**** - Book %d - ******************\n"
               "Book ID: %d\n"
               "Book title: %s\n"
               "Author: %s\n"
               "Year published: %d\n", i+1, books[i].bookID, books[i].title, books[i].author, books[i].yearPublished);
        if (books[i].isAvailable == 1) printf("Book available\n\n");
        else printf("Book not available\n\n");
    }
    printf("All books listed.\n");
}

int searchBookByTitle() {
    if (bookCount == 0) {
        printf("There is no books in this system.\n");
        return -1;
    }

    char titleToSearch[100];
    printf("Enter title to search (Do not use spaces): ");
    scanf("%s", titleToSearch);
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(titleToSearch, books[i].title) == 0) {
            printf("Book ID: %d\n"
                   "Book title: %s\n"
                   "Author: %s\n"
                   "Year published: %d\n", books[i].bookID, books[i].title, books[i].author, books[i].yearPublished);
            if (books[i].isAvailable == 1) printf("Book available\n\n");
            else printf("Book not available\n\n");
            return i;
        }
    }
    printf("There is no books with that title in system.\n");
    return -1;
}

//This function display just first book in the list by an author.
int searchBookByAuthor() {
    if (bookCount == 0) {
        printf("There is no books in this system.\n");
        return -1;
    }
    char authorToSearch[100];
    printf("Enter author to search (Do not use spaces): ");
    scanf("%s", authorToSearch);
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(authorToSearch, books[i].author) == 0) {
            printf("Book ID: %d\n"
                   "Book title: %s\n"
                   "Author: %s\n"
                   "Year published: %d\n", books[i].bookID, books[i].title, books[i].author, books[i].yearPublished);
            if (books[i].isAvailable == 1) printf("Book available\n\n");
            else printf("Book not available\n\n");
            return i;
        }
    }
    printf("There is no books with that author in system.\n");
    return -1;

}

void checkOutBook() {
    int bookIDtoCheckOut;
    int userIDtoCheckOut;
    if (bookCount == 0) {
        printf("There is no books in this system.\n");
        return;
    }
    printf("Enter book ID to check out: ");
    scanf("%d", &bookIDtoCheckOut);
    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookID == bookIDtoCheckOut) {
            printf("Book ID: %d\n"
                "Book title: %s\n"
                "Author: %s\n"
                "Year published: %d\n\n", books[i].bookID, books[i].title, books[i].author, books[i].yearPublished);
            if (books[i].isAvailable == 1) {
                printf("Enter a user ID to check out: ");
                scanf("%d", &userIDtoCheckOut);
                if(users[userIDtoCheckOut].borrowedBooksCount >= 10) {
                    printf("This user cannot barrow another book.\n");
                    return;
                }
                else {
                    users[userIDtoCheckOut].checkedOutBooks[users[userIDtoCheckOut].borrowedBooksCount] = bookIDtoCheckOut;
                    users[userIDtoCheckOut].borrowedBooksCount++;
                    books[i].isAvailable = 0;
                    printf("Book borrowed to %s\n\n", users[0].name);
                    return;
                }
            }
            else printf("Book not available.\n");
            return;
        }
    }
    printf("There is no books with that title in this system.\n");
}

void returnBook() {
    if (bookCount == 0) {
        printf("There is no books in this system.\n");
        return;
    }
    int userIDtoReturn;
    int bookIDtoReturn;
    printf("Enter user ID to return: ");
    scanf("%d", &userIDtoReturn);
    if (users[userIDtoReturn].borrowedBooksCount == 0) {
        printf("This user do not have a borrowed book.\n");
        return;
    }
    printf("List of book(s) borrowed from %s:\n", users[0].name);
    for (int i = 0; i < users[userIDtoReturn].borrowedBooksCount; i++){
        printf("    -Book ID: %d\n", users[userIDtoReturn].checkedOutBooks[i]);
    }
    printf("Enter bookID to return: ");
    scanf("%d", &bookIDtoReturn);
    for (int i = 0; i < users[userIDtoReturn].borrowedBooksCount; i++) {
        if (books[i].bookID == bookIDtoReturn) {
            books[i].isAvailable = 1;
            users[userIDtoReturn].borrowedBooksCount--;
            printf("Book set as returned.");
            return;
        }
    }
}

void listBorrowedBooks() {
    if (bookCount == 0) {
        printf("There is no books in this system.\n");
        return;
    }
    int userIDtoSearch;
    printf("Enter user ID to list borrowed books by user: ");
    scanf("%d", &userIDtoSearch);
    if (users[userIDtoSearch].borrowedBooksCount == 0) {
        printf("This user do not have a borrowed book.\n");
        return;
    }
    printf("List of book(s) borrowed from %s:\n", users[0].name);
    for (int i = 0; i < users[userIDtoSearch].borrowedBooksCount; i++){
        printf("    -Book ID: %d\n", users[userIDtoSearch].checkedOutBooks[i]);
    }
}