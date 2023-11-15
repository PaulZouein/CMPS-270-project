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
}


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
     
     fclose(file);
    
    return count; // Return the number of spells loaded
}


  int isValidSpell(char lastLetter, const char* newSpell) 
{
    return (tolower(lastLetter) == tolower(newSpell[0]));
}

void printSpellList(char spells[MAX_SPELLS][MAX_LENGTH], int spellCount) 
{
    for (int i = 0; i < spellCount; ++i) 
    {
        printf("%s\n", spells[i]);
    }
}

int getDifficultyLevel() 
{
    int level;
    printf("Select difficulty level (1 for Easy, 2 for Medium, 3 for Hard): ");
    scanf("%d", &level);
    while ((getchar()) != '\n');  // Clear the input buffer
    return level;
}

void handle_alarm(int sig) 
{
    printf("\nTime's up! You took too long to respond.\n");
    timeout_flag = 1;  // Set the flag to indicate a timeout has occurred
}

void set_alarm(int seconds) 
{
    signal(SIGALRM, handle_alarm); // Set the alarm signal handler
    alarm(seconds); // Set the alarm to go off after the specified seconds
}



