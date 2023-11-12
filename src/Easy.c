#include "../include/header.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char toLowerCase ( char c ) {
    if ( 65 <= c && c <= 90 ) return c+32;
    return c;
}
char* store[10][10];
void CheckIfExists(char **read, char *s[10]) {//checks if a word is a winning word for the current level & stores it in an array.
    int length = 0;
    while (read[length] != NULL) {
        length++;
    }
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            char lastLetter = read[i][strlen(read[i]) - 1];
            char firstLetter = s[j][0];
            
            if (toLowerCase(lastLetter) == toLowerCase(firstLetter)) {
                store[i][j] = s[j];
                printf("%d",i);
                printf("%s\n",store[i][j]);
            }
        }
    }
}




int main(){
      char *read[] = {"Apple", "Banana", "Cherry", "Date", NULL};
    char *s[] = {"elena", "anana", "herry", "ate", NULL};

    CheckIfExists(read, s);
  
  return 10;
}



