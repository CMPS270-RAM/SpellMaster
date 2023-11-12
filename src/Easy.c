#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

struct Node {
    char* data;
    struct Node* next;
};

struct Tallier {
    int c;
    char** word;
};

int coinToss (int n) {
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

struct Tallier checkIfDefense(int length, char* read[], char* word) {
    struct Tallier content;
    content.c = 0;
    content.word = (char**)malloc(sizeof(char*));

    char lastLetter = tolower(word[strlen(word) - 1]);

    for (int j = 0; j < length; j++) {
        char firstLetter = tolower(read[j][0]);
        if (firstLetter == lastLetter) {
            content.c++;
            content.word[0] = read[j];
        }
    }

    return content;
}

void checkIfExists(char* read[], char* check[]) {
    int readLength = 0;
    while (read[readLength] != NULL) {
        readLength++;
    }

    struct Node* list = NULL; // Initialize the list
    char lastLetter = tolower(check[0][strlen(check[0]) - 1]);

    for (int j = 0; j < readLength; j++) {
        char firstLetter = tolower(read[j][0]);

        if (firstLetter == lastLetter) {
            // Create a new node and store the matching string
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->data = read[j];
            newNode->next = list;
            list = newNode;
        }
    }

    // Print the list (for checking purposes)
    struct Node* current = list;
    struct Tallier tally[readLength];
    int count = 0;

    while (current != NULL) {
        tally[count] = checkIfDefense(readLength, read, current->data);
        count++;
        current = current->next;
    }

    for (int i = 0; i < count; i++) {
        printf("%s    %d:\n", tally[i].word[0], tally[i].c);
        free(tally[i].word); // Free allocated memory
    }

    
}

int main() {
    char* read[] = {"apple", "banana", "cherry", "date", NULL};
    char* check[] = {"bob"};

    printf("Matching strings:\n");
    checkIfExists(read, check);

    return 0;
}


