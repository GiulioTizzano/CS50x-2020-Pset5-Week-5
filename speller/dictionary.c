// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//assign variables
int word_count = 0;

// Number of buckets in hash table
const unsigned int N = 27;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    // initialise lower case word
    char lc_word[LENGTH + 1];

    //lowercase each letter in word[i], where i reaches the limit length 
    for (int i = 0; i < LENGTH + 1; i++)
    {
        lc_word[i] = tolower(word[i]);
    }
    
    node *cursor = table[hash(lc_word)];

    //return true if word is found in dictionary
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number, source:
// https://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
unsigned int hash(const char *word)
{
    unsigned int hash = 0;

    while (*word)
    {
        hash = hash * 101 + *word++;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];

    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }
    
    //loop until end of file, create node and order linked list 
    while (fscanf(dict, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        
        strcpy(n -> word, word);
        n -> next = NULL;

        int hashed_n = hash(word);

        if (table[hashed_n] == NULL)
        {
            table[hashed_n] = n;
            n -> next = NULL;
        }
        else
        {
            n -> next = table[hashed_n];
            table[hashed_n] = n;
        }
        word_count++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        //initiate a cursor and point it at the linked list in position 'i'
        node *cursor = table[i];
        
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor -> next;
            
            //free the tmp that pointed at the cursor's node
            free(tmp);
        }
        
        free(cursor);
        
    }
    // TODO
    return true;
}
