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

struct Tallier checkIfDefense(int length, char* read[], char* word) {
    struct Tallier content;
    content.c = 0;
    content.word = (char**)malloc(sizeof(char*));

    char lastLetter = tolower(word[strlen(word) - 1]);

    for (int j = 0; j < length; j++) {
        char firstLetter = tolower(read[j][0]);
        if ((firstLetter == lastLetter) ) {
            content.c++;
            content.word[0] = read[j];
             printf("%s    %d\n", content.word[0], content.c);
        }
    }

    return content;
}

char* checkIfExists(char* read[], char* check[]) {
    int readLength = 0;
    while (read[readLength] != NULL) {
        readLength++;
    }

    char lastLetter = tolower(check[0][strlen(check[0]) - 1]);

    struct Node* list = NULL; // Initialize the list

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

    struct Node* current = list;
    struct Tallier tally[readLength];
    int count = 0;

    while (current != NULL) {
        tally[count] = checkIfDefense(readLength, read, current->data);
        count++;
        current = current->next;
    }
   char * h = "hello";
    if (count == 0) {
      printf("from no words");
        // No matching words found
        return h;
    }

    int x = coinToss(2);

    if (x == 0) {
      printf("from x = 0");
        return tally[0].word[0]; // Return the first matching string
    } else {
      printf("from else!");
        int randomIndex = coinToss(count);
        return tally[randomIndex].word[0]; // Return a random matching string
    }
}






int main() {
    char* read[] = {"apple", "banana", "cherry", "date", "anana", "annana", NULL};
    char* check[] = {"bob"};

    printf("Matching strings:\n");
    char* result = checkIfExists(read, check);

    if (result == NULL) {
        printf("No matching words found\n");
    } else {
        printf("Matching word: %s\n", result);
    }

    return 0;
}



