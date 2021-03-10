// Attempt at the "More Comfortable" Mario problem
#include <stdio.h>
#include <cs50.h>

// Prints character c to stdout n times
void repeatNTimes(int n, char *c)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s", c);
    }
}

int main(void) 
{
    int nBlocks, validInput = 0;

    while (validInput == 0)
    {
        nBlocks = get_int("Height: ");
        if (nBlocks > 0 && nBlocks < 9)
        {
            validInput = 1;
        }
    }

    for (int i = 0; i < nBlocks; i++)
    {
        int nHash = i + 1;
        int nSpace = nBlocks - nHash;

        repeatNTimes(nSpace, " ");
        repeatNTimes(nHash, "#");
        printf("  ");
        repeatNTimes(nHash, "#");
        printf("\n");
    }

    return 0;
}

