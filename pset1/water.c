#include<cs50.h>
#include<stdio.h>
int main(void)
{
    int min;
    printf("minutes: ");
    min = GetInt();
    printf("bottles: %d \n", 12*min);
}