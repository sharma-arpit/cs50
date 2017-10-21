#include<cs50.h>
#include<stdio.h>
int main(void)
{
    int num[5], c = 1;
    printf("Enter your numbers:\n");
    for(int i=0;i<5;i++)
    {
        num[i] = get_int();
    }
    do
    {
        c=0;
        for(int j=0;j<4;j++)
        {
            if(num[j] > num[j+1])
            {
                int temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                c++;
            }
        }
    }
    while(c != 0);
    printf("These are your sorted list of numbers:\n");
    for(int k=0;k<5;k++)
    {
        printf("%i ", num[k]);
    }
    printf("\n");
}