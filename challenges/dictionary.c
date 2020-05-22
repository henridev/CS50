// Implements a dictionary's functionality
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"


// one node in the hashtable
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = (26*26); // Number of buckets in hash table
node *table[N]; // Hash table
int wordCount = 0; // words in dictionary


// helper functions
bool insert(node *n, unsigned int hashcode);
bool search(const char *word);


bool check(const char *word)
{
    return search(word);
}


/*
 * A case-insensitive implementation of the djb2 hash function.
 * Change NUM_BUCKETS to whatever your number of buckets is.
 * http://stackoverflow.com/questions/2571683/djb2-hash-function.
*/
unsigned int hash(const char *word)
{
     unsigned long hash = 5381;
     for (const char *ptr = word; *ptr != '\0'; ptr++)
     {
         hash = ((hash << 5) + hash) + tolower(*ptr);
     }
     return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    unsigned int hashcode;
    FILE *fptr;
    char buffer[LENGTH + 1];

    fptr = fopen(dictionary, "r");
    if(fptr == NULL)
    {
        printf("error opening up dictionary");
        return false;
    }

    /* insert new words into the LL of hashtable via hashcodes */
    while (fscanf(fptr, "%s", buffer) != EOF)
    {
        hashcode = hash(buffer);
        node *n = (node*) malloc(sizeof(node));

        if(n == NULL)
        {
          printf("failed allocating memory for node \n");
          return false;
        }

        strncpy(n -> word, buffer, sizeof(buffer));
        n -> next = NULL;
        wordCount++;

        bool inserted = insert(n, hashcode);
        if(inserted == false)
        return false;
    }
    fclose(fptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // printf("total wordcount %i \n", wordCount);
    return wordCount;
}


/*
    Unloads dictionary from memory, returning true if successful else false
*/
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *cursor;
        node *tmp;
        cursor = table[i];
        while(cursor -> next != NULL)
        {
            tmp = cursor;

            cursor = cursor -> next;

            free(tmp);
        }

    }
    return true;
}



bool insert(node *n, unsigned int hashcode)
{
    if (table[hashcode] == NULL)
        table[hashcode] = n;
    else
    {
        node *tmp;
        tmp = table[hashcode]; // set tmp equal to head of LL
        table[hashcode] = n; // insert new node on start of LL
        n -> next = tmp; // make pointer of new start to old start
    }

    return true;
}


/*
 1. find hashcode of word
 2. go to LL at the hashcode
 3. travers LL to look for case insensitive match
 in: word to check
 out: Returns true if word is in dictionary else false
*/
bool search(const char *word)
{
    unsigned int hashcode;
    hashcode = hash(word); // 1
    node *tmp;
    tmp = table[hashcode]; // 2

    while(tmp -> next != NULL)
    {
      tmp = tmp -> next;
    //   printf("compare word dict %s with text word %s \n", tmp -> word, word);
      int match;
      match = strcasecmp(tmp -> word, word);
      if(match == 0) // 3
      {
          return true;
      }
    }
    return false;
}