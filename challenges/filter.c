#include "helpers.h"
// will help with including all the typedefs
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    printf("PICTURE height %i \n", height);
    printf("PICTURE width %i \n", width);

    RGBTRIPLE *p = &image[0][0];
    // modern computer systems are “64-bit”,
    // meaning that they use 64 bits to address memory
    // so a pointer should be 8 bytes? NO 12 hex digits * 4 = 48-bits (used for 64-bit system).
    printf("RGBTRIPLE pointer in memory --> %p \n", p);

    printf("RGBTRIPLE start value in memory location --> %i \n", *&p->rgbtBlue);

    printf("pixel one: location in memory: \n %p"
           "* for blue \n %p * for green \n %p * for red  \n",
           &image[0][0].rgbtBlue, &image[0][0].rgbtGreen, &image[0][0].rgbtRed);

    printf("pixel one: values \n %i * for blue \n %i * for green \n %i * for red  \n ",
           *&image[0][0].rgbtBlue, *&image[0][0].rgbtGreen, *&image[0][0].rgbtRed);

    int average = (*&image[0][0].rgbtBlue + *&image[0][0].rgbtGreen + *&image[0][0].rgbtRed) / 3;

    printf("pixel one: average value %i \n", average);

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // applyGrayScale(&image[row][column]);
            GrayScale(&image[row][column].rgbtBlue, &image[row][column].rgbtGreen, &image[row][column].rgbtRed);
        }
    }

    printf("RGBTRIPLE start value in memory --> %i \n", *&p->rgbtBlue);
    printf("pixel one location in memory: \n %p * for blue \n %p * for green \n %p * for red  \n ", &image[0][0].rgbtBlue, &image[0][0].rgbtGreen, &image[0][0].rgbtRed);
    printf("pixel one values: \n %i * for blue \n %i * for green \n %i * for red  \n ", *&image[0][0].rgbtBlue, *&image[0][0].rgbtGreen, *&image[0][0].rgbtRed);
    int average2 = (*&image[0][0].rgbtBlue + *&image[0][0].rgbtGreen + *&image[0][0].rgbtRed) / 3;
    printf("average value pixel one %i \n", average2);
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

void applyGrayScale(RGBTRIPLE *p)
{
    // int average = (*(p.rgbtBlue) + *(p.rgbtGreen) + *(p.rgbtRed)) / 3;

    int blue = *&p->rgbtBlue;
    int green = *&p->rgbtGreen;
    int red = *&p->rgbtRed;
    int average = (blue + green + red) / 3;
    *&p->rgbtBlue = average;
    *&p->rgbtGreen = average;
    *&p->rgbtRed = average;
    // printf("RGBTRIPLE start value in memory --> %i \n", *&p -> rgbtBlue);
}

void GrayScale(BYTE *blue, BYTE *green, BYTE *red)
{
    int average = (*blue + *green + *red) / 3;
    *blue = average;
    *green = average;
    *red = average;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE q = malloc() for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
        }
    }
}

