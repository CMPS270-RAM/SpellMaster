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


char* botEasy (char* read[], char* check, const bool* usedwordList, int readLength, int turn) {

    char lastLetter;
        if (turn != 0) lastLetter = tolower(check[strlen(check) - 1]);

    int nodecount = 0;
    for (int j = 0; j < readLength; j++) {
        char firstLetter = tolower(read[j][0]);
        if ((firstLetter == lastLetter && !usedwordList[j])||turn==0) {
            nodecount++;
        }
    }

    char** list  = (char**)malloc(sizeof(char)*100*nodecount);

    int count = 0;
    for (int j = 0; j < readLength; j++) {
        char firstLetter = firstLetter = tolower(read[j][0]);
        if ((firstLetter == lastLetter && !usedwordList[j])||turn == 0) {
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

