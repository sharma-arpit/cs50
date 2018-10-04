/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */
#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include "dictionary.h"


typedef struct list{
    char key[45];
    struct list* next;
}
node;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
        int l = strlen(word);
    char *copy = malloc(l);
    
    for (int i = 0; i < l; i++)
        copy[i] = tolower(word[i]);
    
    copy[l] = '\0';

    int index = hash(copy);

    node* entry = hashtable[index];
    if (entry)
    {
        // point a cursor node to the head node
        node* cursor = entry;

        // loop through the nodes while a next pointer isn't null
        while (cursor->next != NULL)
            {
                if (strcmp(copy, cursor->word) == 0)
                    return true;

                cursor = cursor->next;
            };

        if (strcmp(copy, cursor->word) == 0)
    		return true;

			cursor = cursor->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
//-----Make an array of Linked List and assign the leading link a key(a-z)-----
    node table[26];
    int c=97;
    for(int i=0;i<26;i++)
    {
        table[i].key[0] = c;
        table[i].next = NULL;
        c++;
    }
//------------------------------------------------------------------------

// ----------Open the Dictionary in read mode------------
    FILE* ptr = fopen("dictionaries/large", "r");
    if(ptr == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
//-------------------------------------------------------

    int index = 0, w=0, k=0;  // k has been used to browsing in table
    char word[LENGTH+1];
//------Start reading the dictionary by letter by letter------
    for(w = fgetc(ptr); w!=EOF ; w = fgetc(ptr))
    {
        if(w != '\n')
        {
            if (isalpha(w) || (w == '\'' && index > 0))
            {
                word[index] = w;
                index++;
                if (index > LENGTH)
                {
                    while ((w = fgetc(ptr)) != EOF && isalpha(w));
                    index = 0;
                }
            
            }
        }
        else if(index > 0)
        {
            word[index] = '\0';
            for(k=0;k<26;k++)
            {
                if((table[k].key[0] == word[0]) && (table[k].next == NULL))
                {
                    node* newptr = malloc(sizeof(node));
                    if(newptr == NULL)
                    {
                        unload();
                        return false;
                    }
                    for(int j = 0; j<=index; j++)
                    {
                        newptr->key[j] = word[j];
                    }
                    newptr->next = NULL;
                    table[k].next = newptr;
                }
                else if(table[k].key[0] == word[0])
                {
                    node *nptr = table[k].next;
                    while(nptr != NULL)
                    {
                        nptr = nptr->next;
                    }
                    node* newptr = malloc(sizeof(node));
                    if(newptr == NULL)
                    {
                        unload();
                        return false;
                    }
                    for(int j = 0; j<=index; j++)
                    {
                        newptr->key[j] = word[j];
                    }
                    newptr->next = NULL;
                    nptr = newptr;
                }
            }
            index = 0;
        }
    }
    if(ferror(ptr))
    {
        printf("Error reading...\n");
        fclose(ptr);
        unload();
        return false;
    }
    fclose(ptr);
    int z = 0;
    while(z < 26)
    {
        node *priptr = table[z].next;
        while(priptr != NULL)
        {
            printf("%s", priptr->key);
            printf("\n");
            priptr = priptr->next;
        }
    }
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    
    return false;
}
