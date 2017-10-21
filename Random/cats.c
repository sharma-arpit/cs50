#include<stdio.h>
#include<cs50.h>
#include<string.h>

#define FALSE 0
int main()
{
    string s= get_string();
    int i, count=1;
    if(s==NULL)
    {
        printf("There is no box\n");
        return 0;
    }
    else if((s[0] == 'C' || s[0] == 'c') && s[1] == 'a' && s[2] == 't' && (s[3] == '\0' || s[3] == ' '))
    {
        printf("The cat is the 1st item in box\n");
        return 0;
    }
    else
    {
        for(i=0;i<strlen(s); i++)
        {
            if(s[i] == ' ' && s[i+1] != ' ')
            {
                count++;
            }
            if(s[i] == 'c' && s[i+1] == 'a' && s[i+2] == 't' && (s[i+3] == ' ' || s[i+3] == '\0'))
            {
                if(s[i-1] == ' ')
                {    switch (count)
                    {
                        case 2:
                        printf("The cat is the 2nd item in the box\n");
                        break;
                        case 3:
                        printf("The cat is the 3rd item in the box\n");
                        break;
                        default:
                        printf("The cat is the %ith item in the box\n", count);
                        break;
                    }
                    return 0;
                }
            }
        }
    }
    printf("No cat yet\n");
    return 0;
}