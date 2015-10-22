#include <stdio.h>
#include <stdlib.h>

// Basic structure of singly linked list
struct node {
	int data;
	struct node *next;
} *head;

// Append a node at the end of last node
void append(int num) {
	struct node *temp, *right;
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = num;
	right = (struct node *)head;
	while (right->next != NULL)
		right = right->next;
	right->next = temp;
	right = temp;
	right->next = NULL;
}

// Add a node at the front of the list
void add( int num ) {
	struct node *temp;
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = num;
	if (head == NULL) {
		head = temp;
		head->next = NULL;
	}
	else {
		temp->next = head;
		head = temp;
	}
}

// Add a node after a specific postion in the list
void addafter(int num, int loc) {
	int i;
	struct node *temp, *left, *right;
	right = head;
	for (i = 1; i < loc; i++) {
		left = right;
		right = right->next;
	}
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = num;
	left->next = temp;
	left = temp;
	left->next = right;
	return;
}

// Insert a new node in the list
// This method checks the position to be inserted at 
// and calls the methods appropriately

// In this case, the elements are inserted such that 
// list remains sorted

void insert(int num) {
	int c = 0;
	struct node *temp;
	temp = head;
	if (temp == NULL)
		add(num);
	else {
		while (temp != NULL) {
			if (temp->data < num)
				c++;
			temp = temp->next;
		}
		if (c == 0)
			add(num);
		else if (c < count())
			addafter(num, ++c);
		else
			append(num);
	}
}

// Delete a node from the list
int delete(int num) {
	struct node *temp, *prev;
	temp = head;
	while (temp != NULL) {
		if (temp->data == num) {
			if (temp == head) {
				head = temp->next;
				free(temp);
				return 1;
			}
			else {
				prev->next = temp->next;
				free(temp);
				return 1;
			}
		}
		else {
			prev = temp;
			temp = temp->next;
		}
	}
	return 0;
}

// Display the linked list
void  display(struct node *r) {
	r = head;
	if (r == NULL)
		return;
	while (r != NULL) {
		printf("%d ", r->data);
		r = r->next;
	}
	printf("\n");
}

// Count of nodes in the linked list
int count() {
	struct node *n;
	int c = 0;
	n = head;
	while (n != NULL) {
		n = n->next;
		c++;
	}
	return c;
}

// Main function
int  main() {
	int i, num;
	struct node *n;
	head = NULL;
	while (1) {
		printf("\nList Operations\n");
		printf("===============\n");
		printf("1.Insert\n");
		printf("2.Display\n");
		printf("3.Size\n");
		printf("4.Delete\n");
		printf("5.Exit\n");
		printf("Enter your choice : ");
		if (scanf("%d", &i) <= 0) {
			printf("Enter only an Integer\n");
			exit(0);
		} 
		else {
			switch (i) {
				case 1:
					printf("Enter the number to insert : ");
					scanf("%d", &num);
					insert(num);
					break;
				case 2:     
					if (head == NULL)
						printf("List is Empty\n");
					else
						printf("Element(s) in the list are : ");
					display(n);
					break;
				case 3:     
					printf("Size of the list is %d\n", count());
					break;
				case 4:     
					if (head == NULL)
						printf("List is Empty\n");
					else {
						printf("Enter the number to delete : ");
						scanf("%d", &num);
						if (delete(num))
							printf("%d deleted successfully\n", num);
						else
							printf("%d not found in the list\n", num);
					}
					break;
				case 5:     
					return 0;
				default:    
					printf("Invalid option\n");
			}
		}
	}
	return 0;
}