#include <stdio.h>
#include <stdlib.h>

#define TOTAL_LINE_BUFFER 8193
#define HEIGHT 4100
#define LENGTH 4120

void setSantasGrid(int rows, int columns, int *grid);
void countHousesWithGifts(int rows, int columns, int *grid, int *numHouses);

int main()
{

    int numHousesGotAtleastOneGift = 0;
    int roboX = 2059, roboY = 2049;
    int xPos = 2059, yPos = 2049;
    int *santasGrid = malloc(HEIGHT * LENGTH * sizeof(int));
    char instructionLine[TOTAL_LINE_BUFFER];
    int numLeft = 0, numRight = 0, numUp = 0, numDown = 0;

    FILE *fptr;
    fptr = fopen("../input.txt", "r");

    if (fptr == NULL)
    {
        perror("Failed to open the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("Successfully opened file!\n");

    if (fgets(instructionLine, TOTAL_LINE_BUFFER, fptr) == NULL)
    {
        perror("Error in reading line.\n");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    setSantasGrid(HEIGHT, LENGTH, (int *)santasGrid);

    int *santasAddress = (int *)santasGrid + yPos * LENGTH + xPos;
    *santasAddress = *santasAddress + 1;

    int *roboSantaAddress = (int *)santasGrid + roboY * LENGTH + roboX;
    *roboSantaAddress = *roboSantaAddress + 1;

    for (int i = 0; i < TOTAL_LINE_BUFFER; i++)
    {
        if (i % 2 == 0)
        {
            switch (instructionLine[i])
            {
            case '^':
                yPos++;
                break;
            case 'v':
                yPos--;
                break;
            case '<':
                xPos--;
                break;
            case '>':
                xPos++;
                break;
            default:
                printf("Uncertain of symbol: %c\n", instructionLine[i]);
            }

            santasAddress = (int *)santasGrid + yPos * LENGTH + xPos;
            *santasAddress = *santasAddress + 1;
        }
        else
        {
            switch (instructionLine[i])
            {
            case '^':
                roboY++;
                break;
            case 'v':
                roboY--;
                break;
            case '<':
                roboX--;
                break;
            case '>':
                roboX++;
                break;
            default:
                printf("Uncertain of symbol: %c\n", instructionLine[i]);
            }

            roboSantaAddress = (int *)santasGrid + roboY * LENGTH + roboX;
            *roboSantaAddress = *roboSantaAddress + 1;
        }
    }

    countHousesWithGifts(HEIGHT, LENGTH, (int *)santasGrid, &numHousesGotAtleastOneGift);

    printf("The number of houses that at least got 1 present is: %d\n", numHousesGotAtleastOneGift);

    fclose(fptr);
    free(santasGrid);
    return 0;
}

void setSantasGrid(int rows, int columns, int *grid)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            *(grid + i * columns + j) = 0;
        }
    }
}

void countHousesWithGifts(int rows, int columns, int *grid, int *numHouses)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (*(grid + i * columns + j) > 0)
            {
                *numHouses = *numHouses + 1;
            }
        }
    }
}
