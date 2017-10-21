#include<cs50.h>
#include<stdio.h>
#include<string.h>
#define _XOPEN_SOURCE
#include<unistd.h>

char *crypt(const char *key, const char *salt);
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    char s[2];
    s[0] = argv[1][0];
    s[1] = argv[1][1];
    char* hash = &argv[1][2];
    printf("%s" , crypt(hash, s));
    printf("\n");
    return 0;
}