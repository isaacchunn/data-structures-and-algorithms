#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 5
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
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
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

/// @brief Hash function 1 for double hashing
/// @param key key
/// @return hashed key
int hash1(int key)
{
    return (key % TABLESIZE);
}

/// @brief Hash function 2 for double hashing
/// @param key key
/// @return hashed key
int hash2(int key)
{
    return (key % PRIME) + 1;
}

/// @brief Attempts to insert a key into the hash table
/// @param key key to insert
/// @param hashTable hash table
/// @return number of key comparisons done during insertion, -1 if duplicate key, > TABLESIZE if table is full
int HashInsert(int key, HashSlot hashTable[])
{    
   //In this case, double hashing is as follows:
    //hash1(k) + j hash2(k), where j is iterative as long as there is a collision, where it starts at 0.
    int i = 0;
    int hashIndex;
    int probe = hash1(key);
    int step = hash2(key);
    int comparisons = 0;
    int insertionIndex = -1;
    //Starting from 0, we try to hash it and find until table size
    for (i = 0; i < TABLESIZE; i++)
    {
        hashIndex = (probe + i * step) % TABLESIZE;
        //If we encounter a deleted, this is the earliest index we can insert into the hash table, but we should still search the rest and see if such key exists.
        if(hashTable[hashIndex].indicator == DELETED && insertionIndex == -1)
            insertionIndex = hashIndex;

        //If we hit an empty, it means there is no such occurence of a key and we have reached the very very last index
        if(hashTable[hashIndex].indicator == EMPTY)
        {
            //We check if there was no earlier index saved, if no, we set the index to be our current index and insert in, returning the comparisons.
            if(insertionIndex == -1)
                insertionIndex = hashIndex;
            //Then we can insert data here and then return i
            hashTable[insertionIndex].key = key;
            hashTable[insertionIndex].indicator = USED;
            return comparisons;
        }
        //As long as it is used, we have already done one comparison and we must increment
        if(hashTable[hashIndex].indicator == USED)
        {   
            comparisons++;
            //However, if at this hash index, the key already exists, then we must return -1 as there is a duplicate.
            //But, there was still 1 comparison being done.
            if(hashTable[hashIndex].key == key)
                return -1;
        }   
    }
    //If we reached here, we went full circle around the hash map, and there are no empty slots, only deleted.
    //So we can just insert at our previously stored "FIRST" deleted index.
    if(insertionIndex != -1)
    {
        hashTable[insertionIndex].key = key;
        hashTable[insertionIndex].indicator = USED;
    }
    return comparisons;
}

/// @brief Attempts to delete a key in the hash table
/// @param key key to delete
/// @param hashTable hash table
/// @return number of key comparisons done during deletion
int HashDelete(int key, HashSlot hashTable[])
{
    int i = 0;
    int hashIndex;
    int probe = hash1(key);
    int step = hash2(key);
    int comparisons = 0;
    
    //Starting from 0, we try to hash it and find until table size
    for (i = 0; i < TABLESIZE; i++)
    {
        hashIndex = (probe + i * step) % TABLESIZE;
        //If the current entry has already been deleted
        if(hashTable[hashIndex].indicator == DELETED)
        {
            //Small optimization, to check if a deleted item key was previously here, but does not count to key comparisons.
            if(hashTable[hashIndex].key == key)
                return -1;
            continue;   
        }
        //We can stop when our current hash index is empty
        //There is no further point to continue checking as it would have added to this place if it could. No key comparisons was done.
        if(hashTable[hashIndex].indicator == EMPTY)
            return -1;

        //The index here is USED, so we have to compare it regardless.
        //Increment comparisons
        comparisons++;
        //Else it is used, then we check if it is the key.
        if(hashTable[hashIndex].key == key)
        {            
            //Update the tag
            hashTable[hashIndex].indicator = DELETED;
            //Return the amount of key comparisons
            return comparisons;
        }
    }
    //After the loop, then the key must not exist.
    return -1;
}