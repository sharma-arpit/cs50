//#include<cs50.h>
#include<stdio.h>
extern void _exit(register int);

int _start()
{
    int n, i, j;
    do
    {
        printf("Height: ");
        scanf("%i", &n);
    }while(n>23||n<0);
    for(j=0;j<n;j++)
    {
        for(i=0;i<n-j-1;i++)// it will print '  '
        {
            printf(" ");
        }
        for(i=n-j-1;i<n;i++)// it will print '#'
        {
            printf("#");
        }
        printf("#");
        printf("\n");
    }
    _exit(0);
}