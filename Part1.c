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

void main(){
    int option;
    do {
        option = menu();
        //if (option == 1) addBook();
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
    printf("Library Managment System\n");
    printf("--------------------------\n");
    printf("1. Add New Book\n");
    printf("2. Delete Book\n");
    printf("3. Search Book by Title\n");
    printf("4. Search Book by Author\n");
    printf("5. Check out Book (to a user)\n");
    printf("6. Return Book (from a user)\n");
    printf("7. List All Books\n");
    printf("8. List Borrowed Books of User\n");
    printf("0. Exit\n");
    printf("Enter your option: ");
    scanf("%d", &option);
    return option;
}