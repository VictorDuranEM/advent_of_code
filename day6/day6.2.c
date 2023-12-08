#include <stdio.h>
#include <math.h>

#define ELEMENTS_COUNT 4

int numDigits(int num);

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

    long race_time = 0;
    long record_distance = 0;

    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        race_time += times[i];
        record_distance += distances[i];
        if (i + 1 < ELEMENTS_COUNT)
        {
            race_time *= pow(10, numDigits(times[i + 1]));
            record_distance *= pow(10, numDigits(distances[i + 1]));
        }
    }

    printf("Race time: %li\n", race_time);
    printf("Record distance: %li\n", record_distance);

    long min = 0;
    long max = 0;

    // Calculate margin
    long margin = 0;
    for (long i = 1; i < race_time; i++)
    {
        long distance = (race_time - i) * i;
        if (distance > record_distance)
        {
            if (min == 0)
            {
                min = i;
            }
            margin++;
        }
        else if (min != 0)
        {
            max = i - 1;
            break;
        }
    }
    
    printf("Min: %li\n", min);
    printf("Max: %li\n", max);
    printf("Margin: %li\n", margin);
    fclose(fp);
}

int numDigits(int num)
{
    int digits = 0;
    while (num != 0)
    {
        num /= 10;
        digits++;
    }
    return digits;
}