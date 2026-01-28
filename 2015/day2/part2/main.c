#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define LINE_BUFFER_SIZE 10
#define TOKEN_BUFFER_SIZE 4
#define NUM_SIDES 3

void cleanLineBuffer(char *lineBuffer, int size);
int findSmallestPerimeter(int sides[]);
int findLargestValue(int sides[]);

int main()
{

    unsigned long totalAmountOfRibbon = 0L;
    char lineBuffer[LINE_BUFFER_SIZE];
    char *tokenBuffer;

    FILE *fptr;
    fptr = fopen("../part1/input.txt", "r");

    if (fptr == NULL)
    {
        perror("Unable to open file.\n");
        exit(EXIT_FAILURE);
    }

    cleanLineBuffer(lineBuffer, LINE_BUFFER_SIZE);
    while (fgets(lineBuffer, LINE_BUFFER_SIZE, fptr) != NULL)
    {
        int sides[3];
        int sides_index = 0;

        tokenBuffer = strtok(lineBuffer, "x");
        sides[sides_index] = atoi(tokenBuffer);
        sides_index++;

        while ((tokenBuffer = strtok(NULL, "x")) != NULL)
        {
            sides[sides_index] = atoi(tokenBuffer);
            sides_index++;
        }

        // int surfaceAreaOfBox = (2 * sides[0] * sides[1]) + (2 * sides[1] * sides[2]) + (2 * sides[2] * sides[0]);
        int feetOfRibbonForBow = sides[0] * sides[1] * sides[2];
        feetOfRibbonForBow = feetOfRibbonForBow + findSmallestPerimeter(sides);
        totalAmountOfRibbon = totalAmountOfRibbon + feetOfRibbonForBow;
        cleanLineBuffer(lineBuffer, LINE_BUFFER_SIZE);
    }

    printf("The total feet of ribbon is: %lu\n", totalAmountOfRibbon);
    fclose(fptr);

    return 0;
}

void cleanLineBuffer(char *lineBuffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        lineBuffer[i] = '\0';
    }
}

int findIndexOfLargestValue(int sides[])
{

    int largestValueInArray = sides[0];
    int index = 0;
    for (int i = 1; i < NUM_SIDES; i++)
    {
        if (sides[i] > largestValueInArray)
        {
            largestValueInArray = sides[i];
            index = i;
        }
    }
    return index;
}

int findSmallestPerimeter(int sides[])
{
    int indexOfLargestValue = findIndexOfLargestValue(sides);
    int smallestSurfaceArea = 0;
    for (int i = 0; i < NUM_SIDES; i++)
    {
        if (i != indexOfLargestValue)
        {
            smallestSurfaceArea = smallestSurfaceArea + (2 * sides[i]);
        }
    }

    return smallestSurfaceArea;
}
