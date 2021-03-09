// Program to check if an input number may represent a valid credit card
// Part of CS50 self-paced work

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>

// Prototype Functions
int countDigits(long toCount);
int getDigit(long toSearch, int index);
int sumDigits(long toSum);
int checkVisa(long toCheck);
int checkMasterCard(long toCheck);
int checkAmericanExpress(long toCheck);
int checkLuhn(long toLuhn);

// Driver program; answers the question
// Is the input number a valid credit card number, and which
// type of card would it be?
int main(void)
{
    long input = get_long("Number: ");
    int luhnValid = checkLuhn(input);
    int isVisa = checkVisa(input);
    int isMasterCard = checkMasterCard(input);
    int isAmericanExpress = checkAmericanExpress(input);

    if (luhnValid == 1)
    {
        if (isVisa == 1)
        {
            printf("VISA\n");
        }
        else if (isMasterCard == 1)
        {
            printf("MASTERCARD\n");
        }
        else if (isAmericanExpress == 1)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return EXIT_SUCCESS;
}


// Count the number of digits in an input number
// TODO - Currently only counts digits to the left of the decimal point
int countDigits(long toCount)
{
    float log_base_ten = log(toCount) / log(10);
    int nDigits = floor(log_base_ten) + 1;
    return nDigits;
}

// Get the digit in the 10^(index) position of toSearch
int getDigit(long toSearch, int index)
{
    long lowerPowerOfTen = powl(10, index);
    long higherPowerOfTen = lowerPowerOfTen * 10;
    long truncLeft = toSearch % higherPowerOfTen;
    int thisDigit = floor(truncLeft / lowerPowerOfTen);
    return thisDigit;
}

// Sum the digits of an input number
int sumDigits(long toSum)
{
    int sum = 0;
    int nDigits = countDigits(toSum);
    for (int i = 0; i < nDigits; i++)
    {
        sum = sum + getDigit(toSum, i);
    }
    return sum;
}

// Checks if the number has characteristics associated with VISA
// (number is 13 or 16 digits, and the digit furthest to the left is 4)
int checkVisa(long toCheck)
{
    int isVisa;
    int nDigits = countDigits(toCheck);
    int firstDigit = getDigit(toCheck, nDigits - 1);
    if (firstDigit == 4 && (nDigits == 13 || nDigits == 16))
    {
        isVisa = 1;
    }
    else
    {
        isVisa = 0;
    }
    return isVisa;
}

// Checks if the number has characteristics associated with MasterCard
// (number is 16 digits, the digit furthest to the left is 5 and the following
// digit is 1, 2, 3, 4, or 5)
int checkMasterCard(long toCheck)
{
    int isMasterCard;
    int nDigits = countDigits(toCheck);
    int firstDigit = getDigit(toCheck, nDigits - 1);
    int secondDigit = getDigit(toCheck, nDigits - 2);
    if (nDigits == 16 && firstDigit == 5 && 
        (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 ||
         secondDigit == 4 || secondDigit == 5))
    {
        isMasterCard = 1;
    }
    else
    {
        isMasterCard = 0;
    }
    return isMasterCard;
}

// Checks if the number has characteristics associated with American Express
// (number is 15 digits, the digit furthest to the left is 3 and the following
// digit is either 4 or 7)
int checkAmericanExpress(long toCheck)
{
    int isAmericanExpress;
    int nDigits = countDigits(toCheck);
    int firstDigit = getDigit(toCheck, nDigits - 1);
    int secondDigit = getDigit(toCheck, nDigits - 2);
    if (nDigits == 15 && firstDigit == 3 && 
        (secondDigit == 4 || secondDigit == 7))
    {
        isAmericanExpress = 1;
    }
    else
    {
        isAmericanExpress = 0;
    }  
    return isAmericanExpress;
}


// Use Luhn's algorithm to determine if the number provided may represent
// a valid credit card number
int checkLuhn(long toLuhn)
{
    int luhnSum = 0;
    int luhnValid;
    int nDigits = countDigits(toLuhn);
    for (int i = 0; i < nDigits; i++)
    {
        int thisDigit = getDigit(toLuhn, i);
        if (i % 2 == 0)
        {
            luhnSum = luhnSum + thisDigit;
        }
        else
        {
            luhnSum = luhnSum + sumDigits(2 * thisDigit);
        }
    }
    
    // If the sum has a zero in the ones place then the input may
    // represent a valid credit card number
    if (getDigit(luhnSum, 0) == 0)
    {
        luhnValid = 1;
    }
    else
    {
        luhnValid = 0;
    }
    return luhnValid;
}
