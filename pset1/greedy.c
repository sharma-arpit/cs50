#include<cs50.h>
#include<stdio.h>
int main(void)
{
    int q, d, n, c, p;
    float m;
    printf("O hai!");
    do
    {
        printf("How much change is owed?\n");
        m = GetFloat();
    }while(m < 0);
    q = m*100/25;
    d = (m*100 - q*25)/10;
    n = (m*100 - q*25 - d*10)/5;
    p = (m*100 - q*25 - d*10 - n*5);
    c = q + d + n + p;
    printf("%d\n", c);
}