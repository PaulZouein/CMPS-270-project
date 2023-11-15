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

void playGame(char spells[MAX_SPELLS][MAX_LENGTH], int spellCount, int difficulty, const char* playerName) 
{
    // Variables to keep track of game state
    int playerTurn = 1; // 1 for player, 0 for computer
    char lastSpell[MAX_LENGTH] = {0};
    int usedSpells[MAX_SPELLS] = {0}; // To mark spells that have been used
    int timeLimit;
    
    // Set time limit based on difficulty
    switch (difficulty) 
    {
        case 1: timeLimit = 30; 
            printf("You have chosen Easy difficulty. You have 30 seconds per turn. Hurry up!\n"); 
                break; // Easy - 30 seconds

        case 2: timeLimit = 20; 
            printf("You have chosen Medium difficulty. You have 20 seconds per turn. Hurry up!\n");
                 break; // Medium - 20 seconds

        case 3: timeLimit = 10; 
            printf("You have chosen Hard difficulty. You have 10 seconds per turn. Hurry up!\n"); 
                break; // Hard - 10 seconds

        default: timeLimit = 30; 
            printf("Invalid input, by default you'll play on Easy difficulty. You have 30 seconds per turn. Hurry up!\n");
                break; // Default to easy if invalid input - 30 seconds
    }
    
    // Seed the random number generator
    srand((unsigned int)time(NULL));
    
    // Set up signal handler for the alarm
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handle_alarm;
    sigaction(SIGALRM, &sa, NULL);

    // Game loop
    while (1) 
    {
        char currentSpell[MAX_LENGTH];
        
        // Reset timeout flag
        timeout_flag = 0;
        
        // Player's turn
        if (playerTurn) 
        {
            printf("Your turn, enter a spell: ");
            fflush(stdout);  // Make sure the prompt is printed immediately
            
            // Set an alarm to go off after the specified time limit
            alarm(timeLimit);
            
            // Get player's spell
            if (scanf("%49s", currentSpell) <= 0 || timeout_flag) 
            {
                if(timeout_flag) 
                {
                    printf("%s, you lose! Computer wins!\n", playerName);
                } 
                
                else 
                {
                    printf("%s, you lose! Computer wins!\n", playerName);
                }

                break;  // Exit the game loop if input fails or time is up
            }
            
            // Cancel the alarm if input was successful
            alarm(0);

        int spellIndex = findSpellIndex(spells, spellCount, currentSpell);

       
    if(spellIndex == -1 || usedSpells[spellIndex] || (lastSpell[0] != '\0' && !isValidSpell(lastSpell[strlen(lastSpell) - 1], currentSpell))) {
        printf("%s, invalid or repeated spell or wrong starting letter. You lose! Computer wins!\n", playerName);
        break;
    }

    // Mark the spell as used
    usedSpells[spellIndex] = 1;


               // Check if the spell exists in the spell list and is valid
        if((findSpellIndex(spells, spellCount, currentSpell) == -1) || (lastSpell[0] != '\0' && !isValidSpell(lastSpell[strlen(lastSpell) - 1], currentSpell))) 
        {
         printf("%s, First spell letter is wrong. You lose! Computer wins!\n", playerName);
         break;
        }
            
            // Check the player's spell (last letter validation)
        if(lastSpell[0] != '\0' && !isValidSpell(lastSpell[strlen(lastSpell) - 1], currentSpell)) 
        {
            printf("Invalid spell. You lose!\n");
            break;
        }
            
        } 
        else 
        {
            // Computer's turn 
            int found = 0;
            for (int i = 0; i < spellCount && !found; i++) 
            {
                if (!usedSpells[i] && isValidSpell(lastSpell[strlen(lastSpell) - 1], spells[i])) 
                {
                    strcpy(currentSpell, spells[i]);
                    printf("Computer's spell: %s\n", currentSpell);
                    found = 1;
                }
            }

    int spellIndex = findSpellIndex(spells, spellCount, currentSpell);

    if (usedSpells[spellIndex]) 
    {
        printf("Computer cannot find a valid spell. Computer loses!\n");
        break;
    }

    // Mark the spell as used
    usedSpells[spellIndex] = 1;


            if (!found) 
            {
                printf("Computer cannot find a valid spell. Computer loses!\n");
                break;
            }
    }
         
        // Update game state
        strcpy(lastSpell, currentSpell);
        usedSpells[findSpellIndex(spells, spellCount, currentSpell)] = 1; // Mark spell as used
        playerTurn = !playerTurn; // Switch turns
    }
}

  int findSpellIndex(char spells[MAX_SPELLS][MAX_LENGTH], int spellCount, const char* spell) 
{
    for (int i = 0; i < spellCount; i++) 
    {
        if (strcmp(spells[i], spell) == 0) 
        {
            return i;
        }
    }
    return -1; // If spell not found, return -1
}

