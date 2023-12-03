#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define HEIGHT 140
#define WIDTH 140

int calculate(char matrix[HEIGHT][WIDTH], int i, int j);
int get_number(char matrix[HEIGHT][WIDTH], int i, int j);
int get_left_part(char matrix[HEIGHT][WIDTH], int i, int j);
int get_right_part(char matrix[HEIGHT][WIDTH], int i, int j, int left_part);

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

    // char matrix[HEIGHT][WIDTH] = {
    //     {'.', 'd', '#', '4', '5', '6', '.', '-'}};

    // printf("%i\n", get_number(matrix, 0, 4));

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

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            char c = matrix[i][j];
            if (c != '*')
            {
                continue;
            }
            part_numbers_sum += calculate(matrix, i, j);
        }
    }

    printf("Total Sum: %d\n", part_numbers_sum);
}

int calculate(char matrix[HEIGHT][WIDTH], int i, int j)
{
    int part_number_1 = 0;
    int part_number_2 = 0;
    bool adjacent_number = false;

    for (int k = 0; k < 8; k++)
    {
        char c = matrix[i - 1][j - 1];
        if (k == 0 && i > 0 && j > 0 && isdigit(c))
        {
            part_number_1 = get_number(matrix, i - 1, j - 1);
            adjacent_number = true;
        }

        c = matrix[i - 1][j];
        if (k == 1 && i > 0)
        {
            if (isdigit(c) && !adjacent_number)
            {
                part_number_1 = get_number(matrix, i - 1, j);
                adjacent_number = true;
            }
            if (!isdigit(c) && adjacent_number)
            {
                adjacent_number = false;
            }
        }

        c = matrix[i - 1][j + 1];
        if (k == 2 && i > 0 && j < WIDTH - 1)
        {
            if (isdigit(c) && !adjacent_number)
            {
                if (part_number_1 == 0)
                {
                    part_number_1 = get_number(matrix, i - 1, j + 1);
                }
                else
                {
                    part_number_2 = get_number(matrix, i - 1, j + 1);
                }
            }
            adjacent_number = false;
        }

        c = matrix[i][j - 1];
        if (k == 3 && j > 0)
        {

            if (isdigit(c))
            {
                if (part_number_2 != 0)
                {
                    return 0;
                }
                else if (part_number_1 == 0)
                {
                    part_number_1 = get_number(matrix, i, j - 1);
                }
                else
                {
                    part_number_2 = get_number(matrix, i, j - 1);
                }
            }
        }

        c = matrix[i][j + 1];
        if (k == 4 && j < WIDTH - 1)
        {
            if (isdigit(c))
            {
                if (part_number_2 != 0)
                {
                    return 0;
                }
                else if (part_number_1 == 0)
                {
                    part_number_1 = get_number(matrix, i, j + 1);
                }
                else
                {
                    part_number_2 = get_number(matrix, i, j + 1);
                }
            }
        }
        
        c = matrix[i + 1][j - 1];
        if (k == 5 && i < HEIGHT - 1 && j > 0 && isdigit(c))
        {
            if (part_number_2 != 0)
            {
                return 0;
            }
            else if (part_number_1 == 0)
            {
                part_number_1 = get_number(matrix, i + 1, j - 1);
            }
            else
            {
                part_number_2 = get_number(matrix, i + 1, j - 1);
            }
            adjacent_number = true;
        }

        c = matrix[i + 1][j];
        if (k == 6 && i > 0)
        {
            if (isdigit(c) && !adjacent_number)
            {
                if (part_number_2 != 0)
                {
                    return 0;
                }
                else if (part_number_1 == 0)
                {
                    part_number_1 = get_number(matrix, i + 1, j);
                }
                else
                {
                    part_number_2 = get_number(matrix, i + 1, j);
                }
                adjacent_number = true;
            }
            if (!isdigit(c) && adjacent_number)
            {
                adjacent_number = false;
            }
        }

        c = matrix[i + 1][j + 1];
        if (k == 7 && i > 0 && j < WIDTH - 1)
        {
            if (isdigit(c) && !adjacent_number)
            {
                if (part_number_2 != 0)
                {
                    return 0;
                }
                else if (part_number_1 == 0)
                {
                    part_number_1 = get_number(matrix, i + 1, j + 1);
                }
                else
                {
                    part_number_2 = get_number(matrix, i + 1, j + 1);
                }       
            }
        }
    }

    return part_number_1 * part_number_2;
}

int get_number(char matrix[HEIGHT][WIDTH], int i, int j)
{
    int left_part = get_left_part(matrix, i, j);
    int full_number = get_right_part(matrix, i, j, left_part);
    return full_number;
}

int get_left_part(char matrix[HEIGHT][WIDTH], int i, int j)
{
    char c = matrix[i][j];
    if (!isdigit(c))
    {
        return 0;
    }

    return get_left_part(matrix, i, j - 1) * 10 + (c - '0');
}

int get_right_part(char matrix[HEIGHT][WIDTH], int i, int j, int left_part)
{
    int full_number = left_part;
    j++;
    char c = matrix[i][j];
    while (isdigit(c))
    {
        full_number = full_number * 10 + (c - '0');
        j++;
        c = matrix[i][j];
    }
    return full_number;
}
