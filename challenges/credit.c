#include <cs50.h>
#include <stdio.h>

int countDigits(unsigned long cardNumber);
string calculateResult(unsigned long banknumber, unsigned long total);

int main(void)
{
    unsigned long cardNumber = get_long("Number: ");
    int count = countDigits(cardNumber);
    string res = "INVALID\n";
    if (count == 15 || count == 16 || count == 13)
    {
        unsigned long lastNumber;
        unsigned long product = 0;
        unsigned long sum = 0;
        unsigned long bankNumber;
        unsigned long tmp;
        unsigned long total;
        
        int timesTwo = 0;

        while (count)
        {  
            lastNumber = cardNumber % 10;
            cardNumber /= 10;
            if (timesTwo)
            {
                tmp = lastNumber * 2;
                product += tmp % 10;
                product += tmp / 10;
                timesTwo = 0;
            }
            else 
            {
                sum += lastNumber;
                timesTwo = 1;
            }
            if (count == 3)
            {
                bankNumber = cardNumber;
            }
            count--;
        }
        total = sum + product; 
        res = calculateResult(bankNumber, total);
        printf("%s", res);
    }
    else
    {
        printf("%s", res);
    }
}

int countDigits(unsigned long cardNumber)
{
    int count = 0;
    unsigned long lastNumber;
    do
    {
        /* Increment digit count */
        count++;
        /* Remove last digit of 'num' */
        cardNumber /= 10;
    } 
    while (cardNumber != 0);
    return count;
}

string calculateResult(unsigned long banknumber, unsigned long total)
{
    if (total % 10 != 0)
    {
        return "INVALID\n";
    }
    else if (banknumber / 10 == 4)
    {
        return "VISA\n";
    }
    else if (banknumber == 34 || banknumber == 37)
    {
        return "AMEX\n";
    }
    else if (banknumber >= 51 && banknumber <= 55)
    {
        return "MASTERCARD\n";
    }
    else 
    {
        return "INVALID\n";
    }
}

