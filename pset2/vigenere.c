#include<stdio.h>
#include<cs50.h>
#include<string.h>
int main(int argc, string argv[])
{
    if(argc!=2)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    for(int a=0;a<strlen(argv[1]);a++)
    {
        if(argv[1][a]>=48 && argv[1][a]<=57)
        {
            printf("Usage: ./vigenere k\n");
            return 1;
        }
    }
    string s;
    int i, n, j=0;
    n = strlen(argv[1]);
    int k[n];
    printf("plaintext:  ");
    s = GetString();
    for(i=0;i<n;i++)
    {
        if(argv[1][i]>96 && argv[1][i]<123)
        {
            k[i] = -97 + argv[1][i];
        }
        else if(argv[1][i]>64 && argv[1][i]<91)
        {
            k[i] = -65 + argv[1][i];
        }
    }
    for(i=0;i<strlen(s);i++)
    {
        if((s[i]+k[j] <= 90 && s[i] >=65) ||(s[i]+k[j] <= 122 && s[i] >=97) )
        {
            s[i] = s[i] + k[j];
            j++;
        }
        else if( ( s[i]>90-k[j] && s[i] <=90 ) || (s[i]>122-k[j] && s[i] <=122))
        {
            s[i] = s[i] + k[j] - 26;
            j++;
        }
        if(j == n)
        {
            j=0;
        }
    }
    printf("ciphertext: %s\n", s);
return 0;
}