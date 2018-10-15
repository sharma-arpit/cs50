#include<iostream>
#include<stdio.h>
#include<stdlib.h>


void swap(int*xp, int*yp)
{
	int*temp;
	*temp = *xp;
	*xp = *yp;
	*yp = *temp;
	return;
}


//selection ---- O(n2)

void selectionsort(int arr[], int n)
{
	int i,j,min;
	for(i = 0; i<n-1;i++)
	{
		min = i;
		for(j= i+1;j<n;j++)
			if(arr[j]<arr[min])
				min = j;
		
		swap(&arr[min], &arr[i]);	
	}
	
	
}


