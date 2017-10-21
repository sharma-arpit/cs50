#include<stdio.h>
int main()
{
	int no_test=0;
	scanf("%d", &no_test);
	float average[no_test];
	for(int i=0;i<no_test;i++)
	{
		scanf("%f", &average[i]);
	}
	for(int j=0;j<no_test;j++)
	{
		int a=average[j];
		double diff = average[j] - a;
		double games=0;
		if(diff!=0)   
		{
		   double w=1;
		   printf("w = %0.8f \n diff = %0.8f\n", w, diff);
		   printf("actual games = %f\n", w/diff);
		}
		else
		{
		   games = 1;
		}
		//printf("games = %f\n", games);
	}
	double f=0.100000;
	double q=1;
	printf(" standard = %f\n", q/f);
return 0;
}