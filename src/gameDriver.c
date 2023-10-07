#include "../include/header.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char **spellList = readSpells("./spells.txt");
  int spellCount = readSpellCount("./spells.txt");
  int spellIndex = checkSpells(spellList,spellCount,"0");
  free(spellList);
}
