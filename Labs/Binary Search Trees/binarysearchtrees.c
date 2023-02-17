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

    //TEST CASES
    insertBSTNode(&root, 20);
    insertBSTNode(&root, 15);
    insertBSTNode(&root, 10);
    insertBSTNode(&root, 18);
    insertBSTNode(&root, 50);
    insertBSTNode(&root, 25);
    insertBSTNode(&root, 80);

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
	printf("\n");

	//question 3
	if (isBST(root,-1000000, 1000000)==1)
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

/// @brief Prints the BST in order. Also, this also prints the BST out in a sorted fashion!
/// @param node root node
void printBSTInOrder(BTNode *node)
{
	//Return if curr node is null
    if(node == NULL)
        return;

    //ELse just traverse down normally starting from left to right using in order traversal
    printBSTInOrder(node->left);  
    //Print all the left values first
    printf("%d ", node->item);
    //Then go right
    printBSTInOrder(node->right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Similar to https://leetcode.com/problems/validate-binary-search-tree/
/// @brief Checks if a binary tree satisfies the requirements of being a BST.
/// @param node Root of binary tree
/// @param min current min of node
/// @param max current max of node
/// @return 1 if BST, 0 if not BST
int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
    int l, r;
    //A BST must always follow the L<C<R rule
    //We do a post order search downwards, and then propagate upwards with the new min or maxes
    //A empty tree is a valid BST.
    if(node == NULL)
        return 1;

    //Else we need to check if the left and right subtrees are equally BSTs
    //We minus 1 as it cannot be the same value, AND it must satisfy the BST requirements.
    l = isBST(node->left, min, node->item - 1);
    //Do the same for right, making use of the current node item +1 as the min.
    r = isBST(node->right, node->item +1, max);

    //So if l and r are all valid subtrees, AND the current node value is inbetween min and max, then this node forms a subset of a valid BST
    if(l && r && min <= node->item && node->item <= max)
        return 1;
    
    //Base return 0 then its not longer a BST and it propagates upwards, the if statement above will never pass and all return 0.
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Removes a BST node from a binary tree
/// @param node root of tree
/// @param value Value to remove 
/// @return 
BTNode *removeBSTNode(BTNode *node, int value)
{
	// //Now we have to check for a few things.
    // if(node == NULL)
    // {
    //     return;
    // }

    // //Else if the current node already has the item, we can't insert as a BST is meant to have unique values!
    // if(node->item == value)
    // {
    //     printf("Can't insert %d into BST, value of %d, already exists!\n", value, value);
    //     return;
    // }

    // //Else just do normal traversals downwards left or right depending on value
    // if(value < node->item)
    //     insertBSTNode(node->left, value);
    // else
    //     insertBSTNode(&((*node->right, value);
    // return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
	// write your code here
    return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////