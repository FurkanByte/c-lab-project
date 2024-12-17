//
// Created by Furkan on 15.12.2024.
// This file created for EENG212 Lab Project
// Library Management System with Linked Lists
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bookNode {
    int bookID;
    char title[100];
    char author[100];
    int yearPublished;
    int isAvailable; //1 Available: 0 Not Available
    struct bookNode *next;
} bookNode;

typedef struct userNode {
    int userID;
    char name[100];
    struct userNode *next;
    bookNode* borrowedBooks;
} userNode;

int menu();
void addBook(bookNode **head, int bookID, const char* title, const char* author, int yearPublished);
void deleteBook(bookNode **head, int bookID);
bookNode* searchBookByTitle(bookNode* head, const char* title);
bookNode* searchBookByAuthor(bookNode* head, const char* author);
void checkOutBook(userNode *userHead, int userID, bookNode *bookHead, int bookID);
void returnBook(userNode *userHead, int userID, bookNode *bookHead, int bookID);
void listBooks(bookNode *head);
void listBorrowedBooks(userNode *userHead, int userID);

void main(){
    bookNode *bookHead = NULL;
    userNode *userHead = NULL;

    int option;

    do {
        option = menu();
        if (option == 1) {
            int bookID;
            char title[100];
            char author[100];
            int yearPublished;
            printf("Enter book ID: ");
            scanf("%d", &bookID);
            printf("Enter title: ");
            scanf("%s", title);
            printf("Enter author: ");
            scanf("%s", author);
            printf("Enter year published: ");
            scanf("%d", &yearPublished);
            addBook(&bookHead, bookID, title, author, yearPublished);
        }
        else if (option == 2) {
            int bookID;
            printf("Enter book ID to delete: ");
            scanf("%d", &bookID);
            deleteBook(&bookHead, bookID);
        }
        //else if (option == 3) searchBookByTitle();
        //else if (option == 4) searchBookByAuthor();
        //else if (option == 5) checkOutBook();
        //else if (option == 6) returnBook();
        else if (option == 7) listBooks(bookHead);
        //else if (option == 8) listBorrowedBooks();
        //else if (option == 0) break;
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

void addBook(bookNode **head, int bookID, const char* title, const char* author, int yearPublished) {
    bookNode* newBook = (bookNode*)malloc(sizeof(bookNode));
    newBook->bookID = bookID;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->yearPublished = yearPublished;
    newBook->isAvailable = 1;
    newBook->next = NULL;

    if (*head == NULL)  *head = newBook;
    else {
        bookNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
    printf("Book %s added successfully.\n", title);
}

void listBooks(bookNode *head) {
    bookNode* temp = head;
    if (temp == NULL) {
        printf("No books in the list\n");
        return;
    }

    int i = 0;
    while (temp != NULL) {
        printf("**** - Book %d - ******************\n"
                       "Book ID: %d\n"
                       "Book title: %s\n"
                       "Author: %s\n"
                       "Year published: %d\n", i+1, temp->bookID, temp->title, temp->author, temp->yearPublished);
        if (temp->isAvailable == 1) printf("Book available\n\n");
        else printf("Book not available\n\n");
        temp = temp->next;
        i++;
    }
    printf("\nAll books listed!\n\n");
}

void deleteBook(bookNode **head, int bookID) {
    bookNode* temp = *head;
    if (temp == NULL) {
        printf("No books in the list\n");
        return;
    }
    if (temp->bookID == bookID) {
        bookNode* hold = *head;
        *head = (*head)->next;
        free(hold);
        printf("Book deleted successfully.\n");
        return;
    } //Works if first node deleting

    while (temp->next->bookID != bookID) {
        temp = temp->next;
    }
    if (temp->next->bookID == bookID) {
        bookNode* hold = temp->next;
        temp->next = temp->next->next;
        free(hold);
        printf("Book deleted successfully.\n");
    }
    else printf("Book not found\n\n");
}