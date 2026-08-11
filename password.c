#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "password.h"

/* ANSI color codes */
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

void getPassword(char password[])
{
    printf("\nEnter Password: ");
    scanf("%99s", password);  // Limit input to 99 characters
}

void analyzePassword(void)
{
    char password[100];

    getPassword(password);

    /* Calculate password length */
    size_t length = strlen(password);

    /* Character counters */
    int uppercase = 0;
    int lowercase = 0;
    int digits = 0;
    int special = 0;

    /* Pattern detection */
    int sequential = 0;
    int sequenceLength = 1;
    int repeatedCharacters = 0;

    /* Character pool used for entropy calculation */
    int poolSize = 0;

    /*
     * Check for sequential characters.
     * Example: abc, 123, 654
     */
    for (size_t i = 1; i < length; i++)
    {
        if (password[i] == password[i - 1] + 1 ||
            password[i] == password[i - 1] - 1)
        {
            sequenceLength++;

            if (sequenceLength >= 3)
            {
                sequential = 1;
            }
        }
        else
        {
            sequenceLength = 1;
        }
    }

    /*
     * Check for repeated consecutive characters.
     * Example: aaa, 111, !!!
     */
    for (size_t i = 1; i < length; i++)
    {
        if (password[i] == password[i - 1])
        {
            repeatedCharacters = 1;
            break;
        }
    }

    /* Analyze character composition */
    for (size_t i = 0; i < length; i++)
    {
        if (isupper(password[i]))
        {
            uppercase++;
        }

        if (islower(password[i]))
        {
            lowercase++;
        }

        if (isdigit(password[i]))
        {
            digits++;
        }

        if (ispunct(password[i]))
        {
            special++;
        }
    }

    /*
     * Calculate character pool size.
     * Lowercase = 26
     * Uppercase = 26
     * Digits    = 10
     * Special   = 32
     */
    if (lowercase > 0)
    {
        poolSize += 26;
    }

    if (uppercase > 0)
    {
        poolSize += 26;
    }

    if (digits > 0)
    {
        poolSize += 10;
    }

    if (special > 0)
    {
        poolSize += 32;
    }

    /* Calculate entropy */
    double entropy = length * log2(poolSize);

    /* Determine strength and rating */
    int stars;
    const char *strength;
    const char *strengthColor;

    if (entropy < 28)
    {
        strength = "Very Weak";
        stars = 1;
        strengthColor = RED;
    }
    else if (entropy < 36)
    {
        strength = "Weak";
        stars = 2;
        strengthColor = RED;
    }
    else if (entropy < 60)
    {
        strength = "Reasonable";
        stars = 3;
        strengthColor = YELLOW;
    }
    else if (entropy < 128)
    {
        strength = "Strong";
        stars = 4;
        strengthColor = GREEN;
    }
    else
    {
        strength = "Very Strong";
        stars = 5;
        strengthColor = GREEN;
    }

    /* Display results */
    
    printf("          PASSWORD ANALYZER             \n");
    
    printf("\n[ PASSWORD ANALYSIS ]\n");
    
    printf("Length              : %zu\n", length);
    printf("Uppercase letters   : %d\n", uppercase);
    printf("Lowercase letters   : %d\n", lowercase);
    printf("Digits              : %d\n", digits);
    printf("Special characters  : %d\n", special);
    printf("Character pool      : %d\n", poolSize);
    printf("Entropy             : %.2f bits\n", entropy);

    printf("\n[ PATTERN ANALYSIS ]\n");
    

    if (sequential)
    {
        printf("Warning: Sequential characters detected\n");
    }
    else
    {
        printf("No sequential pattern detected\n");
    }

    if (repeatedCharacters)
    {
        printf("Warning: Repeated characters detected\n");
    }
    else
    {
        printf("No repeated pattern detected\n");
    }

    printf("\n[ RESULT ]\n");
    
    printf("Strength            : %s%s%s\n",
           strengthColor, strength, RESET);

    printf("Rating              : %s", strengthColor);

    for (int i = 0; i < stars; i++)
    {
        printf("★");
    }

    printf("%s\n", RESET);
    
}