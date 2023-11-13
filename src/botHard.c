#include "../include/header.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  int data;
  struct Node *next;
};

void insertNode(int i, struct Node **start) {
  struct Node *node = malloc(sizeof(struct Node));
  if (node != NULL) {
    node->data = i;
    node->next = NULL;

    struct Node *previousNode = NULL;
    struct Node *currentNode = *start;
  
    while (currentNode != NULL && currentNode->data < i) {
      previousNode = currentNode;
      currentNode = currentNode->next;
    }
  
    if (previousNode != NULL) {
      previousNode->next = node;
      node->next = currentNode;
    } else {
      node->next = currentNode;
      *start = node;
    }
  } else
    puts("No available memory! Node not inserted!");
}

void deleteNode(int i, struct Node **start) {
  struct Node *current = *start;
  struct Node *previous = NULL;
  while (current != NULL && current->data != i) {
    previous = current;
    current = current->next;
  }
  if (current == NULL)
    return;
  else if (current == *start) {
    struct Node *temp = *start;
    *start = (*start)->next;
    free(temp);
  } else {
    previous->next = current->next;
    free(current);
  }
}

bool isEmpty(struct Node *start) { return start == NULL; }

void printGraph ( int spellCount, char** spellList, struct Node** graph ) {
  for ( int i = 0; i < spellCount; i++ ) {
      printf( "%s: ", spellList[i]);
      struct Node *cur = graph[i];
      while ( cur != NULL ) {
        printf("%s, ", spellList[cur->data]);
        cur = cur->next;
      } 
      printf("\n");
  }
}

void printList ( struct Node * start, char**spellList ) {
    printf("list => ");
    struct Node *cur = start;
    while ( cur != NULL ) {
        printf("%s => ", spellList[cur->data]);
        cur = cur->next;
    }
}

struct PathStats {
    double wins;
    double loses;
};

double recCount = 0;

/*
 * (In our implementation we still have an unresolved issue with this function so it is sadly not preforming as it should ;-;)
 * Specifications:
 * pre:
 * outWords: a linked list of the possible outgoing words that can be played
 * graph: a directional graph (implemented using a two dimensional adj list) with all the node connections
 * spellList: a list of all the possble words\spells that can be played
 * usedSpells: a boolean list indicating which spells have been played already
 * spellCount: the total number of spells
 * turn: indicating which turn the function is currently on
 *
 * post:
 * if there are no outWords it is expected to return who would win with that word based on the turn and count that as a loss or a wins
 * if there are outWords the function is expected to simulate playing the word by removing it from the graph and repeat the function call on its possible outWords
 * which will all be added up to find and return the possible number of wins and loses for each possible path
 *
 * Testing:
 * case 1: test with no outWords and it should return a PathStats struct (simply a count for wins and losses) with one win or lose depending on the turn
 * case 2: test with a simple graph and insure that it is going through all the possible paths and returning the right number of possible wins and losses for each path
 *
 */
struct PathStats getPathStats ( struct Node *outWords, struct Node **graph, char**spellList, bool *usedSpells, const int spellCount, int turn ) {
    
    recCount ++;
    double maxRec = 1000000.0;
    if ( recCount > maxRec ) {
        struct PathStats stats;
        stats.wins = 0;
        stats.loses = 0;
        return stats;
    }


