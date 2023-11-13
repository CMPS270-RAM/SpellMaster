#include <stdbool.h>

char **readSpells(char *filePath);
int readSpellCount(char *filePath);
int binSearch(char **spellList, int spellCount, char *spell);
bool beginsWithLetter(char *spell, char *lastSpell);
bool checkUsed(char **usedSpellList, int usedSpellCount, char *spell);
int checkSpells(char **spellList, int spellCount, char *spell);
int coinToss (int n);
bool checkIfSpellsRemain(char** spellList, int spellCount, bool* usedSpells, char* lastSpell);
char* botEasy(char* read[], char* check, const bool* usedwordList, int readLength, int turn);
char* botMedium();
char* botHard();
void game(int numberOfPlayers, int botDifficulty);
