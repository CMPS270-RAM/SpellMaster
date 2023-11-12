#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
void wordsStartingWithLetter(const char* spellList[], int wordCount, char targetLetter, const char* options[]) {
    //pre - conditions : 
    //post - conditions : 
    int resultCount = 0; 
    for(int i = 0; i < wordCount; i++) {
        if (spellList[i][0] == targetLetter) {
            options[resultCount] = spellList[i];
            resultCount++;
        }
    }
}
void collectMatchingWords(const char* wordList[], int wordListCount, const char* possibleWords[], int possibleWordsCount, int* result[]) {
    //pre-cond: 
    //post-cond:
    int resultCount = 0;
    for (int i = 0; i < possibleWordsCount; i++) {
        const char* targetWord = possibleWords[i];
        char lastLetter = targetWord[strlen(targetWord) - 1];

        for (int j = 0; j < wordListCount; j++) {
            const char* currentWord = wordList[j];
            if (currentWord[0] == lastLetter) {
                result[i]++;
            }
        }
    }
}
int  findMinAndSecondMin(const int arr[], int size) {
    //pre:
    //post
    int min =  INT_MAX;// Initialize min to a large value
    int secondMin = INT_MAX;// 

    for (int i = 0; i < size; i++) {
        if (arr[i] < min) {
            secondMin = min; 
            min = arr[i]; 
        } else if (arr[i] < secondMin && arr[i] != min) {
            secondMin = arr[i]; 
    }
    if (min==1){
        return secondMin;
    }
    return min;
}
}