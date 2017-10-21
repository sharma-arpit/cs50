#include<stdio.h>
#include<cs50.h>
#include<string.h>
int main(void)
{
    int i, n;
    string s;
    s= GetString();
    if(s[0]<91 && s[0] >64)
    printf("%c", s[0] );
    else
    printf("%c", s[0]-32);
    for(i=1 ,n = strlen(s); i<n ; i++)
    {
        if(s[i-1]==' ')
        {
            if(s[i]<91 && s[i] >64)
            printf("%c", s[i] );
            else
            printf("%c", s[i]-32);
        }
    }
    printf("\n");
}