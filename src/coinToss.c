#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
 int random(int n){
    time_t t1;
    srand ( (unsigned) time (&t1));
    int random = rand() % n;
   
    return random;

 }
 void main(){
    printf("%d",random(4));

 }
