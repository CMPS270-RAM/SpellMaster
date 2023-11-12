#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Node {
    char* data;
    struct Node* next;
};

void toLowerCase(char* str) {
    while (*str != '\0') {
        *str = tolower(*str);
        str++;
    }
}

void checkIfExists(char*read[], char* check[]) {
    int readLength = 0;
    while (read[readLength] != NULL) {
        readLength++;
    }

    struct Node* list = NULL; // Initialize the list
    int last = 0;
    for (int i = 0; check[i] != '\0'; i++) {//checks to make sure that the last element of "check"is not "NULL"
         last =i;
    }
    last =last- 1;
        for (int j = 0; j < readLength; j++) {
            char firstLetter = tolower(read[j][0]);
            char lastLetter = tolower(check[0][last-1]);

            if (firstLetter == lastLetter) {
                // Create a new node and store the matching string
                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode->data = read[j];
                newNode->next = list;
                list = newNode;
            }
        }
    

    // Print the list(for checking purposes)
    struct Node* current = list;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main() {
    char* read[] = {"apple", "banana", "cherry", "date", NULL};
    char* check[] = {"bob"};

    printf("Matching strings:\n");
    checkIfExists(read, check);

    return 0;
}


