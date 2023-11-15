#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <time.h>



#define MAX_SPELLS 100
#define MAX_LENGTH 50

// Function Prototypes
int loadSpells(const char* filename, char spells[MAX_SPELLS][MAX_LENGTH]); 
int isValidSpell(char lastLetter, const char* spell);
void printSpellList(char spells[MAX_SPELLS][MAX_LENGTH], int spellCount);
int getDifficultyLevel();
void playGame(char spells[MAX_SPELLS][MAX_LENGTH], int spellCount, int difficulty, const char* playerName);
int findSpellIndex(char spells[MAX_SPELLS][MAX_LENGTH], int spellCount, const char* spell);

int main() 
{
  //ill write it at the end.
int loadSpells(const char* filename, char spells[MAX_SPELLS][MAX_LENGTH]) 
{
    FILE *file = fopen(filename, "r");
    if (!file) 
    {
        return -1; // Return -1 if file opening failed
    }

    int count = 0;
    while (count < MAX_SPELLS && fscanf(file, "%49s", spells[count]) == 1) 
    {
        count++;
    }

    
    return count; // Return the number of spells loaded
}

}

