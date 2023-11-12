#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Node {
    char* word;
    struct Node* next;
} Node;

Node* store[10]; // Array of linked lists

void CheckIfExists(char** read, char* s[10]) {
    int length = 0;
    while (read[length] != NULL) {
        length++;
    }

    for (int i = 0; i < length; i++) {
        char lastLetter = read[i][strlen(read[i]) - 1];
        char searchKey = tolower(lastLetter);

        for (int j = 0; s[j] != NULL; j++) {
            char firstLetter = tolower(s[j][0]);

            if (searchKey == firstLetter) {
                // Create a new node to store the matching word
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->word = s[j];
                newNode->next = NULL;

                // Add the new node to the linked list
                if (store[i] == NULL) {
                    store[i] = newNode;
                } else {
                    Node* current = store[i];
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = newNode;
                }
            }
        }
    }
}

int main() {
    char* read[] = {"apple", "banana", "cherry", "date", NULL};
    char* s[] = {"elephant", "avocado", "ornament", "elk", "emperor", NULL};

    printf("Testing CheckIfExists function:\n");
    CheckIfExists(read, s);

    // Print the results from the linked lists
    for (int i = 0; i < 10; i++) {
        Node* current = store[i];
        while (current != NULL) {
            printf("Match at i=%d: %s\n", i, current->word);
            current = current->next;
        }
    }

    return 0;
}

