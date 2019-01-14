// Lab5 - tr2b.c
// Zhubo Deng
// 605186231

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char * argv[]) {
    
    // check; argument counts are supposed to be 2
    int arg_count = 3;
    if (argc != arg_count) {
        fprintf(stderr, "Error! Wrong number of arguments! Should input 2.");
        exit(1);
    }
    
    // initialize from and to pointer and their size
    char* from = argv[1];
    char* to   = argv[2];
    int from_len = strlen(from);
    int to_len   = strlen(to);
    
    // check if their length are equal, otherwise cannot compare
    if (from_len != to_len) {
        fprintf(stderr, "Error! Arguments don't have same length!");
        exit(1);
    }
    
    // check if there are duplicates in "from"
    // compare the letter in from one-by-one
    for (int i = 0; i < from_len; i++) {
        for (int j = i+1; j < from_len; j++) {
            if (from[i] == from[j]) {
                fprintf(stderr, "Error! Can't have same characters in from!");
                exit(1);
            }
        }
    }
    
    // initialize the first char as getchar() and check I/O
    char currChar = getchar();
    if (ferror(stdin)!=0) {
        fprintf(stderr, "I/O Error!");
        exit(1);
    }
    
    int replaced = 0;
    int match_count = 0;     // how many letters matched
    while (currChar != EOF) {
        int index = 0;
        for (int i = 0; i < from_len; i++) {
            if (currChar == from[i]) {
                putchar(to[i]);
                replaced = 1;     // replaced w/ to[i] in the target file
                break;
            } else {
                putchar(currChar);     // no replacement
            }
        }
        
        currChar = getchar();    // getting a new char and go back to the loop
    }
    
    return 0;
    
}
