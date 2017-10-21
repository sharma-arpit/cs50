#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    
    if (argc != 4)
    {
        printf("Usage: ./resize infile outfile factor\n");
        return 1;
    }

    char* infile = argv[1];
    char* outfile = argv[2];
    float n;
    char c;
    
    if(sscanf(argv[3], "%f %c", &n, &c) != 1)
    {
        printf("factor, must be a float\n");
        return 5;
    }
    if(n>100 || n<=0)
    {
        printf(" factor must be in the range 0< n <=100");
        return 4;
    }
    
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    int oldWidth = bi.biWidth;
    int oldPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biWidth *= n;
    bi.biHeight *= n;

    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE currRow[oldWidth];
    int rowNum = -1;
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        int oldI = i / n;
        
        if(rowNum != oldI)
        {
            unsigned int pos = (3 * oldWidth + oldPadding) * oldI + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);
            fseek(inptr, pos, SEEK_SET);
            rowNum = oldI;
            fread(&currRow, sizeof(RGBTRIPLE), oldWidth, inptr);
        }
        
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple = currRow[(int) (j/n)];

            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

        }
    
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}