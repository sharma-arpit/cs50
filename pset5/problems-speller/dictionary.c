/**
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include "dictionary.h"
#include <math.h>

#define HASHTABLE_SIZE 100000
unsigned nword =0;
typedef struct list{
    char word[46];
    struct list* next;
}
node;
//bool hash(node *);
node* hashtable[HASHTABLE_SIZE] = {NULL};
/**
 * Returns true if word is in dictionary else false.
 */

int hash(char* word)
{
    unsigned int h = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
        h = (h << 2) ^ word[i];
    return h % HASHTABLE_SIZE;
}


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
 * Loads dictionary into memory. Returns true if successful else false.
 */

bool load(const char *dictionary)
{
  
    FILE* infile = fopen(dictionary, "r");
    if(infile == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    char dword[47];
   // while(fscanf(infile, "%s", dword) != EOF)
    while(fgets(dword, sizeof(dword), infile))
    {
        dword[strlen(dword)-1] = '\0';
        node *new_node = malloc(sizeof(node));
        if(new_node == NULL)
        {
            unload();
            return false;
        }
        strncpy(new_node->word, dword, 46);
        new_node->next = NULL;
        
        int index = hash(dword);
        if (hashtable[index] == NULL)
    	{
    		hashtable[index] = new_node;
    	}

    	else
    	{
    		node* cursor = hashtable[index];
    		while (cursor->next != NULL)
    		{
    			cursor = cursor->next;
    		}

    		cursor->next = new_node;
    	}
        nword++;
    }
    fclose(infile);
    return true;
}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return nword;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for(int j=0;j<26;j++)
    {
        node* cursor = hashtable[j];
        while(cursor!=NULL)
        {
            node *temp = cursor->next;

            free(cursor);
            cursor = temp;
        }        
    }
    return true;
}