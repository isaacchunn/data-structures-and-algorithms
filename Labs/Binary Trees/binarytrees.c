////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////


typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;

} BTNode;

////////////////////////////////////////////////////////////////////


void mirrorTree(BTNode *node);

void printSmallerValues(BTNode *node, int m);
int smallestValue(BTNode *node);
int hasGreatGrandchild(BTNode *node);

void printTree_InOrder(BTNode *node);
void printTree_PostOrder(BTNode * node);

////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]){

    int i;
    BTNode *root, *root2;
    BTNode btn[15];

    // Create the tree in Q1
    // Using manual dynamic allocation of memory for BTNodes

    root = malloc(sizeof(BTNode));
    root->item = 4;

    root->left = malloc(sizeof(BTNode));
    root->left->item = 5;

    root->right = malloc(sizeof(BTNode));
    root->right->item = 2;

    root->left->left = NULL;

    root->left->right = malloc(sizeof(BTNode));
    root->left->right->item = 6;

    root->left->right->left = NULL;
    root->left->right->right = NULL;

    root->right->left = malloc(sizeof(BTNode));
    root->right->left->item = 3;

    root->right->right = malloc(sizeof(BTNode));
    root->right->right->item = 1;

    root->right->left->left = NULL;

    root->right->left->right = NULL;

    root->right->right->left = NULL;

    root->right->right->right = NULL;

    printTree_InOrder(root);
    printf("\n");
    mirrorTree(root);
    printTree_InOrder(root);
    printf("\n\n");

    //question 2
    printf("\ninput m for question 2: ");
    scanf("%d", &i);
    printf("the values smaller than %d are:", i);
    printSmallerValues(root, i);
    printf("\n\n");

    //question 3
    printf("The smallest value in the tree is %d:\n", smallestValue(root));

    //question 4
    // Create a tree for Q4: Tall enough so some nodes have great-grandchildren
    // Use array of BTNodes, create tree by linking nodes together
    for (i = 0; i <= 6; i++){
        btn[i].item = i;
        //Let i be 0, then the left is (0*2 +1) which is 1.
        btn[i].left = &(btn[i * 2 + 1]);
        //Let i be 0, then the right is (0*2 +2) which is 2.
        btn[i].right = &(btn[i * 2 + 2]);
        //Then it is to be said that the left and right can be calculated for all i <=6
    }
    
    

    for (i = 7; i <= 14; i++){
        btn[i].item = i;
        btn[i].left = NULL;
        btn[i].right = NULL;
    }
    root2 = &btn[0];
    

    printf("The tree for question 4 visited by in-order is \n");
    printTree_PostOrder(root2);
    printf("\nthe values stored in all nodes of the tree that have at least one great-grandchild are: ");

    hasGreatGrandchild(root2);

    return 0;
}

void mirrorTree(BTNode *node){

    // write your code here
    if(node == NULL)
        return;
    
    //We want to reverse each's node right and left from bottom to up all the way to the root node, so this is a post order traversal problem?
    //Go all the way down to it's max depth first, and then we try to swap the left and right
    mirrorTree(node->left);
    mirrorTree(node->right);
    
    //IF both the nodes are not null, we swap them from the most bottom depth
    //Swapping left and right
    BTNode* temp = node->left;
    node->left = node->right;
    node->right = temp;
}

//This means that if our height starts from -1 (the NULL nodes), we then nodes that will be comparing depth >1 will be the nodes containing the great grand childs..
//Using calculate height method in lecture nodes for each node to get the node height
int hasGreatGrandchild(BTNode *node){
    int l, r, height;
    //We have reached a level we don't want to reach...?
    if(node == NULL)
        return -1;
    //Post order traversal down to lowest depth, we will use the return as the level reached
    l = hasGreatGrandchild(node->left);
    r = hasGreatGrandchild(node->right);
    
    //Find max of depths
    height = l > r ? l : r;

    if(height > 1)
        printf("%d ", node->item);
    
    return (height+1);
    
}

void printSmallerValues(BTNode *node, int m){

    // write your code here
    //We want to do a traversal in any traversal method as we are just printing and not doing anything with the value.
    //I will use pre-order.
    
    if(node == NULL)
        return;
    
    //If current node is less than m, then print it out
    if(node->item < m)
        printf("%d ", node->item);
    
    //Then traverse all the way left and then all the way right
    printSmallerValues(node->left, m);
    printSmallerValues(node->right, m);
}

int smallestValue(BTNode *node) {
    
    //If the node is null, we want to return a very large value as we want the minimum of nodes
    if(node == NULL)
        return 999999;
    
    //Then we try conduct depth first to get the bottom nodes and propagate upwards
    int data = node->item;
    int l = smallestValue(node->left);
    int r = smallestValue(node->right);
    
    //Do some min cheecking to find minimum of three values
    if (l < data)
    {
        //If l lesser than data
        data = l;
    }
    if(r < data)
    {
        //If data still bigger than r, then the smallest is r
        data = r;
    }
    return data;
}


//////////////////////////////////////////////////////////////////

void printTree_InOrder(BTNode *node){

    if (node == NULL) return;
    printTree_InOrder(node->left);
    printf("%d, ", node->item);
    printTree_InOrder(node->right);
    return;
}


void printTree_PostOrder(BTNode * node)
{
    if(node == NULL) return;
    printTree_PostOrder(node->left);
    printTree_PostOrder(node->right);
    printf("%d, ", node->item);
}
