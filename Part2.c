//
// Created by Furkan on 15.12.2024.
// This file created for EENG212 Lab Project
// Library Management System with Linked Lists
//

#include <stdio.h>
#include <stdlib.h>

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

void addBook(bookNode **head, int bookID, const char* title, const char* author, int yearPublished);
void deleteBook(bookNode **head, int bookID);
bookNode* searchBookByTitle(bookNode* head, const char* title);
bookNode* searchBookByAuthor(bookNode* head, const char* author);
void checkOutBook(userNode *userHead, int userID, bookNode *bookHead, int bookID);
void returnBook(userNode *userHead, int userID, bookNode *bookHead, int bookID);
void listBooks(bookNode *head);
void listBorrowedBooks(userNode *userHead, int userID);

void main(){
    printf("Hello World2\n");
}