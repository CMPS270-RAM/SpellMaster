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
    char** word;
};

int coinToss(int n) {
    time_t t1;
    srand((unsigned)time(&t1));
    int random = rand() % n;

    return random;
}

void toLowerCase(char* str) {
    while (*str != '\0') {
        *str = tolower(*str);
        str++;
    }
}

struct Tallier checkIfDefense(int length, char* read[], char* word, const bool* usedwordList) {
    struct Tallier content;
    content.c = 0;
    content.word = (char**)malloc(sizeof(char*));

    char firstLetter = tolower(word[strlen(word) - 1]);
    
    for (int j = 0; j < length; j++) {
        char initialLetter = tolower(read[j][0]);
        
        if (initialLetter == firstLetter) {
            if (usedwordList[j] == false) {
                content.c++;
                content.word[0] = (char*)malloc(strlen(read[j]) + 1);
                strcpy(content.word[0], read[j]);
            }
        }
    }

    return content;
}




void checkIfExists(char* read[], char* check[], const bool* usedwordList) {
    int readLength = 0;
    while (read[readLength] != NULL) {
        readLength++;
    }

    char lastLetter = tolower(check[0][strlen(check[0]) - 1]);

    struct Node* list = NULL;
    int nodecount = 0;
    for (int j = 0; j < readLength; j++) {
        char firstLetter = tolower(read[j][0]);

        if (firstLetter == lastLetter && !usedwordList[j]) {
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            if (usedwordList[j] == false) {
                newNode->data = read[j];
                newNode->next = list;
                list = newNode;
                nodecount++;
            }
        }
    }

    struct Node* current = list;
    struct Tallier tally[readLength];
    int count = 0;

    while (current != NULL) {
        tally[count] = checkIfDefense(readLength, read, current->data, usedwordList);
        count++;
        current = current->next;
    }
    struct Node* c = list;
     char* win [count];
     int i = 0;
     while(c != NULL){
      win [i++] = c->data;
      c = c->next;
     }

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
            printf("%s\n", win[0] );
        }
    }

    if (defense == true && winning == true) {
        if (x == 0) {
            printf("%s\n", tally[min].word[0]);
        } else if (x == 1) {
            printf("%s\n",win[0] );
        }
    }

}







int main() {
    char* read[] = {"apple", "banana", "cherry", "date", "anana", "annana", "elena", "erry", "eat", "ear", NULL};
    char* check[] = {"apple"};
    const int readLength = 10;
    bool usedwordList[10];

    // Mark some words as used
    usedwordList[0] = true;
    usedwordList[6] = true;
    usedwordList[7] = true;

    // Test checkIfExists
    checkIfExists(read, check, usedwordList);

    return 0;
}





