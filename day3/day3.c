#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define HEIGHT 140
#define WIDTH 140

bool is_symbol(char character, int i, int j);
bool has_adjacent_symbol(char matrix[HEIGHT][WIDTH], int i, int j);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./day3 <input file>\n");
        return 1;
    }
    
    FILE *fp = fopen(argv[1], "r");
    
    if (fp == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }
    
    char character;
    char matrix[HEIGHT][WIDTH];
    
    int y = 0;
    int x = 0;
    
    while (fscanf(fp, "%c", &character) != EOF)
    {
        if (character == '\n')
        {
            y++;
            x = 0;
        }
        else
        {
            matrix[y][x] = character;
            x++;
        }
    }
    
    int part_numbers_sum = 0;
    bool evaluating_number = false;
    bool adjacent_symbol = false;
    int current_number = 0;
    
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            char c = matrix[i][j];
            if (!evaluating_number && isdigit(c))
            {
                current_number = c - '0';
                evaluating_number = true;
                if (has_adjacent_symbol(matrix, i, j))
                {
                    adjacent_symbol = true;
                }
            }
            else if (evaluating_number && isdigit(c))
            {
                current_number = current_number * 10 + (c - '0');
                if (!adjacent_symbol && has_adjacent_symbol(matrix, i, j))
                {
                    adjacent_symbol = true;
                }
            }
            else if (evaluating_number && !isdigit(c)) {
                if (adjacent_symbol)
                {
                    part_numbers_sum += current_number;
                }
                current_number = 0;
                evaluating_number = false;
                adjacent_symbol = false;
            }
            
            
        }
    }
    
    printf("Total Sum: %d\n", part_numbers_sum);
}

bool is_symbol(char character, int i, int j)
{
    if (i < 0 || j < 0 || i > HEIGHT - 1 || j > WIDTH - 1)
    {
        return false;
    }
    if (!isalnum(character) && character != '.')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool has_adjacent_symbol(char matrix[HEIGHT][WIDTH], int i, int j)
{
    if (is_symbol(matrix[i - 1][j - 1], i - 1, j - 1) || is_symbol(matrix[i - 1][j], i - 1, j) || is_symbol(matrix[i - 1][j + 1], i - 1, j + 1) || 
        is_symbol(matrix[i][j - 1], i, j - 1)                                                  || is_symbol(matrix[i][j + 1], i, j + 1) || 
        is_symbol(matrix[i + 1][j - 1], i + 1, j - 1) || is_symbol(matrix[i + 1][j], i + 1, j) || is_symbol(matrix[i + 1][j + 1], i + 1, j + 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}