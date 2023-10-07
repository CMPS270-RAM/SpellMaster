#include <stdbool.h>

char **readSpells(char *filePath);
int readSpellCount(char *filePath);
int binSearch(char **spellList, int spellCount, char *spell);
bool beginsWithLetter(char *spell, char letter);
bool checkUsed(char **usedSpellList, int usedSpellCount, char *spell);
int checkSpells(char **spellList, int spellCount, char *spell);
