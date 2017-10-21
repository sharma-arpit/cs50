/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include<stdio.h>
#include "helpers.h"
bool sea(int needle, int values[], int p, int q)
{
    int a, b, c, d, i=(p+q)/2; 
    if(values[i] == needle)
    {
        return true;
    }
    else if(values[i] < needle)
    {
        a = i+1;
        b = q;
        if(a>b){return false;}
        return sea(needle, values, a, b);
    }
    else if(values[i] > needle)
    {
        c = p;
        d = i-1;
        if(c>d){return false;}
        return sea(needle, values, c, d);
    }
    return false;
}
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int p, q, r, i = n/2;
    if(values[i] == value)
    {
        return true;
    }
    else if(values[i] < value)
    {
        p=i+1;
        q=n;
        if(p>q){return false;}
        return sea(value, values, p, q );
    }
    else if(values[i] > value)
    {
        r=i-1;
        if(r<0){return false;}
        return search(value, values, r);
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //insertionsort
    int j, i, temp=0;
    for(i=0;i<n;i++)
    {
        temp = values[i];
        j=i-1;
        while(j>=0 && values[j]>temp)
        {
            values[j+1] = values[j];
            values[j]=temp;
            j--;
        }
    }
    for(int i=0;i<n;i++)
    {
        printf("%i\n", values[i]);
    }
    return;
}
