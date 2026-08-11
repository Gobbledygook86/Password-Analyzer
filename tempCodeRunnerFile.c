#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "password.h"

void getPassword(char password[])
{
    printf("Enter Password: ");
    scanf("%99s", password); // Limit
}

void analyzePassword(void)
{
    char password[100];

    getPassword(password);

    size_t length = strlen(password);

    int uppercase=0;
    int lowercase=0;
    int digits=0;
    int special=0;

    for(int i=0; i<length; i++)
    {
        if(isupper(password[i]))
            uppercase++;
         if(islower(password[i]))
            lowercase++;
         if(isdigit(password[i]))
            digits++;
         if(ispunct(password[i]))
            special++;
    }

    printf("\nYou enetered: %s\n",password);
    printf("Password length: %zu\n", length);
    printf("Uppercase letters: %d\n", uppercase);
    printf("Lowercase letters: %d\n", lowercase);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", special);
}