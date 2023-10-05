#include <stdio.h>
#include<stdlib.h>
#include <string.h>

char** readFile () {
    FILE *fptr = fopen("spells.txt","r");
    
    int spellCount;
    fscanf(fptr,"%d\n",&spellCount);
    printf("count: %d ",spellCount);
     
    char** spells=(char**) malloc(spellCount * sizeof(char*));
    char temp[100];
    int count = 0;
    while ( fscanf(fptr, "%s", temp) == 1 ) {
        int len =strlen(temp);
        spells[count] = (char*) malloc(len*sizeof(char));
        for (int i=0;i<len;i++){
            spells[count][i]=temp[i];
        }
        count++;
    }

    return spells;
}