#include<stdio.h>
#include<unistd.h>
int main(void)
{
    while (1)
    {
        printf("\\");
        sleep(1);
        printf("\b");
        printf("-");
        sleep(1);
        printf("\b");
        printf("/");
        sleep(1);
        printf("\b");
        printf("-");
        sleep(1);
        printf("\b");
    }
}