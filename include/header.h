#include <stdbool.h>

char **readSpells(char *filePath);
int readSpellCount(char *filePath);
int binSearch(char **spellList, int spellCount, char *spell);
bool beginsWithLetter(char *spell, char *lastSpell);
bool checkUsed(char **usedSpellList, int usedSpellCount, char *spell);
int checkSpells(char **spellList, int spellCount, char *spell);
int coinToss (int n);
bool checkIfSpellsRemain(char** spellList, int spellCount, bool* usedSpells, char* lastSpell);
char* botEasy();
char* botMedium(char* spellList[],int spellListCount,const char* prevWord,const bool* usedwordList);
char* botHard();
void game(int numberOfPlayers, int botDifficulty);
