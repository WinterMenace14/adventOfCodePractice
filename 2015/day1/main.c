#include "stdio.h"
#include "stdlib.h"

#define CHAR_BUFFER 1000

void clearBuffer(char *buffer, int size);
void updateFloorValueFromBuffer(char *buffer, int bufferSize, int *floor);

int main()
{

    int floor = 0;
    char buffer[CHAR_BUFFER];
    clearBuffer(buffer, CHAR_BUFFER);

    // read in file
    FILE *fptr;
    fptr = fopen("./input.txt", "r");

    if (fptr == NULL)
    {
        perror("Failed to read the file.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Successfully read input file.\n");
    }

    // read in the line of characters
    while (fgets(buffer, CHAR_BUFFER, fptr) != NULL)
    {
        updateFloorValueFromBuffer(buffer, CHAR_BUFFER, &floor);
        clearBuffer(buffer, CHAR_BUFFER);
    }

    printf("The instructions lead to floor: %d\n", floor);

    fclose(fptr);
    return 0;
}

void clearBuffer(char *buffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        buffer[i] = '\0';
    }
}

void updateFloorValueFromBuffer(char *buffer, int bufferSize, int *floor)
{
    for (int i = 0; i < CHAR_BUFFER && buffer[i] != '\0'; i++)
    {
        if (buffer[i] == '(')
        {
            *floor = *floor + 1;
        }
        if (buffer[i] == ')')
        {
            *floor = *floor - 1;
        }
    }
}