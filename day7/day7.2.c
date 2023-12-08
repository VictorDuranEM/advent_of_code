#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define ITEMS 1000
#define ITEM_SIZE 10
#define HAND_SIZE 5
#define FIVE_OF_A_KIND 6
#define FOUR_OF_A_KIND 5
#define FULL_HOUSE 4
#define THREE_OF_A_KIND 3
#define TWO_PAIRS 2
#define ONE_PAIR 1
#define HIGH_CARD 0

typedef struct
{
    char hand[HAND_SIZE + 1]; // Accounting for null terminator
    int type;
    int bid;
} hand;

typedef struct
{
    char card;
    int count;
} card;

void classify(hand *h);
void merge_sort(hand hands[ITEMS], int start, int end);
bool is_lower_than(hand *a, hand *b);
int get_card_strength(char card);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./day7 <input file>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    char *items[ITEMS];
    char line[ITEM_SIZE + 1];
    printf("Reading file...\n");
    for (int i = 0; fgets(line, ITEM_SIZE + 1, fp) != NULL;)
    {
        if (line[0] == '\n')
        {
            continue;
        }
        items[i] = strdup(line);
        i++;
    }

    printf("Creating hands...\n");
    hand hands[ITEMS];
    for (int i = 0; i < ITEMS; i++)
    {
        hand h;
        sscanf(items[i], "%s %d", h.hand, &h.bid);
        hands[i] = h;
    }

    printf("Classifying hands...\n");
    for (int i = 0; i < ITEMS; i++)
    {
        classify(&hands[i]);
    }

    printf("Sorting hands...\n");
    merge_sort(hands, 0, ITEMS - 1);
    
    // print hands with all their attributes
    // for (int i = 0; i < ITEMS; i++)
    // {
    //     printf("%s %d %d\n", hands[i].hand, hands[i].bid, hands[i].type);
    // }

    printf("Calculating total winnings...\n");
    int total = 0;
    for (int i = 0; i < ITEMS; i++)
    {
        total += hands[i].bid * (i + 1);
    }

    printf("Total winnings: %d\n", total);
}

void classify(hand *h)
{
    char *hand = h->hand;
    card cards[HAND_SIZE];
    for (int i = 0; i < HAND_SIZE; i++)
    {
        cards[i].card = '\0';
        cards[i].count = 0;
    }
    int count = 0;
    for (int i = 0; i < HAND_SIZE; i++)
    {
        bool found = false;
        for (int j = 0; j < count; j++)
        {
            if (cards[j].card == hand[i])
            {
                cards[j].count++;
                found = true;
                break;
            }
        }
        if (!found)
        {
            card c;
            c.card = hand[i];
            c.count = 1;
            cards[count] = c;
            count++;
        }
    }
    // Count how many Js in cards
    int j_count = 0;
    for (int i = 0; i < count; i++)
    {
        if (cards[i].card == 'J')
        {
            j_count = cards[i].count;
            break;
        }
    }

    if (count == 1)
    {
        h->type = FIVE_OF_A_KIND;
    }
    else if (count == 2)
    {
        if (j_count > 0)
        {
            h->type = FIVE_OF_A_KIND;
        }
        else if (cards[0].count == 4 || cards[1].count == 4)
        {
            h->type = FOUR_OF_A_KIND;
        }
        else
        {
            h->type = FULL_HOUSE;
        }
    }
    else if (count == 3)
    {
        if (cards[0].count == 3 || cards[1].count == 3 || cards[2].count == 3)
        {
            if (j_count > 0)
            {
                h->type = FOUR_OF_A_KIND;
            }
            else
            {
                h->type = THREE_OF_A_KIND;
            }
        }
        else
        {
            if (j_count == 1)
            {
                h->type = FULL_HOUSE;
            }
            else if (j_count == 2)
            {
                h->type = FOUR_OF_A_KIND;
            }
            else
            {
                h->type = TWO_PAIRS;
            }
        }
    }
    else if (count == 4)
    {
        if (j_count > 0)
        {
            h->type = THREE_OF_A_KIND;
        }
        else
        {
            h->type = ONE_PAIR;
        }
    }
    else
    {
        if (j_count == 1)
        {
            h->type = ONE_PAIR;
        }
        else
        {
            h->type = HIGH_CARD;
        }
    }
}

void merge_sort(hand hands[ITEMS], int start, int end)
{
    if (start == end)
    {
        return;
    }
    int mid = (start + end) / 2;
    merge_sort(hands, start, mid);
    merge_sort(hands, mid + 1, end);

    hand temp[ITEMS];
    int a = start;
    int b = mid + 1;
    for (int i = 0; i < end - start + 1; i++)
    {
        if (a > mid)
        {
            temp[i] = hands[b];
            b++;
        }
        else if (b > end)
        {
            temp[i] = hands[a];
            a++;
        }
        else if (is_lower_than(&hands[a], &hands[b]))
        {
            temp[i] = hands[a];
            a++;
        }
        else
        {
            temp[i] = hands[b];
            b++;
        }
    }

    for (int i = start; i <= end; i++)
    {
        hands[i] = temp[i - start];
    }
}

bool is_lower_than(hand *a, hand *b)
{
    if (a->type < b->type)
    {
        return true;
    }
    else if (a->type > b->type)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < HAND_SIZE; i++)
        {
            if (get_card_strength(a->hand[i]) < get_card_strength(b->hand[i]))
            {
                return true;
            }
            else if (get_card_strength(a->hand[i]) > get_card_strength(b->hand[i]))
            {
                return false;
            }
        }
    }
    // if both hands are equal
    return false;
}

int get_card_strength(char card)
{
    switch (card)
    {
    case 'A':
        return 14;
    case 'K':
        return 13;
    case 'Q':
        return 12;
    case 'J':
        return -1;
    case 'T':
        return 10;
    default:
        return card - '0';
    }
}