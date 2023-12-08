#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DIRECTIONS_LEN 293
#define NODES_COUNT 678

typedef struct
{
    char curr[4];
    char left[4];
    char right[4];
} node;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./day8.out <input file>\n");
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
    }

    // Read in directions
    char directions[DIRECTIONS_LEN];
    char ch;
    int directions_read = 0;
    while ((ch = fgetc(fp)) != '\n')
    {
        directions[directions_read] = ch;
        directions_read++;
    }

    // Read in nodes
    node nodes[NODES_COUNT];
    int nodes_read = 0;
    while (nodes_read < NODES_COUNT)
    {
        char curr[4];
        char left[4];
        char right[4];
        int ret = fscanf(fp, "%s = (%[^,], %[^)])", curr, left, right);
        if (ret == EOF)
        {
            break;
        }
        else if (ret != 3)
        {
            continue;
        }
        node new_node;
        strcpy(new_node.curr, curr);
        strcpy(new_node.left, left);
        strcpy(new_node.right, right);
        nodes[nodes_read] = new_node;
        nodes_read++;
    }

    // for (int i = 0; i < DIRECTIONS_LEN; i++)
    // {
    //     printf("%c", directions[i]);
    // }

    // for (int i = 0; i < nodes_read; i++)
    // {
    //     printf("%s = (%s, %s)\n", nodes[i].curr, nodes[i].left, nodes[i].right);
    // }

    // Get node for AAA
    node curr_node;
    for (int i = 0; i < nodes_read; i++)
    {
        if (strcmp(nodes[i].curr, "AAA") == 0)
        {
            curr_node = nodes[i];
            break;
        }
    }

    // Determine steps to reach ZZZ starting at AAA
    int steps = 0;
    for (int i = 0; i < directions_read; i++)
    {
        if (directions[i] == 'L')
        {
            for (int j = 0; j < nodes_read; j++)
            {
                if (strcmp(nodes[j].curr, curr_node.left) == 0)
                {
                    curr_node = nodes[j];
                    break;
                }
            }
        }
        else if (directions[i] == 'R')
        {
            for (int j = 0; j < nodes_read; j++)
            {
                if (strcmp(nodes[j].curr, curr_node.right) == 0)
                {
                    curr_node = nodes[j];
                    break;
                }
            }
        }
        steps++;
        if (strcmp(curr_node.curr, "ZZZ") == 0)
        {
            printf("Reached ZZZ in %d steps\n", steps);
            break;
        }
        if (i == directions_read - 1)
        {
            i = -1;
        }
    }
}