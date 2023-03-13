#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 3

typedef struct _listnode{
    int key;
    struct _listnode *next;
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

int Hash(int,int);

ListNode* HashSearch(HashTable, int);
int HashInsert(HashTable *, int);

//In Practice, we will not do it
void HashPrint(HashTable);

int main()
{
    //Option that user will choose
    int opt;
    //Size of hash table
    int size;

    int i;
    int key;

    //Create a HashTable
    HashTable Q3Hash;
    Q3Hash.hSize = 0;
    Q3Hash.nSize = 0;
    Q3Hash.Table = NULL;

    printf("============= Hash Table ============\n");
    printf("|1. Create a hash table             |\n");
    printf("|2. Insert a key to the hash table  |\n");
    printf("|3. Search a key in the hash table  |\n");
    printf("|4. Print the hash table            |\n");
    printf("|5. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=4){
        switch(opt){
        case 1:
            printf("Enter number of data to be inserted:\n");
            scanf("%d",&size);

            //Do additional checking for wrong input
            while(size < 0)
            {
                printf("Size cannot be below 0.\n");
                printf("Enter number of data to be inserted:\n");
                scanf("%d",&size);
            }
            
            //The number of nodes are determined by load factor, e.g input 9, then 9/LOAD factor is our table size
            Q3Hash.hSize = (int)size/ LOAD_FACTOR;
            Q3Hash.nSize = 0;

            Q3Hash.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q3Hash.hSize));
            //Initialize all the linked lists base on hSize.
            for(i=0;i<Q3Hash.hSize;i++){
               Q3Hash.Table[i].head = NULL;
               Q3Hash.Table[i].size = 0;
            }
            printf("HashTable is created.\n");
            break;
        case 2: //Insertion
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);

            if(HashInsert(&Q3Hash,key))
                printf("%d is inserted.\n",key);
            else
                printf("%d is a duplicate. No key is inserted.\n",key);
            break;
        case 3: //Search
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            ListNode* node = HashSearch(Q3Hash, key);

            if(node!=NULL)
                printf("%d is found.\n",key);
            else
                printf("%d is not found.\n",key);
            break;
        case 4:
            HashPrint(Q3Hash);
            break;
        }

    printf("Enter selection: ");
    scanf("%d",&opt);
    }

    //Delete all nodes in the ll
    for(i=0;i<Q3Hash.hSize;i++)
    {
        while(Q3Hash.Table[i].head)
        {
            ListNode *temp;
            temp = Q3Hash.Table[i].head;
            Q3Hash.Table[i].head = Q3Hash.Table[i].head->next;
            free(temp);
        }
    }
    //Then free the table
    free(Q3Hash.Table);

    return 0;

}

/// @brief Hashing function that uses simple modulo.
/// @param key key to insert
/// @param hSize size of hash table
/// @return index of hash table for insertion
int Hash(int key,int hSize)
{
    return key%hSize;
}

/// @brief Searches the hash table and returns the head of that linked list if it exists.
/// @param Q3Hash hash table
/// @param key key to search
/// @return node in hash table that with key
ListNode* HashSearch(HashTable Q3Hash, int key)
{
    //Variable declaration
    int hashIndex;
    ListNode * curr;
    //Sanity check
    //Check if the size of hash table is 0
    if(Q3Hash.hSize == 0)
        return NULL;
    //Variable declaration
    hashIndex = Hash(key, Q3Hash.hSize);
    //Then set curr as the head of that node table
    curr = Q3Hash.Table[hashIndex].head;
    //While loop to get the node with key.
    while(curr!= NULL)
    {
        if(curr->key == key)
            return curr;
        curr = curr->next;
    }
    //Else no node was found
    return NULL;
}

/// @brief Inserts as key into the hash table
/// @param Q3HashPtr pointer to the hash table
/// @param key key to insert
/// @return 1 if successful insertion, 0 otherwise.
int HashInsert(HashTable* Q3HashPtr, int key)
{
    //We want to insert this key into the hash table, we must first check if such a key exists.
    ListNode * newNode;
    int hashIndex;

    //If the hash table size is 0, we can not insert at all.
    if(Q3HashPtr->hSize == 0)
        return 0;

    //We can use our hash search function to find for a duplicate. If we found a node, then theres a duplicate, so we return.
    if(HashSearch(*Q3HashPtr, key) != NULL)
        return 0;

    //Else theres no duplicate, and we can just insert at the front.
    //SInce its going to be sequential anyway, there is no difference in controlling insertion at back or front for now. 
    //Unless in the future we insert in a sorted manner, then we can use binary search in chaining?
    //Update hash index
    hashIndex = Hash(key,Q3HashPtr->hSize);
    //Make new node
    newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->key = key;
    //Set the next of this node to be head
    newNode->next = Q3HashPtr->Table[hashIndex].head;
    Q3HashPtr->Table[hashIndex].head = newNode;
    //Update size
    Q3HashPtr->Table[hashIndex].size++;
    //Increment nSize
    Q3HashPtr->nSize++;
    return 1;
}

void HashPrint(HashTable Q3Hash)
{
    int i;
    ListNode *temp;
    //For each slot in the hash table
    for(i=0;i<Q3Hash.hSize;i++)
    {
        //Set a temp to be head of of this slot
        temp =Q3Hash.Table[i].head;
        //First element
        printf("%d:  ",i);
        //Traverse and print
        while(temp !=NULL)
        {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}
