#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

int convert(string input);
int num = 0;

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    // Get the last char.
    int num_int = 0;
    int len = strlen(input);
    // base case
    if (input == 0)
    {
        return num;
    }
    // god did
    if (input[0] != '\0')
    {
        num_int = input[len - 1] - '0';
        input[len - 1] = '\0';
        convert(input);
    }
    if (num % 10 == 0)
    {
        num = num + num_int;
    }
    else
    {
        num = num * 10;
        num = num + num_int;
    }
    return num;
}
