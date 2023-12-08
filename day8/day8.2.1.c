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

int get_steps(node nodes[], int nodes_count, char directions[], int start_node_index);
int get_next_node_index(node nodes[], int index, int nodes_count, char direction);
int get_node_index(node nodes[], int nodes_count, char name[]);
unsigned long gcd(unsigned long a, unsigned long b);
unsigned long lcm(unsigned long a, unsigned long b);

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
    int start_nodes_steps[NODES_COUNT];
    int start_nodes_count = 0;
    for (int i = 0; i < nodes_read; i++)
    {
        if (nodes[i].curr[2] == 'A')
        {
            start_nodes[start_nodes_count] = i;
            start_nodes_count++;
        }
    }
    
    // Determine steps to reach a node that ends with Z
    for (int i = 0; i < start_nodes_count; i++)
    {
        start_nodes_steps[i] = get_steps(nodes, nodes_read, directions, start_nodes[i]);
    }
    
    // int steps_gcd = gcd(start_nodes_steps[0], start_nodes_steps[1]);
    // for (int i = 2; i < start_nodes_count; i++)
    // {
    //     steps_gcd = gcd(steps_gcd, start_nodes_steps[i]);
    // }
    unsigned long steps_lcm = lcm(start_nodes_steps[0], start_nodes_steps[1]);
    for (int i = 2; i < start_nodes_count; i++)
    {
        printf("Steps to reach node %s: %d\n", nodes[start_nodes[i]].curr, start_nodes_steps[i]);
        steps_lcm = lcm(steps_lcm, start_nodes_steps[i]);
    }
    
    printf("Total steps: %lu\n", steps_lcm);
    
}

int get_steps(node nodes[], int nodes_count, char directions[], int start_node_index)
{
    int steps = 0;
    int curr_node_index = start_node_index;
    for (int i = 0; i < DIRECTIONS_LEN; i++)
    {
        char direction = directions[i];
        curr_node_index = get_next_node_index(nodes, curr_node_index, nodes_count, direction);
        steps++;
        if (nodes[curr_node_index].curr[2] == 'Z')
        {
            break;
        }
        if (i == DIRECTIONS_LEN - 1)
        {
            i = -1;
        }
    }
    return steps;
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

// Function to calculate gcd of two numbers
unsigned long gcd(unsigned long a, unsigned long b) {
    while (b != 0) {
        unsigned long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate lcm of two numbers
unsigned long lcm(unsigned long a, unsigned long b) {
    unsigned long absProduct = a * b;
    return absProduct / gcd(a, b);
}