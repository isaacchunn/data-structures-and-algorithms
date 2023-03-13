#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

//Defines a slot in the hash table.
typedef struct _slot{
    int key;                  //key in hash table
    enum Marker indicator;      //indication of whether it is empty or used  
    int next;                 //linear probing to linkto next index
} HashSlot;

//Functions to implement
int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

//Hash function
int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    //Initialization of values
    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

/// @brief Attempts to insert key into the hash table
/// @param key  key to insert
/// @param hashTable hash table
/// @return index of slot where key is inserted, -1 if inserting duplicate key, > TABLESIZE if full.
int HashInsert(int key, HashSlot hashTable[])
{   
    //Loop through all the keys iteratively to find if we can insert
    int i;
    //Store the hash index of the original key
    int hashIndex = hash(key);
    //Store the temp index of the original key
    int tempIndex = hash(key);
    int lastIndex = hashIndex;
    //The temp key
    int tempKey = key;
    //Check for duplicate keys
    for (i = 0; i < TABLESIZE; i++)
    {
        if(hashTable[i].key == key)
            return -1;
    }
    //No existing duplicate key.
    //Check that we can insert at this index
    if(hashTable[hashIndex].indicator == EMPTY)
    {
        //Then we update the key here
        hashTable[hashIndex].key = key;
        hashTable[hashIndex].indicator = USED;
        return hashIndex;
    }

    //Get up to prev
    while(hashTable[lastIndex].next != -1)
    {
        lastIndex = hashTable[lastIndex].next;
    }
    //Else, we have encountered a collision and was unable to add it in
    //So we check up to n counts using linear probing
    for (i = 0; i < TABLESIZE; i++)
    {
        //If at this index, it is not used
        if(hashTable[tempIndex].indicator == EMPTY)
        {
            //We do an insertion here 
            hashTable[tempIndex].key = key;
            hashTable[tempIndex].indicator = USED;    
            //Update the next at the index of hashIndex
            hashTable[lastIndex].next = tempIndex;
        
            //printf("Temp index: %d | HashIndex: %d\n", tempIndex, hashIndex);
            //Then return tempIndex
            return tempIndex;
        }
        tempIndex = hash(++tempKey);
    }

    //Else we check through all and the table is empty
    return TABLESIZE;
}

/// @brief Attempts to find a key in the hash table
/// @param key key to find
/// @param hashTable hash table
/// @return index of slot where key is, -1 if non existing key
int HashFind(int key, HashSlot hashTable[])
{
    //The hash table has already been initialized.
    int hashIndex = hash(key);
    //A counter to prevent infinite loop
    int i = 0;
 
    //Else we can do this loop, but making sure we account for worst case of n checks
    for (i = 0; i < TABLESIZE && hashIndex != -1; i++)
    {  
        //Then we access the hash table at this index to find if its indicator is empty (non-existing key)
        if(hashTable[hashIndex].indicator == EMPTY)
        {
            return -1;
        }
        else if(hashTable[hashIndex].key == key)
        {       
             //IF it is not here, we check until we find or next is -1
            return hashIndex;
        }
        //Else we can keep going next and continuie loop
        hashIndex = hashTable[hashIndex].next;
    }
    //Default -1 means cannot find after all efforts.
    return -1;
}