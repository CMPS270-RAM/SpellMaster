#include "../include/header.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player {
  int playerNumber;
  char name[30];
  int score;
  int reasonLost;
  bool lost;
};

struct GameStatus {
  struct Player *players[2];
  int currentTurn;
  bool *usedSpells;
  int usedSpellsCount;
  char lastUsedSpell[50];
};

void printSpells(char **spellList, int spellCount) {
  printf("%50s\n", "Spells List");
  printf("%50s\n", "-----------");
  int count = 0;
  for (int i = 0; i < spellCount; i++) {
    if (count < 4) {
      printf("%-20s", spellList[i]);
      count++;
    } else {
      printf("%s\n", spellList[i]);
      count = 0;
    }
  }
  printf("\n");
  for ( int i = 0; i < 100; i++ ) printf("_");
  printf("\n\n");
}

int main() {

  printf("\e[1;1H\e[2J");
  char *reasonsLost[4] = {
      "has no more spells that can be played",
      "used a spell that does't satisfy the matching condition",
      "repeated a previously cast spell", "used an invalid spell"};

  char **spellList = readSpells("./spells.txt");
  int spellCount = readSpellCount("./spells.txt");

  struct Player p1;
  p1.playerNumber = 1;
  p1.score = 0;
  p1.lost = 0;
  printf("Player %i, Enter your name: ", p1.playerNumber);
  scanf("%s", p1.name);

  struct Player p2;
  p2.playerNumber = 2;
  p2.score = 0;
  p2.lost = 0;
  printf("Player %i, Enter your name: ", p2.playerNumber);
  scanf("%s", p2.name);

  struct GameStatus game;
  game.players[0] = &p1;
  game.players[1] = &p2;
  game.currentTurn = coinToss(2);
  game.usedSpellsCount = 0;
  game.usedSpells = malloc(sizeof(bool) * spellCount);
  for ( int i = 0; i < spellCount; i++ ) game.usedSpells[i] = false;

  printf("\e[1;1H\e[2J");
  printSpells(spellList, spellCount);
  printf("%s Starts\n", game.players[game.currentTurn]->name);

  while (!p1.lost && !p2.lost) {

    if (game.usedSpellsCount > 0) {
      printf("\e[1;1H\e[2J");
      printSpells(spellList, spellCount);
      printf("%s chooses: %s\n", game.players[abs(game.currentTurn - 1)]->name,
             game.lastUsedSpell);
    }

    printf("%s chooses: ", game.players[game.currentTurn]->name);
    char spell[50];
    scanf("%s", spell);

    if (game.usedSpellsCount != 0) {
      if (!beginsWithLetter(spell, game.lastUsedSpell)) {
        game.players[game.currentTurn]->lost = true;
        game.players[game.currentTurn]->reasonLost = 1;
      }
    } else {
      strcpy(game.lastUsedSpell, spell);
    }

    int spellIndex = checkSpells(spellList, spellCount, spell);
    if (spellIndex == -1) {
      game.players[game.currentTurn]->lost = true;
      game.players[game.currentTurn]->reasonLost = 3;
    }

    if (spellIndex != -1 && game.usedSpells[spellIndex]) {
      game.players[game.currentTurn]->lost = true;
      game.players[game.currentTurn]->reasonLost = 2;
    }

    if (game.players[game.currentTurn]->lost) {
      printf("%s won (%s %s)\n", game.players[(game.currentTurn + 1) % 2]->name,
             game.players[game.currentTurn]->name,
             reasonsLost[game.players[game.currentTurn]->reasonLost]);
    } else {
      strcpy(game.lastUsedSpell, spell);
      game.usedSpells[spellIndex] = 1;
      game.usedSpellsCount++;
      game.currentTurn = (game.currentTurn + 1) % 2;
      if (!checkIfSpellsRemain(spellList, spellCount, game.usedSpells,
                               game.lastUsedSpell)) {
        game.players[game.currentTurn]->lost = true;
        game.players[game.currentTurn]->reasonLost = 0;
        printf("%s won (%s %s)\n",
               game.players[(game.currentTurn + 1) % 2]->name,
               game.players[game.currentTurn]->name,
               reasonsLost[game.players[game.currentTurn]->reasonLost]);
      }
    }
  }

  for (int i = 0; i < spellCount; i++)
    free(spellList[i]);
  free(spellList);
  free(game.usedSpells);
}
