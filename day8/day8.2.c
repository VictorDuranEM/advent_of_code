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

int get_next_node_index(node nodes[], int index, int nodes_count, char direction);
int get_node_index(node nodes[], int nodes_count, char name[]);

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

    // Get the index of all nodes that end with A
    int start_nodes[NODES_COUNT];
    int start_nodes_count = 0;
    for (int i = 0; i < nodes_read; i++)
    {
        if (nodes[i].curr[2] == 'A')
        {
            start_nodes[start_nodes_count] = i;
            start_nodes_count++;
        }
    }
    
    // TODO remove
    // start_nodes_count = 2;
    printf("Start nodes count: %d\n", start_nodes_count);

    // Determine steps to reach a node that ends with Z
    unsigned long steps = 0;
    for (int i = 0; i < directions_read; i++)
    {
        // get next node for each start node
        for (int j = 0; j < start_nodes_count; j++)
        {
            start_nodes[j] = get_next_node_index(nodes, start_nodes[j], nodes_read, directions[i]);
        }
        steps++;
        // check if all of the nodes end with Z
        bool all_end_with_z = true;
        // for (int k = 0; k < start_nodes_count; k++)
        // {
        //     printf("%s ", nodes[start_nodes[k]].curr);
        // }
        // printf("\n");
        for (int k = 0; k < start_nodes_count; k++)
        {
            if (nodes[start_nodes[k]].curr[2] != 'Z')
            {
                all_end_with_z = false;
                break;
            }
        }
        if (all_end_with_z)
        {
            break;
        }
        if (i == directions_read - 1)
        {
            i = -1;
        }
    }
    
    printf("Steps: %lu\n", steps);
    
}

int get_next_node_index(node nodes[], int index, int nodes_count, char direction)
{
    node curr_node = nodes[index];
    if (direction == 'L')
    {
        return get_node_index(nodes, nodes_count, curr_node.left);
    }
    else if (direction == 'R')
    {
        return get_node_index(nodes, nodes_count, curr_node.right);
    }
    return -1;
}

int get_node_index(node nodes[], int nodes_count, char name[])
{
    for (int i = 0; i < nodes_count; i++)
    {
        if (strcmp(nodes[i].curr, name) == 0)
        {
            return i;
        }
    }
    return -1;
}