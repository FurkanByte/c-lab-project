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
    //Users definitions
    userNode user1;
    userNode user2;
    userNode user3;

    user1.userID = 1;
    strcpy(user1.name, "Furkan");
    user1.next = &user2;
    user1.borrowedBooks = NULL;

    user2.userID = 2;
    strcpy(user2.name, "Albert");
    user2.next = &user3;
    user2.borrowedBooks = NULL;

    user3.userID = 3;
    strcpy(user3.name, "Trump");
    user3.next = NULL;
    user3.borrowedBooks = NULL;

    bookNode *bookHead = NULL;
    userNode *userHead = &user1;

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
        else if (option == 3) {
            char titleToSearch[100];
            printf("Enter title to search: ");
            scanf("%s", titleToSearch);
            bookNode* temp = searchBookByTitle(bookHead, titleToSearch);
            if (temp != NULL) {
                printf("Book ID: %d\n", temp->bookID);
                printf("Title: %s\n", temp->title);
                printf("Author: %s\n", temp->author);
                printf("Year published: %d\n", temp->yearPublished);
            }

        }
        else if (option == 4) {
            char authorToSearch[100];
            printf("Enter author to search: ");
            scanf("%s", authorToSearch);
            bookNode* temp = searchBookByAuthor(bookHead, authorToSearch);
            if (temp != NULL) {
                printf("Book ID: %d\n", temp->bookID);
                printf("Title: %s\n", temp->title);
                printf("Author: %s\n", temp->author);
                printf("Year published: %d\n", temp->yearPublished);
            }

        }
        /*else if (option == 5) {
            int userID, bookID;
            printf("Enter user ID to borrow: ");
            scanf("%d", &userID);
            printf("Enter book ID to borrow: ");
            scanf("%d", &bookID);

            checkOutBook(userHead, userID, bookHead, bookID);
        }*/
       else if (option == 6) {
           int userID, bookID;
           printf("Enter user ID to return: ");
           scanf("%d", &userID);
           printf("Enter book ID to return: ");
           scanf("%d", &bookID);
           returnBook(userHead, userID, bookHead, userID);
       }
        else if (option == 7) listBooks(bookHead);
        else if (option == 8) {
            int userID;
            printf("Enter user ID to list borrowed books form user: ");
            scanf("%d", &userID);
            listBorrowedBooks(userHead, userID);
        }
       
        else if (option == 0) break;
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
        else printf("Book not available.\n\n");
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
    else printf("Book not found!\n\n");
}

bookNode* searchBookByTitle(bookNode* head, const char* title) {
    bookNode* temp = head;
    if (temp == NULL) {
        printf("No books in the list!\n");
        return NULL;
    }
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    printf("Book %s not found!\n", title);
    return NULL;
}

