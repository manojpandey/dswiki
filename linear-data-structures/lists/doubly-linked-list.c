#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int id;
    char name[20];
    struct node* right;
    struct node* left;
};

struct node* start = NULL;
int val, choice;
char str[20];

void addFront(int ele, char *p) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("\nOverflow");

    }
    else {
        if (start == NULL) {
            newNode->id = ele;
            strcpy(newNode->name , p);
            newNode->left = NULL;
            newNode->right = NULL;
            start = newNode;
        }
        else
        {
            newNode->id = ele;
            strcpy(newNode->name , p);
            newNode->right = start;
            start->left = newNode;
            newNode->left = NULL;
        }
    }
}

void delEnd() {
    if (start == NULL) {

        printf("\nUnderflow");
    }
    else {
        struct node* temp = start;
        start = start->left;
        start->right = NULL;
        free(temp);

    }
}

void traversal() {
    struct node* temp = start;
    while (temp != NULL) {
        printf("\nID:%d \nNAME: %s", temp->id, temp->name);
        temp = temp->left;
    }
}

int main() {

    printf("\t\t\tDOUBLY LINKED LIST");
    printf("\nEnter 1 to insert \nEnter 2 to delete \nEnter 3 to traverse \nEnter 4 to exit");
    scanf("%d", &choice);

    while (choice != 4) {
        switch (choice) {
            case 1:
                printf("\nEnter Employee Id:");
                scanf("%d", &val);
                fflush(stdin);
                printf("\nEnter name of employee:");

                gets(str);
                puts(str);
                addFront(val, str);
                break;

            case 2:
                delEnd();
                break;
            case 3:
                traversal();
                break;
            default:
                printf("\nIncorrect Input");

        }
        printf("\nEnter 1 to insert \nEnter 2 to delete \nEnter 3 to traverse \nEnter 4 to exit");
        scanf("%d", &choice);
    }
    return 0;
}