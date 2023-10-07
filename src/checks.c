#include "../include/header.h"
#include <stdbool.h>
#include <stdio.h>

bool beginsWithLetter(char *spell, char letter) {
    return spell[0] == letter;
}

bool checkUsed(char **usedSpellList, int usedSpellCount, char *spell) {
  return binSearch(usedSpellList, usedSpellCount, spell) == 0;
}

int checkSpells(char **spellList, int spellCount, char *spell) {
  return binSearch(spellList, spellCount, spell);
}