bookNode* searchBookByAuthor(bookNode* head, const char* author) {
    bookNode* temp = head;
    if (temp == NULL) {
        printf("No books in the list!\n");
        return NULL;
    }
    while (temp != NULL) {
        if (strcmp(temp->author, author) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    printf("Book %s not found!\n", author);
    return NULL;
}

void checkOutBook(userNode *userHead, int userID, bookNode *bookHead, int bookID) {
    userNode* tempUser = userHead;
    while (tempUser->userID != userID)  tempUser = tempUser->next;
    if (tempUser->userID == userID) {
        bookNode* tempBook = bookHead;
        while (tempBook->bookID != bookID) tempBook = tempBook->next;
        if (tempBook->bookID == bookID) {
            if (tempBook->isAvailable == 1) {
                tempBook->isAvailable = 0;
                if (tempUser -> borrowedBooks == NULL) {
                    tempUser -> borrowedBooks = tempBook;
                    tempUser -> borrowedBooks -> next = tempUser -> borrowedBooks;
                }
                else {
                    bookNode* tempBorrowedBooks = tempUser -> borrowedBooks;
                    while (tempBorrowedBooks->next == tempBorrowedBooks) {
                        tempBorrowedBooks = tempBorrowedBooks->next;
                    }

                }
            }
            else {
                printf("Book is not available.\n\n");
                return;
            }



        }
        else printf("UserID %d not found!\n", userID);

    }
} //Not Completed
void returnBook(userNode *userHead, int userID, bookNode *bookHead, int bookID) {
    userNode* tempUser = userHead;
    while (tempUser && tempUser->userID != userID) tempUser = tempUser->next;

    if (tempUser && tempUser->userID == userID) {
        if (tempUser->borrowedBooks == NULL) {
            printf("User has no borrowed books.\n");
            return;
        }

        bookNode* current = tempUser->borrowedBooks;
        bookNode* prev = NULL;

        do {
            if (current->bookID == bookID) {
                if (prev == NULL) { // Removing the only book in the circular list
                    if (current->next == current) {
                        tempUser->borrowedBooks = NULL;
                    } else {
                        bookNode* last = current;
                        while (last->next != current) last = last->next;
                        tempUser->borrowedBooks = current->next;
                        last->next = tempUser->borrowedBooks;
                    }
                } else {
                    prev->next = current->next;
                    if (current == tempUser->borrowedBooks) {
                        tempUser->borrowedBooks = current->next;
                    }
                }

                current->isAvailable = 1;
                printf("Book ID %d returned successfully.\n", bookID);
                return;
            }

            prev = current;
            current = current->next;
        } while (current != tempUser->borrowedBooks);

        printf("Book ID %d not found in user's borrowed books.\n", bookID);
    } else {
        printf("User ID %d not found.\n", userID);
    }
}
void listBorrowedBooks(userNode *userHead, int userID) {
    userNode* tempUser = userHead;
    while (tempUser && tempUser->userID != userID) tempUser = tempUser->next;

    if (tempUser && tempUser->userID == userID) {
        if (tempUser->borrowedBooks == NULL) {
            printf("User has no borrowed books.\n");
            return;
        }

        bookNode* current = tempUser->borrowedBooks;
        do {
            printf("Book ID: %d\n", current->bookID);
            printf("Title: %s\n", current->title);
            printf("Author: %s\n", current->author);
            printf("Year Published: %d\n\n", current->yearPublished);

            current = current->next;
        } while (current != tempUser->borrowedBooks);
    } else {
        printf("User ID %d not found.\n", userID);
    }
}
void checkOutBook(userNode *userHead, int userID, bookNode *bookHead, int bookID) {
    
    userNode* tempUser = userHead;
    while (tempUser && tempUser->userID != userID) tempUser = tempUser->next;

    if (tempUser == NULL) {
        printf("User ID %d not found.\n", userID);
        return;
    }

    
    bookNode* tempBook = bookHead;
    while (tempBook && tempBook->bookID != bookID) tempBook = tempBook->next;

    if (tempBook == NULL) {
        printf("Book ID %d not found.\n", bookID);
        return;
    }

    if (tempBook->isAvailable == 0) {
        printf("Book ID %d is not available for checkout.\n", bookID);
        return;
    }

    
    bookNode* borrowedBooks = tempUser->borrowedBooks;
    if (borrowedBooks != NULL) {
        bookNode* current = borrowedBooks;
        do {
            if (current->bookID == bookID) {
                printf("User ID %d has already borrowed Book ID %d.\n", userID, bookID);
                return;
            }
            current = current->next;
        } while (current != borrowedBooks);
    }

    
    tempBook->isAvailable = 0; 

    if (tempUser->borrowedBooks == NULL) { 
        tempUser->borrowedBooks = tempBook;
        tempBook->next = tempBook;
    } else { 
        bookNode* last = tempUser->borrowedBooks;
        while (last->next != tempUser->borrowedBooks) {
            last = last->next; 
        }
        last->next = tempBook;
        tempBook->next = tempUser->borrowedBooks; 
    }

    printf("Book ID %d has been successfully checked out to User ID %d.\n", bookID, userID);
}
