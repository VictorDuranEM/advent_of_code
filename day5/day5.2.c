#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ELEMENTS_COUNT 20
// #define ELEMENTS_COUNT 4

typedef struct map
{
    long dest_range_start;
    long source_range_start;
    long range_length;
    struct map *next;
} map;

long calculate_destination(long seed, map *current_map)
{
    if (current_map == NULL)
    {
        return seed;
    }

    if (seed >= current_map->source_range_start && seed < current_map->source_range_start + current_map->range_length)
    {
        return current_map->dest_range_start + (seed - current_map->source_range_start);
    }

    return calculate_destination(seed, current_map->next);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./day5 input.txt\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Read seeds
    long elements[ELEMENTS_COUNT];
    fseek(input, 7, SEEK_SET);

    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        fscanf(input, "%li", &elements[i]);
    }
    
    printf("HERE0\n");
    
    long seeds_count = 0;
    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        if (i % 2 != 0)
        {
            seeds_count += elements[i];
        }
    }
    
    printf("seeds_count: %li\n", seeds_count);
    
    long *seeds = malloc(sizeof(long) * seeds_count);
    int seeds_index = 0;
    
    printf("HERE1\n");
    
    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        if (i % 2 == 0)
        {
            printf("Element at index %i: %li\n", i, elements[i]);
            for (int j = 0; j < elements[i + 1]; j++)
            {
                seeds[seeds_index] = elements[i] + j;
                seeds_index++;
            }
        }
    }
    
    printf("HERE2\n");

    // Read maps
    map *seed_to_soil_map = NULL;
    map *soil_to_fertilizer_map = NULL;
    map *fertilizer_to_water_map = NULL;
    map *water_to_light_map = NULL;
    map *light_to_temperature_map = NULL;
    map *temperature_to_humidity_map = NULL;
    map *humidity_to_location_map = NULL;
    
    map *current_map = NULL;
    
    bool first_element = false;

    while (!feof(input))
    {
        char line[100];
        fgets(line, 100, input);
        if (line[0] == '\n')
        {
            continue;
        }
        else if (strcmp(line, "seed-to-soil map:\n") == 0)
        {
            // printf("seed-to-soil map:\n");
            seed_to_soil_map = malloc(sizeof(map));
            first_element = true;
            current_map = seed_to_soil_map;
        }
        else if (strcmp(line, "soil-to-fertilizer map:\n") == 0)
        {
            // printf("soil-to-fertilizer map:\n");
            soil_to_fertilizer_map = malloc(sizeof(map));
            first_element = true;
            current_map = soil_to_fertilizer_map;
        }
        else if (strcmp(line, "fertilizer-to-water map:\n") == 0)
        {
            // printf("fertilizer-to-water map:\n");
            fertilizer_to_water_map = malloc(sizeof(map));
            first_element = true;
            current_map = fertilizer_to_water_map;
        }
        else if (strcmp(line, "water-to-light map:\n") == 0)
        {
            // printf("water-to-light map:\n");
            water_to_light_map = malloc(sizeof(map));
            first_element = true;
            current_map = water_to_light_map;
        }
        else if (strcmp(line, "light-to-temperature map:\n") == 0)
        {
            // printf("light-to-temperature map:\n");
            light_to_temperature_map = malloc(sizeof(map));
            first_element = true;
            current_map = light_to_temperature_map;
        }
        else if (strcmp(line, "temperature-to-humidity map:\n") == 0)
        {
            // printf("temperature-to-humidity map:\n");
            temperature_to_humidity_map = malloc(sizeof(map));
            first_element = true;
            current_map = temperature_to_humidity_map;
        }
        else if (strcmp(line, "humidity-to-location map:\n") == 0)
        {
            // printf("humidity-to-location map:\n");
            humidity_to_location_map = malloc(sizeof(map));
            first_element = true;
            current_map = humidity_to_location_map;
        }
        else
        {
            long dest_range_start;
            long source_range_start;
            long range_length;
            sscanf(line, "%li %li %li", &dest_range_start, &source_range_start, &range_length);
            // printf("%li %li %li\n", dest_range_start, source_range_start, range_length);

            if (first_element)
            {
                current_map->dest_range_start = dest_range_start;
                current_map->source_range_start = source_range_start;
                current_map->range_length = range_length;
                current_map->next = NULL;
                first_element = false;
            }
            else
            {
                current_map->next = malloc(sizeof(map));
                current_map = current_map->next;
                current_map->dest_range_start = dest_range_start;
                current_map->source_range_start = source_range_start;
                current_map->range_length = range_length;
                current_map->next = NULL;
            }
        }
    }
    
    // print each map
    // printf("seed-to-soil map:\n");
    // current_map = seed_to_soil_map;
    // while (current_map != NULL)
    // {
    //     printf("%li %li %li\n", current_map->dest_range_start, current_map->source_range_start, current_map->range_length);
    //     current_map = current_map->next;
    // }
    
    // printf("soil-to-fertilizer map:\n");
    // current_map = soil_to_fertilizer_map;
    // while (current_map != NULL)
    // {
    //     printf("%li %li %li\n", current_map->dest_range_start, current_map->source_range_start, current_map->range_length);
    //     current_map = current_map->next;
    // }
    
    // printf("fertilizer-to-water map:\n");
    // current_map = fertilizer_to_water_map;
    // while (current_map != NULL)
    // {
    //     printf("%li %li %li\n", current_map->dest_range_start, current_map->source_range_start, current_map->range_length);
    //     current_map = current_map->next;
    // }
    
    // printf("water-to-light map:\n");
    // current_map = water_to_light_map;
    // while (current_map != NULL)
    // {
    //     printf("%li %li %li\n", current_map->dest_range_start, current_map->source_range_start, current_map->range_length);
    //     current_map = current_map->next;
    // }
    
    // printf("light-to-temperature map:\n");
    // current_map = light_to_temperature_map;
    // while (current_map != NULL)
    // {
    //     printf("%li %li %li\n", current_map->dest_range_start, current_map->source_range_start, current_map->range_length);
    //     current_map = current_map->next;
    // }
    
    // printf("temperature-to-humidity map:\n");
    // current_map = temperature_to_humidity_map;
    // while (current_map != NULL)
    // {
    //     printf("%li %li %li\n", current_map->dest_range_start, current_map->source_range_start, current_map->range_length);
    //     current_map = current_map->next;
    // }
    
    // printf("humidity-to-location map:\n");
    // current_map = humidity_to_location_map;
    // while (current_map != NULL)
    // {
    //     printf("%li %li %li\n", current_map->dest_range_start, current_map->source_range_start, current_map->range_length);
    //     current_map = current_map->next;
    // }
    
    printf("HERE3\n");
    
    // Calculate the final location
    long shortest_location = 0;
    for (int i = 0; i < seeds_count; i++)
    {
        long location = 0;
        long soil = calculate_destination(seeds[i], seed_to_soil_map);
        long fertilizer = calculate_destination(soil, soil_to_fertilizer_map);
        long water = calculate_destination(fertilizer, fertilizer_to_water_map);
        long light = calculate_destination(water, water_to_light_map);
        long temperature = calculate_destination(light, light_to_temperature_map);
        long humidity = calculate_destination(temperature, temperature_to_humidity_map);
        location = calculate_destination(humidity, humidity_to_location_map);
        if (i == 0 || location < shortest_location)
        {
            shortest_location = location;
        }
    }
    
    printf("Shortest location: %li\n", shortest_location);
    
    free(seeds);
}

// seed-to-soil map:
// soil-to-fertilizer map:
// fertilizer-to-water map:
// water-to-light map:
// light-to-temperature map:
// temperature-to-humidity map:
// humidity-to-location map: