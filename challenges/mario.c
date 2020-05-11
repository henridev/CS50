#include <cs50.h>
#include <stdio.h>

void printLeft(int whitespace, int tagsToPrint); 
void printRight(int whitespace, int tagsToPrint); 

int main(void)
{
    int height = 0;
    while (height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }

    int tagsToPrint = 1;
    int whitespace = height - tagsToPrint;
    
    for (int i = 0; i < height; i++)
    {
        printLeft(whitespace, tagsToPrint);
        printf("  ");
        printRight(whitespace, tagsToPrint);
        tagsToPrint++;
        whitespace--;
        printf("\n");
    }
}

void printLeft(int whitespace, int tagsToPrint)
{
    for (int j = 0; j < whitespace; j++)
    {
        printf(" ");
    }
    for (int k = 0; k < tagsToPrint; k++)
    {
        printf("#");
    }
}

void printRight(int whitespace, int tagsToPrint)
{
    for (int j = 0; j < tagsToPrint; j++)
    {
        printf("#");
    }
}