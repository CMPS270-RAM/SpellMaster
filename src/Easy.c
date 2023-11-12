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




void checkIfExists(char* read[], char* check, const bool* usedwordList, int readLength) {

    char lastLetter = tolower(check[strlen(check) - 1]);

    int nodecount = 0;
    for (int j = 0; j < readLength; j++) {
        char firstLetter = tolower(read[j][0]);
        if (firstLetter == lastLetter && !usedwordList[j]) {
            nodecount++;
        }
    }

    char** list  = (char**)malloc(sizeof(char)*100*nodecount);

    int count = 0;
    for (int j = 0; j < readLength; j++) {
        char firstLetter = tolower(read[j][0]);
        if (firstLetter == lastLetter && !usedwordList[j]) {
            list[count] = read[j];
            count++;
        }
    }

    struct Tallier tally[nodecount];

    for ( int i = 0; i < nodecount; i++ )
        tally[i] = checkIfDefense(readLength, read, list[i], usedwordList);

    int min = tally[0].c;
    for (int i = 0; i < count; i++) {
        if (tally[i].c < min) {
            min = tally[i].c;
        }
    }

    bool winning = false;
    bool defense = true;
    int x = coinToss(2); // Generate a random value for x

    if (count != 0) {
        winning = true;
    }

    if (tally != NULL) {
        defense = true;
    }

    if (defense == false && winning == false) {
        int rand = coinToss(readLength - 1);
        printf("%s\n", read[rand]);
    }

    if (defense == false && winning == true) {
        if (x == 0) {
            int rand = coinToss(readLength - 1);
            printf("%s\n", read[rand]);
        } else if (x == 1) {
            printf("%s\n", tally[0] );
        }
    }

    if (defense == true && winning == true) {
        if (x == 0) {
            printf("%s\n", tally[min].word);
        } else if (x == 1) {
            printf("%s\n",tally[0] );
        }
    }

}







int main() {
    char* read[] = {"apple", "banana", "cherry", "date", "anana", "annana", "elena", "erry", "eat", "ear"};
    char* check = "apple";
    const int readLength = 10;
    bool usedwordList[10];
    for ( int i = 0; i < 10; i++ ) usedwordList[i] = false;

    // Mark some words as used
    usedwordList[0] = true;
    usedwordList[6] = true;
    usedwordList[7] = true;

    // Test checkIfExists
    checkIfExists(read, check, usedwordList, 10);

    return 0;
}





