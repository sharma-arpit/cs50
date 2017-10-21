#include<cs50.h>
#include<stdio.h>
#include<string.h>
#define _XOPEN_SOURCE
#include<unistd.h>

char *crypt(const char *key, const char *salt);
int check(char* , char* , char*);
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
    char* hash = argv[1];
    char pass[5];
    for(int i=65;i < 91 ; i++)
    {
        pass[0] = i;
        for(int j =1 ;j< 5;j++)
        pass[j] = '\0';
        if(!check(pass, s, hash))
        {
            return 0;
        }
        pass[0] = i + 32;
        if(!check(pass, s, hash))
        {
            return 0;
        }
    }
    return 0;
}
int check(char* pass, char* s, char* hash)
{
    char* result = crypt(pass, s);
    int c = 0,n = strlen(result), i;
    for(i=0; i < n; i++)
    {
        if(hash[i] == result[i])
        {
            c++;
        }
    }
    if(c == n)
    {
        printf("%s", pass);
        printf("\n");
        return 0;
    }
return 2;
}