#include "..\include\header.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char toLowerCase ( char c ) {
    if ( 65 <= c && c <= 90 ) return c+32;
    return c;
}

bool beginsWithLetter(char *spell, char *lastSpell) {
  return toLowerCase(spell[0]) == toLowerCase(lastSpell[strlen(lastSpell) - 1]);
}

bool checkIfSpellsRemain(char** spellList, int spellCount, bool* usedSpells, char* lastSpell) {
    for ( int i = 0; i < spellCount; i++ ) {
        if ( beginsWithLetter(spellList[i], lastSpell) && !usedSpells[i] ) return true;
    }
    return false;
}

int checkSpells(char **spellList, int spellCount, char *spell) {
  return binSearch(spellList, spellCount, spell);
}
