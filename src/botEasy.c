#include "../include/header.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

struct Node {
    char* data;
    struct Node* next;
};

struct Tallier {
    int c;
    char* word;
};

/*
 * Specifications:
 *
 * pre: 
 * read: should contain the spells that can be played during the game
 * length: should be the length of the read list
 * word: the word to be tallied for next possible plays
 * usedwordList: a boolean list indicating if a word is used or not
 * word must not be empty
 * word should be part of the read list
 * 
 * post:
 * returns a tallier struct with the word that was tallied and the number of possible plays after it
 *
 * Testing:
 *
 * case 1: test with a word with no possible next plays
 * case 2: test with a word that has multiple next plays
 *
 */
struct Tallier checkIfDefense(int length, char* read[], char* word, const bool* usedwordList) {
    struct Tallier content;
    content.c = 0;
    content.word = (char*)malloc(strlen(word)*sizeof(char));
    strcpy(content.word, word);

    int indexOfWord = binSearch(read, length, word);
    char lastLetter = tolower(word[strlen(word) - 1]);
    
    for (int j = 0; j < length; j++) {
        if ( j != indexOfWord ) {
            char initialLetter = tolower(read[j][0]);

            if (initialLetter == lastLetter) {
                if (!usedwordList[j]) {
                    content.c++;
                }
            }
        }
    }

    return content;
}

/*
 * Specifications:
 *
 * pre:
 * read: should contain the spells that can be played during the game
 * readLength: should be the length of the read list
 * check: the previously played word
 * usedwordList: a boolean list indicating if a word is used or not
 * turn: to determine if there was a previous spell or its the first player
 *
 * post:
 * returns a word from the read list
 * case 1: if a winning word exists (no next plays) play it
 * case 2: if no winning word exists randomly plays the word with the highest tally ( hoping that the human doesn't see the win )
 * case 3: or plays the word with the lowest tally ( hoping that the human doesn't find the word )
 *
 * Testing: 
 * case 1: test that it is returning a valid word
 * case 2: test that it is returning a word that has not been played before
 * case 3: test that it is returning the win word if it exists
 * case 4: test that it is returning the word with max or min possible plays if a win word doesn't exist
 *
 */
char* botEasy (char* read[], char* check, const bool* usedwordList, int readLength, int turn) {

    char lastLetter;
        if (turn != 0) lastLetter = tolower(check[strlen(check) - 1]);

    int nodecount = 0;
    for (int j = 0; j < readLength; j++) {
        char firstLetter = tolower(read[j][0]);
        if ( turn != 0 ) {
            if ( firstLetter == lastLetter && !usedwordList[j] ) {
                nodecount++;
            }
        } else nodecount++;
    }

    char** list  = (char**)malloc(sizeof(char)*100*nodecount);

    int count = 0;
    for (int j = 0; j < readLength; j++) {
        char firstLetter = firstLetter = tolower(read[j][0]);
        if ( turn != 0 ) {
            if (firstLetter == lastLetter && !usedwordList[j]) {
                list[count] = read[j];
                count++;
            }} else {
                list[count] = read[j];
                count++;
            }
    }

    struct Tallier tally[nodecount];

    for ( int i = 0; i < nodecount; i++ ){
        tally[i] = checkIfDefense(readLength, read, list[i], usedwordList);
    }

    int maxWordIndex = 0;
    int minWordIndex = 0;
    int min = tally[0].c;
    int max = tally[0].c;
    for (int i = 0; i < count; i++) {
        if (tally[i].c < min) {
            minWordIndex = i;
            min = tally[i].c;
        }
        if (tally[i].c > max) {
            maxWordIndex = i;
            max = tally[i].c;
        }
    }
    
    if ( min == 0 ) {
        return tally[minWordIndex].word;
    }

    int rand = coinToss(2);
    if ( rand == 0 ) {
        return tally[minWordIndex].word;
    } else {
        return tally[maxWordIndex].word;
    }

}

