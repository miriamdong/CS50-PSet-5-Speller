// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 10000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    // make a cursor node which points to the head of the hash table
    node *cursor = table[index];
    // loop through the list until the final node is reached
    for (node *temp = cursor; temp != NULL; temp = temp->next)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hashvalue = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hashvalue += tolower(word[i]);
        hashvalue = (hashvalue * tolower(word[i])) % N;
    }
    return hashvalue;
}

int counter = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // OPEN DICTIONARY FILE and read the file.
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "cannot open file");
        return false;
    }
    
    //wordlist is a character array of the words.
    char wordlist[LENGTH + 1];
    //while fscanf != EOF print the words into the character array word
    while (fscanf(file, "%s", wordlist) != EOF)
    {
        // Keep track of the nodes being made
        counter++;
        // allocate memory for each new node
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            return 1;
        }
        // initialize the new node by copying the word to the next node
        strcpy(newNode->word, wordlist);
        newNode->next = NULL;
        // add to hash table each element of the hashtable is a linked list
        int index = hash(wordlist);
        // if the index is not yet assigned, put the newest node at the head of this index.
        if (table[index] == NULL)
        {
            table[index] = newNode;
        }
        // if the index is assigned pointing to the existing head node at the table[index]
        // then make the new node the head
        else
        {
            //makes the next the new head
            newNode->next = table[index];
            //head points to the new node.
            table[index] = newNode;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // keep track of the nodes being added
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // free each of hash table's (buckets) memory 
    // make a cursor which points to the head node
    // this cursor will work through the linked lists making each = NULL, freeing the memory
    node *tmp = NULL;
    node *cursor = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
