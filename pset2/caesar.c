#include<stdio.h>
#include<cs50.h>
#include<string.h>
int main(int argc, string argv[])
{
    if(argc !=2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    int k = atoi(argv[1]);
    string s;
    int i;
    k= k%26;
    printf("plaintext:  ");
    s = GetString();
    for(i=0; i<strlen(s); i++)
    {
        if((s[i]+k <= 90 && s[i] >=65) ||(s[i]+k <= 122 && s[i] >=97) )
        {
            s[i] = s[i] + k;
        }
        else if( ( s[i]>90-k && s[i] <=90 ) || (s[i]>122-k && s[i] <=122))
        {
            s[i] = s[i] + k - 26;
        }
    }
    printf("ciphertext: %s\n", s);
return 0;
}