#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./day2 <input file>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    char line_buffer[200];
    int game_count = 1;
    int sum_valid_games = 0;
    bool validGame = true;

    // read a line from the file
    while (fgets(line_buffer, sizeof(line_buffer), fp) != NULL)
    {
        printf("%s", line_buffer);

        // get a substring after ": "
        char *line = strstr(line_buffer, ": ");
        char *substring = strstr(line_buffer, ": ") + 2;

        int digit = 0;
        char color[6];
        char color_index = 0;

        for (int i = 0; i < strlen(substring); i++)
        {
            char c = substring[i];
            if (isdigit(c))
            {
                if (digit == 0)
                {
                    digit = c - '0';
                }
                else
                {
                    digit = digit * 10 + (c - '0');
                }
            }

            if (digit > 0 && substring[i] == ' ')
            {
                continue;
            }

            if (digit > 0 && !isdigit(c))
            {
                if (c == ',' || c == ';' || c == '\n')
                {
                    if (strcmp(color, "green") == 0 && digit > 13)
                    {
                        validGame = false;
                        break;
                    }
                    else if (strcmp(color, "red") == 0 && digit > 12)
                    {
                        validGame = false;
                        break;
                    }
                    else if (strcmp(color, "blue") == 0 && digit > 14)
                    {
                        validGame = false;
                        break;
                    }
                    digit = 0;
                    color_index = 0;
                    color[color_index] = '\0';
                }
                else
                {
                    color[color_index] = c;
                    color_index++;
                    color[color_index] = '\0';
                }
            }
        }
        
        if (validGame)
        {
            sum_valid_games += game_count;
            printf("valid game: %i\n\n", game_count);
        }
        else
        {
            printf("invalid game: %i\n\n", game_count);
        }
        
        validGame = true;
        game_count++;
    }
    
    printf("sum_valid_games: %i\n", sum_valid_games);
}