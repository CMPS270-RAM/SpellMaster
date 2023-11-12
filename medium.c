#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
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
void collectMatchingWords(const char* spellList[], int spellListCount, const char* options[], int optionsCount, int* result[]) {
    //pre-cond: 
    //post-cond:
    int resultCount = 0;
    for (int i = 0; i < optionsCount; i++) {
        const char* targetWord = options[i];
        char lastLetter = targetWord[strlen(targetWord) - 1];

        for (int j = 0; j < spellListCount; j++) {
            const char* currentWord = spellList[j];
            if (currentWord[0] == lastLetter) {
                result[i]++;
            }
        }
    }
}
void creatTally(const char* spellList[],int spellListCount,const char* usedwordList[],int usedwordListCount,int *tally,int tallySize){
    for (int i = 0; i < tallySize; i++) {
        tally[i] = 0;
    }
    for (int i = 0; i < spellListCount; i++) {
        const char *word = spellList[i];
    
        //need to change word  to lowercase.

        int used = 1;//word not in used 
        for (int j=0;j<usedwordListCount;j++){
            int used = strcmp(word, usedwordList[j]);
            if (used==0){
            //word is ALREADY USED 
             break;
            }
        }
        if (used==1){//not used -> add it to tally
        int index = tolower(word[0]) - 'a';
        tally[index]++;
        }
    }
}
char* functMedium(const char* spellList[],int spellListCount,const char* prevWord,const char* usedwordList[],int usedwordListCount){
    int* tally = (int*)malloc(27 * sizeof(int));
    tally=creatTally(spellList,spellListCount,usedwordList,usedwordListCount,tally,27)
    char lastLetter = prevWord[strlen(prevWord) - 1];
    for (int i = 0; i < spellListCount; i++) {
        char *word = spellList[i];
        //IF WINING WORD :
        if(word[0]==lastLetter&&tally[tolower(word[strlen(word) - 1])-'a']==0){
            return word;
        }
        //IF NOT WIINING WORD CHECK IF DEFENSE 
        else if(word[0]==lastLetter){
            bool noLose=true;
            //int last = tolower(lastLetter)-'a';
            for (int j = 0; j < spellListCount; i++) {
                char *word2 = spellList[i];
                if(tally[tolower(word2[strlen(word2) - 1])-'a']==0){
                    noLose=false;
                    break;
                }
                return word;
            }
        }   
    }
    //if word neither defense nor winning :
    char *min_word;
    char* max_word;
    int max=INT_MIN;
    int min=INT_MAX;
    for (int i = 0; i < spellListCount; i++) {
        char *word = spellList[i];
        if(word[0]==lastLetter){
            if(tally[tolower(word[strlen(word) - 1])-'a']>max){
                max=tally[tolower(word[strlen(word) - 1])-'a'];
                max_word=word;
            }
            if(tally[tolower(word[strlen(word) - 1])-'a']<min){
                min=tally[tolower(word[strlen(word) - 1])-'a'];
                min_word=word;
            }
        }
        //return either minword or maxword
    }

}