    if ( isEmpty( outWords ) ) {

        struct PathStats stats;
        stats.wins = 0;
        stats.loses = 0;

        if ( turn%2 == 0 ) stats.wins++;
        else stats.loses++;

        return stats;

    } else {

        int numOutGoing = 0;
        struct Node *cur = outWords;
        while ( cur != NULL ) {
            numOutGoing++;
            cur = cur->next;
        }

        struct PathStats results [numOutGoing];
        int spellsOutGoing [numOutGoing]; 

        int count = 0;
        cur = outWords;
        while ( cur != NULL ) {
            spellsOutGoing[count] = cur->data;
            count++;
            cur = cur->next;
        }

        for ( int i = 0; i < numOutGoing; i++ ) {

                struct Node *temp = graph[spellsOutGoing[i]];
                graph[spellsOutGoing[i]] = NULL;
                for ( int j = 0; j < spellCount; j++ ) {
                    deleteNode(spellsOutGoing[i], &graph[j]);
                }
                usedSpells[spellsOutGoing[i]] = true;

                results[i] = getPathStats(temp, graph, spellList, usedSpells, spellCount, turn+1);

                graph[spellsOutGoing[i]] = temp;
                for (int j = 0; j < spellCount; j++) {
                    if ( !usedSpells[j] && spellsOutGoing[i] != j && beginsWithLetter(spellList[spellsOutGoing[i]],spellList[j])) {
                        insertNode(spellsOutGoing[i], &graph[j]);
                    }
                }
                usedSpells[spellsOutGoing[i]] = false;

        }

        struct PathStats StatsSum;
        StatsSum.wins = 0;
        StatsSum.loses = 0;
        for ( int i = 0; i < numOutGoing; i++ ) {
            StatsSum.wins  += results[i].wins;
            StatsSum.loses += results[i].loses;
        }

        return StatsSum;
    }
}

/*
 * Specifications:
 * pre:
 * spellList: a list of all the possble words\spells that can be played
 * usedSpells: a boolean list indicating which spells have been played already
 * spellCount: the total number of spells
 * previousSpell: the previously played spell so that we know the possible next words to play  
 * turn: indicating whether this is the first turn or not
 *
 * post:
 * to return the next play which puts you on the path with the least loses
 * it builds the graph and uses the previous word to find out what are the possible next plays and starts the recursive calls to find which is the best path:w
 *
 * Testing:
 * case 1: test with an empty graph
 * case 2: test with a graph that has an obvious win path 
 * case 3: test with a graph that has an obvious lose path
 * case 4: test that a valid and unplayed word is returned
 *
 */

char *botHard( char **spellList, const int spellCount, const bool *usedSpells, const char *previousSpell, int turn) {

  struct Node *graph [spellCount];
  bool usedSpellsCopy[spellCount];
  for ( int i = 0; i < spellCount; i++ ) usedSpellsCopy[i] = usedSpells[i];

  for (int i = 0; i < spellCount; i++) {
      graph[i] = NULL;
      if (!usedSpells[i]) {
          for (int j = 0; j < spellCount; j++) {
              if (i != j && !usedSpells[j] && beginsWithLetter(spellList[j], spellList[i])) {
                  insertNode(j, &graph[i]);
              }
          }
      }
  }

  int possiblePlaysCount = 0;
  int possiblePlays [spellCount];
  struct PathStats possiblePlayStats[spellCount];

  if ( turn > 0 ) {
      for (int i = 0; i < spellCount; i++) {
          if ( !usedSpells[i] && beginsWithLetter(spellList[i], previousSpell)) {
              possiblePlays[possiblePlaysCount] = i;
              possiblePlaysCount++;
          }
      }
  } else {
      for (int i = 0; i < spellCount; i++) {
          possiblePlays[possiblePlaysCount] = i;
          possiblePlaysCount++;
      }
  }

  for ( int i = 0; i < possiblePlaysCount; i++ ) {

      struct Node *temp = graph[possiblePlays[i]];
      graph[possiblePlays[i]] = NULL;
      for ( int j = 0; j < spellCount; j++ ) {
          deleteNode(possiblePlays[i], &graph[j]);
      }
      usedSpellsCopy[possiblePlays[i]] = true;

      possiblePlayStats[i] = getPathStats ( temp, graph, spellList, usedSpellsCopy, spellCount, 0 );

      graph[possiblePlays[i]] = temp;
      for (int j = 0; j < spellCount; j++) {
          if ( !usedSpellsCopy[j] && possiblePlays[i]!=j && beginsWithLetter(spellList[possiblePlays[i]], spellList[j])) {
              struct Node *start = graph[j];
              insertNode(possiblePlays[i], &graph[j]);
          }
      }
      usedSpellsCopy[possiblePlays[i]] = false;
  }

  double minLoses = pow(2, 64);
  int minLosesWord = -1;

  for ( int i = 0; i < possiblePlaysCount; i++ ) {
      if ( possiblePlayStats[i].loses < minLoses ) {
          minLoses = possiblePlayStats[i].loses;
          minLosesWord = i;
      }
  }

  return spellList[possiblePlays[minLosesWord]];
}




