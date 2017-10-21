/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "rec.h"

int main()
{
    FILE* inptr = fopen("card2.raw", "r");
    if(inptr == NULL)
    {
        fprintf(stderr, "Could not open card.raw\n");
        return 1;
    }
    
    FILE* img = fopen("test.jpg" , "w");
    int i=0, k=0, c=0;
    FOX quad[128];
    char image[8];
    do
    {
        c = fread(&quad, sizeof(FOX), 128, inptr);
        {
            if(c==128 && quad[0].one == 0xff && quad[0].two == 0xd8 &&
            quad[0].three == 0xff && (quad[0].four & 0xf0) == 0xe0)
            {
                fclose(img);
                sprintf(image, "%.3d.bmp", i++);
                img = fopen(image, "a");
                if(img == NULL){printf("Could not open\n"); return 2;}
            }
            if(i>=1 && c==128)
            {
                for(int j=0;j<128;j++)
                {
                    FOX block = quad[j];
                    fwrite(&block, sizeof(FOX), 1, img);
                }
            }
        }
        k++;
        unsigned int pos = k * sizeof(FOX) * 128;
        fseek(inptr, pos, SEEK_SET);
    }while(c==128);
    fclose(inptr);
    fclose(img);
    return 0;
}
