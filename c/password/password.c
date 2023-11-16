// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool lower_pass = false;
    bool upper_pass = false;
    bool number_pass = false;
    bool symbol_pass = false;
    for (int i = 0; password[i] != '\0'; i++)
    {
        if (password[i] >= 'a' && password[i] <= 'z')
        {
            lower_pass = true;
        }
        else if (password[i] >= 'A' && password[i] <= 'Z')
        {
            upper_pass = true;
        }
        else if (password[i] >= '0' && password[i] <= '9')
        {
            number_pass = true;
        }
        else if (password[i] >= '!' && password[i] <= '/')
        {
            symbol_pass = true;
        }
    }
    if (upper_pass == true && lower_pass == true && number_pass == true && symbol_pass == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
