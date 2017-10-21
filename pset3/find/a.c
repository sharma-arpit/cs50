#include<stdio.h>
#include<cs50.h>

const int MAX = 65563;
int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./a d");
        return 1;
    }
    int count=0, size, haystack[MAX];
    int needle = atoi(argv[1]);
    for(size=0; size< MAX; size++)
    {
        int straw = get_int();
        if (straw == INT_MAX)
        {
            break;
        }
        haystack[size] = straw;
    }
    for(int i=0; i < size; i++)
    {
        if(haystack[i] == needle)
        {
            count++;
        }
    }
    printf("We found needle in this Haystack %d times.\n", count);
    return 0;
}