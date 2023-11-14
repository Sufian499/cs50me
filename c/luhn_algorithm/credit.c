#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Input number loop
    long n = 0;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 0);
    // counter and vars for the algorithm
    int c = 1;
    long ncopy = n;
    int sum_valor = 0;
    int sum_i = 0;
    int sum_j = 0;
    while (ncopy > 0)
    {
        // Algorithm
        sum_valor = ncopy % 10;
        if (c % 2 == 0 && c > 0)
        {
            sum_valor = sum_valor * 2;
            if (sum_valor >= 10)
            {
                int sum_valor_dec = sum_valor / 10;
                int sum_valor_res = sum_valor % 10;
                sum_i = sum_i + sum_valor_dec + sum_valor_res;
            }
            else
            {
                sum_i = sum_i + sum_valor;
            }
        }
        else
        {
            sum_j = sum_valor + sum_j;
        }
        // Count digits
        ncopy = ncopy / 10;
        c += 1;
    }
    // check algorithm
    c = c - 1;
    int t = sum_i + sum_j;
    t = t % 10;
    // bools for checking all card types
    bool checksum_master = false;
    bool checksum_visa = false;
    bool checksum_amex = false;
    if (t == 0)
    {
        // check visa
        long visacheck = n / 1000000000000;
        long visacheck_ = n / 1000000000000000;
        if (c == 13 || c == 16)
        {
            if (visacheck == 4 || visacheck_ == 4)
            {
                checksum_visa = true;
            }
        }
        // check amex
        long amexcheck = n / 10000000000000;
        if (c == 15)
        {
            if (amexcheck == 34 || amexcheck == 37)
            {
                checksum_amex = true;
            }
        }
        // check MASTERCARD
        long mc_check = n / 100000000000000;
        if (c == 16)
        {
            if (mc_check == 51 || mc_check == 52 || mc_check == 53 || mc_check == 54 || mc_check == 55)
            {
                checksum_master = true;
            }
        }
    }
    // Responses
    if (checksum_master)
    {
        printf("MASTERCARD\n");
    }
    else if (checksum_amex)
    {
        printf("AMEX\n");
    }
    else if (checksum_visa)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
