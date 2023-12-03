#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    
    int game_power = 0;

    // read a line from the file
    while (fgets(line_buffer, sizeof(line_buffer), fp) != NULL)
    {
        // printf("%s", line_buffer);

        // get a substring after ": "
        char *line = strstr(line_buffer, ": ");
        char *substring = strstr(line_buffer, ": ") + 2;

        int digit = 0;
        char color[6];
        char color_index = 0;
        int max_red = 0;
        int max_green = 0;
        int max_blue = 0;

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
                    if (strcmp(color, "green") == 0)
                    {
                        if (digit > max_green)
                        {
                            max_green = digit;
                        }
                    }
                    else if (strcmp(color, "red") == 0)
                    {
                        if (digit > max_red)
                        {
                            max_red = digit;
                        }
                    }
                    else if (strcmp(color, "blue") == 0)
                    {
                        if (digit > max_blue)
                        {
                            max_blue = digit;
                        }
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
        
        game_power += max_red * max_green * max_blue;
    }
    
    printf("Game power: %i\n", game_power);
    
}