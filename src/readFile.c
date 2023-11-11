#include <stdio.h>
#include<stdlib.h>
#include <string.h>

char** readSpells (char* filePath) {
    FILE *fptr = fopen(filePath,"r");
    
    int spellCount;
    fscanf(fptr,"%d\n",&spellCount);
     
    char** spells=(char**) malloc(spellCount * sizeof(char*));
    char temp[100];
    int count = 0;
    while ( fscanf(fptr, "%s", temp) == 1 ) {
        int len =strlen(temp);
        spells[count] = (char*) malloc(len*sizeof(char));
        strcpy(spells[count],temp);
        count++;
    }

    return spells;
}

int readSpellCount (char* filePath) {
    FILE *fptr = fopen(filePath,"r");
    int spellCount;
    fscanf(fptr,"%d\n",&spellCount);
    return spellCount;
}