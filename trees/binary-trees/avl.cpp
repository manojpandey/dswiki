#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

int size;

struct node {
	int key, height;
	struct node *left, *right;
};

//height of tree
int height(struct node* N)
{
	if(N == NULL)
		return 0;
	return N->height;
}
int max(int a, int b)
{
	return (a>b)?a:b;
}
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
	temp->height = 1;
	return temp;	
}

struct node* rightRotate(struct node* y)
{
	struct node* x = y->left;
	struct node* T2 = x->right;
	//Perform rotation
	x->right = y;
	y->left = T2;

	//Update heights
	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;

	return x;
}
struct node* leftRotate(struct node* x)
{
	struct node* y = x->right;
	struct node* T2 = y->left;
	//Perform rotation
	y->left = x;
	x->right = T2;

	//Update heights
	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;

	return y;
}
int getBalance(struct node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
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
	node->height = max(height(node->left), height(node->right))+1;
	int balance  = getBalance(node);

	//LL
	if(balance > 1 && key < node->left->key)
		return rightRotate(node);
	//RR
	if(balance < -1 && key > node->right->key)
		return leftRotate(node);
	//LR
	if(balance > 1 && key > node->left->key)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
	//RL
	if(balance < -1 && key < node->right->key)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
	
	return node;
}	
struct node *minValueNode(struct node* node)
{
	struct node *current = node;
	while(current->left != NULL)
		current = current->left;
	return current;
}

void preOrder(struct node *root)
{
	if(root != NULL)
	{
		cout<< root->key<< " ";
		preOrder(root->left);
		preOrder(root->right);
	}
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
		if(root->left == NULL || root->right == NULL)
		{
			struct node *temp = root->left ? root->left : root->right;
		if(temp == NULL)
		{
			temp = root;
			root = NULL;	
		}
		else
			*root = *temp;
		free(temp);
		}
		else
		{
		struct node *temp = minValueNode(root->right);
		root->key = temp->key;

		root->right = deleteNode(root->right, temp->key);
	}
}
	if(root == NULL)
		return root;
	root->height = max(height(root->left), height(root->right))+1;
	int balance  = getBalance(root);

	//LL
	if(balance > 1 && getBalance(root->left) >=0)
		return rightRotate(root);
	//RR
	if(balance < -1 && getBalance(root->right) <=0)
		return leftRotate(root);
	//LR
	if(balance > 1 && getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	//RL
	if(balance < -1 && getBalance(root->right) >0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	
	return root;
}	

int main()
{
  struct node *root = NULL;
 
  /* Constructing tree given in the above figure */
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);
 
    /* The constructed AVL Tree would be
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6
    */
 
    printf("Pre order traversal of the constructed AVL tree is \n");
    preOrder(root);
 
    root = deleteNode(root, 10);
 
    /* The AVL Tree after deletion of 10
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */
 
    printf("\nPre order traversal after deletion of 10 \n");
    preOrder(root);
 
  return 0;
}