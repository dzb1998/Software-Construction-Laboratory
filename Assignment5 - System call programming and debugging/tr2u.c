// Lab5 - tr2u.c
// Zhubo Deng
// 605186231

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    
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
    
    char currChar[2];
    while (read(STDIN_FILENO, currChar, 1) > 0) {
      for (int i = 0; i < from_len; i++) {
	if (from[i] == currChar[0]) {
	  currChar[0] = to[i];
	  write(STDOUT_FILENO, currChar, 1);
	} else {
	  write(STDOUT_FILENO, currChar, 1);
	}
      }
    }

    
    return 0;
    
}
