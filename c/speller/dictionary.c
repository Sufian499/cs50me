// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 40;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Copy the word and make it lowercase
    char *pWord = malloc(strlen(word) + 1); // Creo una string pWord con el tamaño de memoria de strlen(word) + 1 para el '\0'.
    if (pWord == NULL)                      // If there is no memory space return false.
    {
        return false;
    }
    // Make all letters of the copied word lowercase
    int len = strlen(word);
    for (int i = 0; i <= len; i++)
    {
        pWord[i] = tolower(word[i]);
    }

    // hash the lowercase word, hash and check through de linked list.
    int checkHash = hash(pWord);
    node *cursor = table[checkHash];
    // check linked list till find if the word is in the dictionary.
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0) // If strcasecmp is == 0 the values are equal.
        {
            free(pWord);
            return true;
        }
        cursor = cursor->next;
    }
    free(pWord);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (word == NULL)
    {
        return 0;
    }
    unsigned int hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value += word[i];
        hash_value = (hash_value * word[i]);
    }
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    return hash_value % N; // Residuo % N para tener un numero dentro del rango 0 - N.
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the file and read through the words.
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false; // The dictionary could not be opened.
    }

    // Read through every line.
    char line[47];
    while (fscanf(dict, "%s", line) != EOF)
    {
        // Allocate memory for a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false; // No space
        }

        // Copy the word to the node word element and set null to next
        strcpy(n->word, line);
        n->next = NULL;
        // Hash
        int hash_position = hash(line);

        if (table[hash_position] == NULL) // If the position of table is empty, fill it with the node
        {
            table[hash_position] = n;
        }
        else // If a node is already in the position of the table, point the new node to the indexed node.
        {
            n->next = table[hash_position];
            table[hash_position] = n;
        }
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int wordCount = 0;

    // Bucle por todos los indices de tables
    for (int i = 0; i < N; i++)
    {
        // Bucle para recorrer la linked list
        for (node *ptr = table[i]; ptr != NULL; ptr = ptr->next)
        {
            wordCount++;
        }

        // Fácil de entender
        /*
        node *ptr = table[i];
        while (ptr != NULL)
        {
            wordCount++;
            ptr = ptr->next;
        }
        */
    }
    // printf("Words number: %i\n", wordCount);
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    int number_of_words = size(); // Init a variable with the number of word of dictinary
    int c = 0;                    // Counter var to count the word of the hash table
    // Travel through all linked list
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        node *tmp = NULL;
        while (ptr != NULL)
        {
            c++;
            tmp = ptr;       // Temp variable for storing the previous node
            ptr = ptr->next; // jump the pointer to the next node
            free(tmp);       // free the previous node
            tmp = NULL;
        }
        free(ptr); // Free the final node.
    }
    // If the number of words counted in the linked lists equals de words of the dictionary return true
    if (number_of_words == c)
    {
        return true;
    }
    else // return false if there was a word that was not fred.
    {
        return false;
    }
}
