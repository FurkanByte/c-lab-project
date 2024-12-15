//
// Created by Furkan on 15.12.2024.
// This file created for EENG212 Lab Project
// Library Management System with Structers and Arrays
//

#include <stdio.h>
#include <stdlib.h>

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
    int option;

    do {
        option = menu();
        if (option == 1) addBook();
        //else if (option == 2) deleteBook();
        //else if (option == 3) searchBookByTitle();
        //else if (option == 4) searchBookByAuthor();
        //else if (option == 5) checkOutBook();
        //else if (option == 6) returnBook();
        //else if (option == 7) listBooks();
        //else if (option == 8) listBorrowedBooks();
        //else if (option == 9) break;
    }while(1);

  }

int menu() {
    int option;
    printf("----------------------------\n"
           "  Library Managment System\n"
           "----------------------------\n"
           "1. Add New Book\n"
           "2. Delete Book\n"
           "3. Search Book by Title\n"
           "4. Search Book by Author\n"
           "5. Check out Book (to a user)\n"
           "6. Return Book (from a user)\n"
           "7. List All Books\n"
           "8. List Borrowes Books of User\n"
           "0. Exit\n"
           "----------------------------\n\n"
           "Enter your choice : ");
    scanf("%d", &option);
    return option;
}

void addBook() {
    if (bookCount == 99) {
        printf("Too many books! Cannot add another.\n");
        return;
    }
    printf("Enter book ID: ");
    scanf("%d", &books[bookCount].bookID);
    printf("Enter title: ");
    scanf("%s", books[bookCount].title);
    printf("Enter author: ");
    scanf("%s", books[bookCount].author);
    printf("Enter year published: ");
    scanf("%d", &books[bookCount].yearPublished);
    books[bookCount].isAvailable = 1;
    printf("Book '%s' added successfully.\n\n", books[bookCount].title);

    bookCount++;
}