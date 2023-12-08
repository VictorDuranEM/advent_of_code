#include <stdio.h>

#define ELEMENTS_COUNT 4

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./day6 <input file>\n");
        return 1;
    }
    
    FILE *fp = fopen(argv[1], "r");
    
    if (fp == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }
    
    // Obtain times and distances
    int times[ELEMENTS_COUNT];
    int distances[ELEMENTS_COUNT];
    
    fseek(fp, 6, SEEK_CUR);
    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        fscanf(fp, "%i", &times[i]);
    }
    
    fseek(fp, 10, SEEK_CUR);
    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        fscanf(fp, "%i", &distances[i]);
    }
    
    // Calculate margin
    int margin = 1;
    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        // print index
        int ways_to_win = 0;
        for (int j = 1; j < times[i]; j++)
        {
            int distance = (times[i] - j) * j;
            if (distance > distances[i])
            {
                ways_to_win++;
            }
        }
        if (ways_to_win != 0)
        {
            margin *= ways_to_win;
        }
    }
    
    printf("Margin: %i\n", margin);
    fclose(fp);
}