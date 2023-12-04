#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LINE_LENGTH 107 // Account for null terminator
#define WINNING_NUMBERS_LENGTH 10
#define PLAYER_NUMBERS_LENGTH 25
#define CHARACTERS_TO_SKIP 10

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./day4 <input file>\n");
        return 1;
    }
    
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }
    
    int total_points = 0;
    
    // int iteration = 1;
    
    while (1)
    {
        fseek(fp, CHARACTERS_TO_SKIP, SEEK_CUR);
        char line[LINE_LENGTH];
        fgets(line, LINE_LENGTH, fp);
        
        // printf("Line: %s\n", line);
        
        char* separator = strstr(line, " | ");
        *separator = '\0';
        separator += 3;
        char* winning_numbers_string = line;
        char* player_numbers_string = separator;
        
        int winning_numbers[WINNING_NUMBERS_LENGTH];
        int player_numbers[PLAYER_NUMBERS_LENGTH];
        
        int num = 0;
        char* token = strtok(winning_numbers_string, " ");
        while (token != NULL)
        {
            winning_numbers[num] = atoi(token);
            token = strtok(NULL, " ");
            num++;
        }
        
        num = 0;
        token = strtok(player_numbers_string, " ");
        while (token != NULL)
        {
            player_numbers[num] = atoi(token);
            token = strtok(NULL, " ");
            num++;
        }
        
        int matches = 0;
        
        for (int i = 0; i < PLAYER_NUMBERS_LENGTH; i++)
        {
            for (int j = 0; j < WINNING_NUMBERS_LENGTH; j++)
            {
                if (player_numbers[i] == winning_numbers[j])
                {
                    matches++;
                }
            }
        }
        
        int points = pow(2, matches - 1);
        total_points += points;
        
        // printf("Matches: %d\n", matches);
        // printf("Points: %d\n", points);
        
        // printf("Iteration: %d\n", iteration);
        // iteration++;
        
        // check if we are at the end of the file
        if (fgets(line, LINE_LENGTH, fp) == NULL)
        {
            break;
        }
    }
    
    printf("Total points: %d\n", total_points);
}