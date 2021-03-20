// Compare the "Scrabble" score of two inputs
// Part of CS50 self-paced work

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

// Custom data types
typedef struct
{
    char letter;
    int score;
}
tile;

// Prototype functions
int scoreWord(string word);

int main(void)
{
    string player1 = get_string("Player 1:");
    string player2 = get_string("Player 2:");
    int player1Score = scoreWord(player1);
    int player2Score = scoreWord(player2);
    if (player1Score > player2Score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player2Score > player1Score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    return EXIT_SUCCESS;
}

int scoreWord(string word)
{
    // Define all possible score values for tiles
    // This takes up more lines, but is (hopefully) easier to read and maintain
    // TODO - Read from external file (e.g. CSV)
    tile tiles[26];
    tiles[0].letter = 'A';
    tiles[0].score = 1;
    tiles[1].letter = 'B';
    tiles[1].score = 3;
    tiles[2].letter = 'C';
    tiles[2].score = 3;
    tiles[3].letter = 'D';
    tiles[3].score = 2;
    tiles[4].letter = 'E';
    tiles[4].score = 1;
    tiles[5].letter = 'F';
    tiles[5].score = 4;
    tiles[6].letter = 'G';
    tiles[6].score = 2;
    tiles[7].letter = 'H';
    tiles[7].score = 4;
    tiles[8].letter = 'I';
    tiles[8].score = 1;
    tiles[9].letter = 'J';
    tiles[9].score = 8;
    tiles[10].letter = 'K';
    tiles[10].score = 5;
    tiles[11].letter = 'L';
    tiles[11].score = 1;
    tiles[12].letter = 'M';
    tiles[12].score = 3;
    tiles[13].letter = 'N';
    tiles[13].score = 1;
    tiles[14].letter = 'O';
    tiles[14].score = 1;
    tiles[15].letter = 'P';
    tiles[15].score = 3;
    tiles[16].letter = 'Q';
    tiles[16].score = 10;
    tiles[17].letter = 'R';
    tiles[17].score = 1;
    tiles[18].letter = 'S';
    tiles[18].score = 1;
    tiles[19].letter = 'T';
    tiles[19].score = 1;
    tiles[20].letter = 'U';
    tiles[20].score = 1;
    tiles[21].letter = 'V';
    tiles[21].score = 4;
    tiles[22].letter = 'W';
    tiles[22].score = 4;
    tiles[23].letter = 'X';
    tiles[23].score = 8;
    tiles[24].letter = 'Y';
    tiles[24].score = 4;
    tiles[25].letter = 'Z';
    tiles[25].score = 10;

    // Now we can use this structure to score a word
    int wordScore = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char uChar = toupper(word[i]);
        int offset = (int) uChar - (int) 'A';
        // Checks that the tile represents a letter
        if ((0 <= offset) && (offset <= 25))
        {
            // This logic isn't strictly necessary (given this program is simple)
            // but serves as a sort of checking mechanism for errors that could arise
            if (uChar == tiles[offset].letter)
            {
                wordScore += tiles[offset].score;
            }
        }
    }

    return wordScore;
}
