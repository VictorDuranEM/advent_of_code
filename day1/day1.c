#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./Day1.1 <input file>\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

   if (input == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }
    
    char c = 0;
    int sum = 0;
    int firstDigit = -1;
    int lastDigit = -1;
    char word[6];
    int wordLen = 0;
    int count = 0;

    while (c != EOF)
    {
        c = fgetc(input);

        if ((c == '\n' || c == EOF) && firstDigit != -1)
        {
            int num = firstDigit * 10 + lastDigit;
            count++;
            printf("%i: %i\n", count, num);
            sum += num;
            firstDigit = -1;
            lastDigit = -1;
            wordLen = 0;
            word[wordLen] = '\0';
        }
        else if (c >= '0' && c <= '9')
        {
            if (firstDigit == -1)
            {
                firstDigit = c - '0';
                lastDigit = c - '0';
            }
            else if (firstDigit != -1)
            {
                lastDigit = c - '0';
            }
            wordLen = 0;
            word[wordLen] = '\0';
        }
        else if (wordLen == 0 && (c == 'o' || c == 't' || c == 'f' || c == 's' || c == 'e' || c == 'n'))
        {
            word[wordLen] = c;
            wordLen++;
            word[wordLen] = '\0';
        }
        else if (wordLen == 1 && (c == 'n' || c == 'w' || c == 'h' || c == 'o' || c == 'i' || c == 'e'))
        {
            word[wordLen] = c;
            wordLen++;
            word[wordLen] = '\0';
            if (!(strcmp(word, "on") == 0 || strcmp(word, "tw") == 0 || strcmp(word, "th") == 0 || strcmp(word, "fo") == 0 || strcmp(word, "fi") == 0 || strcmp(word, "si") == 0 || strcmp(word, "se") == 0 || strcmp(word, "ei") == 0 || strcmp(word, "ni") == 0))
            {
                wordLen = 1;
                word[0] = c;
                word[1] = '\0';
            }
        }
        else if (wordLen == 2 && (c == 'e' || c == 'o' || c == 'r' || c == 'u' || c == 'v' || c == 'x' || c == 'g' || c == 'n'))
        {
            word[wordLen] = c;
            wordLen++;
            word[wordLen] = '\0';
            if (!(strcmp(word, "one") == 0 || strcmp(word, "two") == 0 || strcmp(word, "thr") == 0 || strcmp(word, "fou") == 0 || strcmp(word, "fiv") == 0 || strcmp(word, "six") == 0 || strcmp(word, "sev") == 0 || strcmp(word, "eig") == 0 || strcmp(word, "nin") == 0))
            {
                wordLen = 1;
                word[0] = c;
                word[1] = '\0';
            }
            if (strcmp(word, "one") == 0)
            {
                if (firstDigit == -1)
                {
                    firstDigit = 1;
                    lastDigit = 1;
                }
                else if (firstDigit != -1)
                {
                    lastDigit = 1;
                }
                wordLen = 1;
                word[0] = 'e';
                word[1] = '\0';
            }
            // do the same for two and six
            else if (strcmp(word, "two") == 0)
            {
                if (firstDigit == -1)
                {
                    firstDigit = 2;
                    lastDigit = 2;
                }
                else if (firstDigit != -1)
                {
                    lastDigit = 2;
                }
                wordLen = 1;
                word[0] = 'o';
                word[1] = '\0';
            }
            else if (strcmp(word, "six") == 0)
            {
                if (firstDigit == -1)
                {
                    firstDigit = 6;
                    lastDigit = 6;
                }
                else if (firstDigit != -1)
                {
                    lastDigit = 6;
                }
                wordLen = 0;
                word[wordLen] = '\0';
            }
        }
        else if (wordLen == 3 && (c == 'e' || c == 'r' || c == 'h'))
        {
            word[wordLen] = c;
            wordLen++;
            word[wordLen] = '\0';
            if (!(strcmp(word, "thre") == 0 || strcmp(word, "four") == 0 || strcmp(word, "five") == 0 || strcmp(word, "seve") == 0 || strcmp(word, "eigh") == 0 || strcmp(word, "nine") == 0))
            {
                wordLen = 1;
                word[0] = c;
                word[1] = '\0';
            }
            if (strcmp(word, "four") == 0)
            {
                if (firstDigit == -1)
                {
                    firstDigit = 4;
                    lastDigit = 4;
                }
                else if (firstDigit != -1)
                {
                    lastDigit = 4;
                }
                wordLen = 0;
                word[wordLen] = '\0';
            }
            else if (strcmp(word, "five") == 0)
            {
                if (firstDigit == -1)
                {
                    firstDigit = 5;
                    lastDigit = 5;
                }
                else if (firstDigit != -1)
                {
                    lastDigit = 5;
                }
                wordLen = 1;
                word[0] = 'e';
                word[1] = '\0';
            }
            else if (strcmp(word, "nine") == 0)
            {
                if (firstDigit == -1)
                {
                    firstDigit = 9;
                    lastDigit = 9;
                }
                else if (firstDigit != -1)
                {
                    lastDigit = 9;
                }
                wordLen = 1;
                word[0] = 'e';
                word[1] = '\0';
            }
        }
        else if (wordLen == 4 && (c == 'e' || c == 'n' || c == 't'))
        {
            word[wordLen] = c;
            wordLen++;
            word[wordLen] = '\0';
            if (!(strcmp(word, "three") == 0 || strcmp(word, "seven") == 0 || strcmp(word, "eight") == 0))
            {
                wordLen = 1;
                word[0] = c;
                word[1] = '\0';
            }
            if (strcmp(word, "three") == 0)
            {
                if (firstDigit == -1)
                {
                    firstDigit = 3;
                    lastDigit = 3;
                }
                else if (firstDigit != -1)
                {
                    lastDigit = 3;
                }
                wordLen = 1;
                word[0] = 'e';
                word[1] = '\0';
            }
            else if (strcmp(word, "seven") == 0)
            {
                if (firstDigit == -1)
                {
                    firstDigit = 7;
                    lastDigit = 7;
                }
                else if (firstDigit != -1)
                {
                    lastDigit = 7;
                }
                wordLen = 1;
                word[0] = 'n';
                word[1] = '\0';
            }
            else if (strcmp(word, "eight") == 0)
            {
                if (firstDigit == -1)
                {
                    firstDigit = 8;
                    lastDigit = 8;
                }
                else if (firstDigit != -1)
                {
                    lastDigit = 8;
                }
                wordLen = 1;
                word[0] = 't';
                word[1] = '\0';
            }
        }
        else if (wordLen > 0)
        {
            if (c == 'o' || c == 't' || c == 'f' || c == 's' || c == 'e' || c == 'n')
            {
                wordLen = 1;
                word[0] = c;
                word[1] = '\0';
            }
            else
            {
                wordLen = 0;
                word[wordLen] = '\0';
            }
        }
    }

    printf("Sum: %i\n", sum);
}