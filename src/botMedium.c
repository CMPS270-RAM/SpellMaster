#include "../include/header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>

void creatTally(char* spellList[],int spellListCount,const bool* usedwordList,int *tally,int tallySize){
    /*  pre:    spell list must be passed along with its size 
                tally must be created in the function calling this one 
                usedword list must be passed

        post:   will return a list representing the number of words available starting with each letter of the alphabet

        testing : 
            case1:-passing array with multiple words where some start with same letter 
                 should return numbering correctly 
                  
    */
    for (int i = 0; i < tallySize; i++) { //initialize tally to zeros 
        tally[i] = 0;
    }

    for (int i = 0; i < spellListCount; i++) {
        const char *word = spellList[i];
        //if word is not used add it to tally
        if(usedwordList[i]==false){
            int index = tolower(word[0]) - 'a';
            tally[index]++;
        }
    }
}
char* botMedium(char* spellList[],int spellListCount,char* prevWord,bool* usedwordList){
    /* pre: the list of words along with its size 
            the prev word played 
            the usedwords list 
        post: 
        will return the winning word with no more chances for player to play if possible 
        will return a word that helps gauaranteeing not losing in case the first option doesnt exsist
        will return a word with min or max following words to be played if neither winning or defense words exsist
    
        testing: 
        case1: -make sure it doesnt return a used word
        case2: -make sure chosen word is valid (starts with last letter of prev word)
        case3: -make sure it choses the WIN word by checking tally = 0 if it exists 
        case4: -make sure it choses a defense word in case first case doesnt exist 
        case5:- make sure it choses either a min or max word in case win and defense dont exist 
    */
    
    int* tally = (int*)malloc(27 * sizeof(int));
    creatTally(spellList,spellListCount,usedwordList,tally,27);
    char lastLetter= prevWord[strlen(prevWord) - 1];
    //check if winning word exsists and return it if it does
    for (int i = 0; i < spellListCount; i++) {
        char *current = spellList[i];
        if(current[0]==lastLetter && tally[tolower(current[strlen(current) - 1])-'a']==0 && usedwordList[i]==false){
            return current;
        }
    }

    // check if defense word exsists and return it if its safe
    for (int i = 0; i < spellListCount; i++) {
        char *current2 = spellList[i];
        if((current2[0]==lastLetter && usedwordList[i]==false)){
            bool noLose=true;
            char last= current2[strlen(current2) - 1];
            for (int k = 0; k < spellListCount; k++) {
                char *current3 = spellList[k];
                if(tally[tolower(current3[strlen(current3) - 1])-'a'] == 0){
                    noLose=false;
                    break;
                }
                return current2; //its a word that wont make u lose 
            }
        }   
    }

    // check the min and max words and chose one randomly as your last option
    char* min_word;
    char* max_word;
    int max=INT_MIN;
    int min=INT_MAX;
    for (int i = 0; i < spellListCount; i++) {
        char *lastopt = spellList[i];
        if(lastopt[0] == lastLetter && usedwordList[i]==false){
            //word with max number of next options
            if(tally[tolower(lastopt[strlen(lastopt) - 1])-'a'] > max){
                max = tally[tolower(lastopt[strlen(lastopt) - 1])-'a'];
                max_word = lastopt;
            }
            //word with min num of next options
            if(tally[tolower(lastopt[strlen(lastopt) - 1])-'a']< min){
                min = tally[tolower(lastopt[strlen(lastopt) - 1])-'a'];
                min_word = lastopt;
            }
        }
    }

    //randomly return min or max
    int choice = coinToss(2);
    if(choice==1){
       return max_word;
    }
    return min_word;
}
