// Program to perform a substitution on a string
// Part of CS50 self-paced work

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

// Contsant variables
const int NUMLETTERS = 26;

// Function Prototypes
int validateKey(string key);

// Main Driver Code
//
// Status: Currently only used for testing supporting functions
int main(void){
    int isValidKey;
    string key;
    do
    {
        key = get_string("Key: ");
        isValidKey = validateKey(key);
    }
    while (isValidKey == 0);

    return EXIT_SUCCESS;
}

// Answers the question
// Is the supplied key valid?
// Checks (1) if the supplied key is the correct length
// and, if so, (2) if all characters in key are unique
//
// Status: Works as expected just so long as all characters in
// key are letters
int validateKey(string key)
{
    // Initialize the frequency table
    int frequency[NUMLETTERS];
    for (int i = 0; i < NUMLETTERS; i++)
    {
        frequency[i] = 0;
    }
    
    int nCharsKey = strlen(key);
    int startIndex = (int) 'a';

    // If the key doesn't have the appropriate number of characters it
    // cannot be considered valid.  This may be premature optimization
    // as it only really saves us time if the input key is very long
    if (nCharsKey == NUMLETTERS)
    {
        // Populate the frequency table for each character, ignoring case
        for (int i = 0; i < nCharsKey; i++)
        {
            char c = key[i];
            char lowerCaseC = tolower(c);
            int offset = (int) lowerCaseC - startIndex;
            if (offset <= NUMLETTERS)
            {
                frequency[offset] += 1;
            }
        }
        // Print the frequency table (for debugging/testing)        
        for (int i = 0; i < nCharsKey; i++)
        {
            char c = (char) (startIndex + i);
            printf("%c: %i\n", c, frequency[i]);
        }

        int allCharsUnique = 1;
        for (int i = 0; i < nCharsKey; i++)
        {
            if (frequency[i] > 1)
                {
                    allCharsUnique = 0;
                }
        }

        return allCharsUnique;
    }
    else
    {
        return 0;
    }
}
