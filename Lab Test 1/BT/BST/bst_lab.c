//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

typedef struct _btnode{
int item;
struct _btnode *left;
struct _btnode *right;
} BTNode;

///////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);
BTNode *removeBSTNode(BTNode *node, int value);
BTNode *findMin(BTNode *p);

///////////////////////////////////////////////////////////////////////

int main(){
	int i=0;

	BTNode *root=NULL;

	//question 1
	do{
		printf("input a value you want to insert(-1 to quit):");

		scanf("%d",&i);
		if (i!=-1)
			insertBSTNode(&root,i);
	}while(i!=-1);

	//question 2
	printf("\n");
	printBSTInOrder(root);

	//question 3
	if ( isBST(root,-1000000, 1000000)==1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");

	//question 4
	do{
		printf("\ninput a value you want to remove(-1 to quit):");
		scanf("%d",&i);
		if (i!=-1)
		{
			root=removeBSTNode(root,i);
			printBSTInOrder(root);
		}
	}while(i!=-1);


	return 0;
}

//////////////////////////////////////////////////////////////////////

/// @brief Attempts to insert a node in the BST
/// @param node root of BST
/// @param value value to insert
void insertBSTNode(BTNode **node, int value)
{
    BTNode * newNode;
	//Now we have to check for a few things.
    //1. If the current node is NULL, it either means we did not find the value, OR the tree is empty.
    //So, we would malloc a node and insert it regardless!
    if(*node == NULL)
    {
        //Make a new node
        newNode = malloc(sizeof(BTNode));
        //Then, initialize it's left and right and value.
        newNode->item = value;
        newNode->left = NULL;
        newNode->right = NULL;
        //Then update the root or newly created node to be this node
        *node = newNode;
        return;
    }

    //Else if the current node already has the item, we can't insert as a BST is meant to have unique values!
    if((*node)->item == value)
    {
        printf("Can't insert %d into BST, value of %d, already exists!\n", value, value);
        return;
    }

    //Else just do normal traversals downwards left or right depending on value
    if(value < (*node)->item)
        insertBSTNode(&((*node)->left), value);
    else
        insertBSTNode(&((*node)->right), value);
}

//////////////////////////////////////////////////////////////////////

/// @brief Prints a BST in order
/// @param node headof BT
void printBSTInOrder(BTNode *node)
{
    //Base case
    if(node == NULL)
        return;

    printBSTInOrder(node->left);
    printf("%d ", node->item);
    printBSTInOrder(node->right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Determines if the BT is a BST
/// @param node head of binary tree
/// @param min min node
/// @param max max node
/// @return 1 if the BT is a BST, 0 otherwise
int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
    int l,r;
	//Check if it's a BST
    if(node == NULL)
        return 1;

    //Check for boundaries
    if(min < node->item && node->item < max)
    {
        l = isBST(node->left, min, node->item);
        r = isBST(node->right, node->item, max);

        return l && r;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *removeBSTNode(BTNode *node, int value)
{
	// write your code here
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
	// write your code here
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////