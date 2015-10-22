#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

int size;

struct node {
	int key;
	struct node *left, *right;
};
// Search
struct node* search(struct node* root, int key)
{
	if(root == NULL || root->key == key)
		return root;

	if (root->key < key)
		return search(root->right, key);

	return search(root->left, key);
}
// Create New Node
struct node *newNode(int item)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;	
}
// Insert
struct node* insert(struct node* node, int key)
{
	if(node == NULL)
		return newNode(key);
	if (key < node->key )
		node->left = insert(node->left, key);
	else if (key > node->key )
		node->right = insert(node->right, key);
	return node;
}	

void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}
struct node *minValueNode(struct node* node)
{
	struct node *current = node;
	while(current->left != NULL)
		current = current->left;
	return current;
}

struct node * deleteNode(struct node *root, int key)
{
	if (root == NULL)
		return root;
	if (key< root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else
	{
		if(root->left == NULL)
		{
			struct node *temp = root->right;
			free(root);
			return temp;
		}
		else if(root->right == NULL)
		{
			struct node *temp = root->left;
			free(root);
			return temp;
		}
	
	struct node *temp = minValueNode(root->right);
	root->key = temp->key;

	root->right = deleteNode(root->right, temp->key);
	}
	return root;
}
int main()
{
	int a[10];
	struct node *root = NULL;
	/* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
	root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);
	inorder(root);

	printf("\nDelete 20\n");
    root = deleteNode(root, 20);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);

    printf("\nDelete 30\n");
    root = deleteNode(root, 30);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);

    printf("\nDelete 50\n");
    root = deleteNode(root, 50);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);
    return 0;
}