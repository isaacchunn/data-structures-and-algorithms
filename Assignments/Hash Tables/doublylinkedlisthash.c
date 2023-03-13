#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 3

typedef struct _listnode{
    int key;
    struct _listnode *next;
    struct _listnode *pre;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} HashTableNode;

typedef struct _hashTable{
   int hSize;
   int nSize;
   HashTableNode *Table;
} HashTable;

int Hash(int key,int hSize);

ListNode* HashSearch(HashTable, int);
int HashInsert(HashTable *, int);
int HashDelete(HashTable *, int);

//In Practice, we will not do it
void HashPrint(HashTable);

int main()
{
    int opt;
    int size;

    int i;
    int key;

    //Create a HashTable
    HashTable Q1;

    printf("============= Hash Table ============\n");
    printf("|1. Create a hash table             |\n");
    printf("|2. Insert a key to the hash table  |\n");
    printf("|3. Search a key in the hash table  |\n");
    printf("|4. Delete a key from the hash table|\n");
    printf("|5. Print the hash table            |\n");
    printf("|6. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=5){
        switch(opt){
        case 1:
            printf("Enter number of data to be inserted:\n");
            scanf("%d",&size);

            Q1.hSize = (int)size/ LOAD_FACTOR;
            Q1.nSize = 0;

            Q1.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q1.hSize));

            for(i=0;i<Q1.hSize;i++){
                Q1.Table[i].head = NULL;
                Q1.Table[i].size = 0;
            }
            printf("HashTable is created.\n");
            break;
        case 2: //Insertion
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            if(HashInsert(&Q1,key))
                printf("%d is inserted.\n",key);
            else
                printf("%d is a duplicate. No key is inserted.\n",key);
            break;
        case 3: //Search
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            ListNode* node = HashSearch(Q1, key);

            if(node!=NULL)
                printf("%d is found.\n",key);
            else
                printf("%d is not found.\n",key);
            break;
        case 4: //Deletion
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            if(HashDelete(&Q1,key))
                printf("%d is deleted.\n",key);
            else
                printf("%d is not existing.\n",key);
            break;
        case 5:
            HashPrint(Q1);
            break;
        }

    printf("Enter selection: ");
    scanf("%d",&opt);
    }

    for(i=0;i<Q1.hSize;i++)
    {
        while(Q1.Table[i].head)
        {
            ListNode *temp;
            temp = Q1.Table[i].head;
            Q1.Table[i].head = Q1.Table[i].head->next;
            free(temp);
        }
    }
    free(Q1.Table);

    return 0;
}


/// @brief Attempts to insert a key into the hash table
/// @param Q1Ptr Pointer to hash table
/// @param key key to insert in hash table
/// @return 1 if successful, 0 if not successful
int HashInsert(HashTable* Q1Ptr, int key)
{
    //Declare some variables
    int hashIndex;
    ListNode * newNode;

    //Check if the size of table is 0
    if(Q1Ptr == NULL || Q1Ptr->hSize == 0)
        return 0;
    
    //Then use our hash function to check for a duplicate
    if(HashSearch(*Q1Ptr,key) != NULL)
        return 0;

    //Then there is no duplicate, so we can insert it at the front easily
    //Update hash index
    hashIndex = Hash(key, Q1Ptr->hSize);
    //Make a new node
    newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->key = key;
    //Insert the node created in a double linked list fashion
    //Set node's next to be the current head
    newNode->next = Q1Ptr->Table[hashIndex].head;
    //Set the prev of it's head to be newNode if the head is not NULL.
    if(Q1Ptr->Table[hashIndex].head != NULL)
        Q1Ptr->Table[hashIndex].head->pre = newNode;
    //Then set the head as the node, and set the node prev to be NULL
    Q1Ptr->Table[hashIndex].head = newNode;
    newNode->pre = NULL;
    return 1;
}

/// @brief Deletes a node from the hash table
/// @param Q1Ptr pointer to hash table
/// @param key key to delete
/// @return 1 if successful, 0 if unsuccessful 
int HashDelete(HashTable* Q1Ptr, int key)
{
    //Declare some variables
    int hashIndex;
    ListNode * curr, *temp;

    //Check if the size of table is 0
    if(Q1Ptr == NULL || Q1Ptr->hSize == 0)
        return 0;

    //Use the hash search to find the exact node
    curr = HashSearch(*Q1Ptr, key);
    //If no such node exists, we dont need to delete anything.
    if(curr == NULL)
        return 0;

    //Update hash index
    hashIndex = Hash(key, Q1Ptr->hSize);
    //This means curr is head as there is no previous node
    if(curr->pre == NULL)
    {
        //Set the head to be the next node
        Q1Ptr->Table[hashIndex].head = curr->next;
    }
    else
    {
        //Else we are either in the middle of the LL or at the back, but there will exist a prev
        //set the prev node next to be curr next, it does not matter if curr next is NULl
        curr->pre->next = curr->next;
    }
    //Then update the node of the next node if its not NULL
    if(curr->next != NULL)
    {
        //Then update next prev
        curr->next->pre = curr->pre;
    }
    //Then free curr
    free(curr);
    return 1;
}

int Hash(int key,int hSize)
{
    return key%hSize;
}

ListNode* HashSearch(HashTable Q1, int key)
{
    int index;

    ListNode *temp;

    if(Q1.hSize != 0)
      index = Hash(key,Q1.hSize);
    else
      return NULL;

    temp = Q1.Table[index].head;
    while(temp !=NULL){
        if(temp->key == key)
            return temp;
        temp = temp->next;
    }

    return NULL;
}

void HashPrint(HashTable Q1)
{
    int i;
    ListNode *temp;
    for(i=0;i<Q1.hSize;i++)
    {
        temp =Q1.Table[i].head;
        printf("%d:  ",i);
        while(temp !=NULL)
        {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}