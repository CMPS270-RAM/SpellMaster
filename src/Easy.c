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

int coinToss(int n) {
    time_t t1;
    srand((unsigned)time(&t1));
    int random = rand() % n;

    return random;
}

int min ( int i1, int i2 ) {
    if ( i1 < i2 ) return i1;
    return i2;
}

int compareStrings ( char* w1, char* w2 ) {
    for ( int i = 0; i < min(strlen(w1), strlen(w2)); i++ ) {
        char l1 = w1[i];
        char l2 = w2[i];
        if ( 65 <= l1 && l1 <= 90 ) l1 += 32;
        if ( 65 <= l2 && l2 <= 90 ) l2 += 32;
        if ( l1 < l2 ) return -1;
        if ( l1 > l2 ) return 1;
    }
    if ( strlen(w1) < strlen(w2) ) return -1;
    if ( strlen(w1) > strlen(w2) ) return 1;
    return 0; 
}

int binSearch ( char** spellList, int spellCount, char* spell ) {
    int lower = 0;
    int upper = spellCount-1;
    while ( lower <= upper ) {
        int mid = lower + ((upper-lower)/2);
        int comp = compareStrings(spell, spellList[mid]);
        if ( comp == 0 ) return mid;
        if ( comp > 0 ) lower = mid + 1;
        else upper = mid - 1;
    }
    return -1;
}

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




char* checkIfExists(char* read[], char* check, const bool* usedwordList, int readLength, int turn) {

    char lastLetter = tolower(check[strlen(check) - 1]);

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
        char firstLetter = tolower(read[j][0]);
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

    if ( min == 0 ) return tally[minWordIndex].word;

    int rand = coinToss(2);
    if ( rand == 0 ) return tally[minWordIndex].word;
    else return tally[maxWordIndex].word;

}







int main() {
    char* read[] = {"apple", "banana", "yaya", "date", "anana", "annana", "elena", "erry", "eel", "ear", "leen", "raa"};
    char* check = "apple";
    const int readLength = 12;
    bool usedwordList[12];
    for ( int i = 0; i < 12; i++ ) usedwordList[i] = false;

    // Mark some words as used
    usedwordList[0] = true;
    usedwordList[6] = true;

    // Test checkIfExists
    printf( "%s", checkIfExists(read, check, usedwordList, 12, 0));

    return 0;
}





