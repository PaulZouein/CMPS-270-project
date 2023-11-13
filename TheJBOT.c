#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SPELLS 100
#define MAX_LENGTH 50

// Global array to store all spells
char allSpells[MAX_SPELLS][MAX_LENGTH];
int allSpellCount = 0; // Counter for the number of spells loaded

// Function Prototypes
int isValidSpell(char lastLetter, const char* spell);
int findSpellIndex(const char* spell);
void loadAllSpells(const char* filename);

// Bot's function for the Battle Royale competition
char* castSpell_pauljads(char** spells, char* previous_spell) {
    static int usedSpells[MAX_SPELLS] = {0};
    char lastLetter = '\0';

    // Determine the last letter of the previous spell, if any
    if (previous_spell != NULL && strlen(previous_spell) > 0) {
        lastLetter = previous_spell[strlen(previous_spell) - 1];
    }

    // Strategy: Choose a spell that the opponent might not be able to counter
    for (int i = 0; i < allSpellCount; i++) {
        if ((!lastLetter || isValidSpell(lastLetter, allSpells[i])) && !usedSpells[i]) {
            // Check if this spell would be difficult for the opponent to counter
            char nextLastLetter = allSpells[i][strlen(allSpells[i]) - 1];
            int counterSpellFound = 0;
            for (int j = 0; j < allSpellCount; j++) {
                if (isValidSpell(nextLastLetter, allSpells[j]) && !usedSpells[j]) {
                    counterSpellFound = 1;
                    break;
                }
            }

            if (!counterSpellFound) {
                usedSpells[i] = 1; // Mark the spell as used
                return allSpells[i];
            }
        }
    }

    // If no strategic spell found, fallback to the first valid spell
    for (int i = 0; i < allSpellCount; i++) {
        if ((!lastLetter || isValidSpell(lastLetter, allSpells[i])) && !usedSpells[i]) {
            usedSpells[i] = 1; // Mark the spell as used
            return allSpells[i];
        }
    }

    return NULL; // No valid spell found
}

// Helper function to load spells from a file
void loadAllSpells(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open spell file.\n");
        exit(1);
    }

    while (allSpellCount < MAX_SPELLS && fscanf(file, "%49s", allSpells[allSpellCount]) == 1) {
        allSpellCount++;
    }

    fclose(file);
}

// Implementation of isValidSpell
int isValidSpell(char lastLetter, const char* newSpell) {
    return (tolower(lastLetter) == tolower(newSpell[0]));
}

// Implementation of findSpellIndex
int findSpellIndex(const char* spell) {
    for (int i = 0; i < allSpellCount; i++) {
        if (strcmp(allSpells[i], spell) == 0) {
            return i;
        }
    }
    return -1; // Spell not found
}

