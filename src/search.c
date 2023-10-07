#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
