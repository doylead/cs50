// Program to perform a substitution on a string
// Part of CS50 self-paced work

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

// Contsant variables
const int NUMLETTERS = 26;
const int NUMASCII = 128;

// Function Prototypes
int validateKey(string key);

// Main Driver Code
// Assumptions: All characters are ASCII
// 
// Status: Working on developing the encryption mapping
// 
// Output error codes
/// 0 - Success
/// 1 - Incorrect number of command line inputs
/// 2 - Key contains incorrect number of characters
/// 3 - Key contains non-alphabet characters (but has the correct total number of characters)
/// 4 - Key does not contain a one to one mapping for each character
/// Note: Error codes are in some sense consecutive (e.g. if both 2 and 3 apply, 2 will be returned)
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution.out key\n");
        return 1; // See error codes before definition of main
    }

    // Checks to see if the key is valid
    string key = argv[1];
    int isValidKey = validateKey(key);
    if (isValidKey != 0)
    {
        return isValidKey; // See error codes before definition of main
    }

    // Use a valid key to encrypt a message
    // This does not currently use a "helper function" as functions cannot
    // return an array in C

    // Because we've now validated the key, generate a mapping of the form
    // mapping[(int) i] --> j
    // where i is the unencrypted character, and (char) j is the encrypted
    // character
    //
    // Initialize the base array (no encryption)
    int mapping[NUMASCII];
    for (int i = 0; i < NUMASCII; i++)
    {
        mapping[i] = i;
    }

    // Add information from the provided key
    int upperCaseStart = (int) 'A';
    int lowerCaseStart = (int) 'a';
    int offset = 0;
    for (int i = 0; i < NUMLETTERS; i++)
    {
        char c = key[i];
        if (isupper(c) == 0) // Is lowercase
        {
            offset = (int) c - lowerCaseStart;
        }
        else if (islower(c) == 0) // Is uppercase
        {
            offset = (int) c - upperCaseStart;
        }
        mapping[upperCaseStart + i] = upperCaseStart + offset;
        mapping[lowerCaseStart + i] = lowerCaseStart + offset;
    }

    // Ask for the input string to be encrypted
    string unencryptedString = get_string("plaintext: ");

    // Perform the encryption
    int nCharsInput = strlen(unencryptedString);
    char encryptedString[nCharsInput + 1];
    for (int i = 0; i < nCharsInput; i++)
    {
        char unencrypted_c = unencryptedString[i];
        int unencrypted_i = (int) unencrypted_c;
        int encrypted_i = mapping[unencrypted_i];
        char encrypted_c = (char) encrypted_i;
        encryptedString[i] = encrypted_c;
    }
    encryptedString[nCharsInput] = '\0';

    // Output result
    printf("ciphertext: %s\n", encryptedString);

    return EXIT_SUCCESS;
}

// Answers the question
// Is the supplied key valid?
// Warning: "non-void function does not return a value in all control paths"
int validateKey(string key)
{
    // Initialize character frequency table for the key
    int frequency[NUMLETTERS];
    for (int i = 0; i < NUMLETTERS; i++)
    {
        frequency[i] = 0;
    }
    int nCharsKey = strlen(key);
    int startIndex = (int) 'a';
    int allCharsUnique = 1;

    // If the key doesn't have the appropriate number of characters it
    // cannot be considered valid
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

            // Any non-alphabet characters would lead to an invalid key
            if (isalpha(c) == 0)
            {
                return 3; // See error codes before definition of main
            }
        }

        // Checks that each character applies once and only once
        for (int i = 0; i < nCharsKey; i++)
        {
            if (frequency[i] != 1)
            {
                allCharsUnique = 0;
            }
        }
        if (allCharsUnique == 1)
        {
            return 0; // See error codes before definition of main
        }
        else if (allCharsUnique == 0)
        {
            return 4; // See error codes before definition of main
        }
    }
    else
    {
        return 2; // See error codes before definition of main
    }
}