#include "helpers.h"
// will help with including all the typedefs
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    printf("PICTURE height %i \n", height);
    printf("PICTURE width %i \n", width);

    RGBTRIPLE *p = &image[0][0];
    // modern computer systems are “64-bit”,
    // meaning that they use 64 bits to address memory
    // so a pointer should be 8 bytes? NO 12 hex digits * 4 = 48-bits (used for 64-bit system).
    printf("RGBTRIPLE pointer in memory --> %p \n", p);

    printf("RGBTRIPLE start value in memory location --> %i \n", *&p->rgbtBlue);

    printf("pixel one: location in memory: \n %p"
           "* for blue \n %p * for green \n %p * for red  \n",
           &image[0][0].rgbtBlue, &image[0][0].rgbtGreen, &image[0][0].rgbtRed);

    printf("pixel one: values \n %i * for blue \n %i * for green \n %i * for red  \n ",
           *&image[0][0].rgbtBlue, *&image[0][0].rgbtGreen, *&image[0][0].rgbtRed);

    int average = (*&image[0][0].rgbtBlue + *&image[0][0].rgbtGreen + *&image[0][0].rgbtRed) / 3;

    printf("pixel one: average value %i \n", average);

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            GrayScale(&image[row][column].rgbtBlue, &image[row][column].rgbtGreen, &image[row][column].rgbtRed);
        }
    }

    printf("pixel one: values adjusted \n %i * for blue \n %i * for green \n %i * for red  \n ",
           *&image[0][0].rgbtBlue, *&image[0][0].rgbtGreen, *&image[0][0].rgbtRed);

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            Sepia(&image[row][column].rgbtBlue, &image[row][column].rgbtGreen, &image[row][column].rgbtRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width / 2; column++)
        {
            Reflect(&image[row][column], &image[row][width - column]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ogImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ogImage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            getNeighbours(row, colum, height, width, ogImage, image)
        }
    }

    return;
}

void GrayScale(BYTE *blue, BYTE *green, BYTE *red)
{
    int average = (*blue + *green + *red) / 3;
    *blue = average;
    *green = average;
    *red = average;
}

void Sepia(BYTE *blue, BYTE *green, BYTE *red)
{
    BYTE tmpblue = *blue;
    BYTE tmpgreen = *green;
    BYTE tmpred = *red;
    // printf("pixel one: values \n %i ",
    //   tmpred);
    int blueNew = 0.272 * tmpred + 0.534 * tmpgreen + 0.131 * tmpblue;
    int greenNew = 0.349 * tmpred + 0.686 * tmpgreen + 0.168 * tmpblue;
    int redNew = 0.393 * tmpred + 0.769 * tmpgreen + 0.189 * tmpblue;
    *blue = blueNew;
    *green = greenNew;
    *red = redNew;
}

void Reflect(RGBTRIPLE *start, RGBTRIPLE *end)
{
    RGBTRIPLE tmp = *start;
    *start = *end;
    *end = tmp;
}

void getNeighbours(int row, int column, int height, int width, RGBTRIPLE ogImage[height][width], RGBTRIPLE[height][width] * image)
{
    int totalBlue = (*image[row][column]).rgbtBlue;
    int totalGreen = (*image[row][column]).rgbtGreen;
    int totalRed = (*image[row][column]).rgbtRed;
    int count = 1

        // right
        if (column + 1 < width)
    {
        adjustRGB(totalBlue, totalGreen, totalRed, ogImage[row][column + 1]);
        total += ogImage[row][column + 1];
        count++;
    }
    // left
    if (column - 1 >= 0)
    {
        total += ogImage[row][column - 1];
        count++;
    }

    if (row + 1 < height)
    {
        // under
        total += ogImage[row + 1][column];
        count++;
        if (column + 1 < width)
        {
            // under right
            total += myArray[row + 1][column + 1];
            count++;
        }
        if (column - 1 >= 0)
        {
            // under left
            total += myArray[row + 1][column - 1];
            count++;
        }
    }

    if (row - 1 >= 0)
    {
        // top
        total += myArray[row - 1][column];
        count++;

        if (column + 1 < width)
        {
            // top right
            total += myArray[row - 1][column + 1];
            count++;
        }

        if (column - 1 >= 0)
        {
            // top left
            total += myArray[row - 1][column - 1];
            count++;
        }
    }

    (*image[row][column]).rgbtBlue = totalBlue;
    (*image[row][column]).rgbtRed = totalRed;
    (*image[row][column]).rgbtGreen = totalGreen;
}

void adjustRGB(int *totalBlue, int *totalGreen, int *totalRed, RGBTRIPLE pixel)
{
    *totalBlue += pixel.rgbtBlue;
    *totalGreen += pixel.rgbtGreen;
    *totalRed += pixel.rgbtRed;
}