// Homework 4
// Zhubo Deng
// 605186231


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int frobcmp(char const* a, char const* b) {
    
    // Initialize the index for a and b
    int a_Index = 0;
    int b_Index = 0;
    
    // Suppose they don't start with a space, then compare
    while (a[a_Index] != ' ' && b[b_Index] != ' ') {
        if ( (a[a_Index]^42) > (b[b_Index]^42) ) {
            return 1;
        }
        else if (( (a[a_Index]^42) < (b[b_Index]^42) )) {
            return -1;
        }
        a_Index++;
        b_Index++;
    }
    
    if ( a[a_Index] != ' ' && b[b_Index] == ' ' ) {
        return 1;
    }
    else if ( a[a_Index] == ' ' && b[b_Index] != ' ' ) {
        return -1;
    }
    else
        return 0;
    
}


// Assign the value to frobcmp funtion
int compareFunc(const void* a, const void* b) {
    return frobcmp(*(char**) a, *(char**) b);
}



int main(void) {
    
    // Declare current word and array of all the words
    char* currWord = (char*) malloc(sizeof(char));
    char** wordsArr = (char**) malloc(sizeof(char*));
    
    // Declare word count and letter count
    int wordsCount = 0;
    int charsCount = 0;
    
    // Set up first 2 chars as stdin, and check error
    char currIn = getchar();
    if (ferror(stdin) != 0) {
        fprintf(stderr, "Can't Read Input!");
        exit(1);
    }
    char nextIn = getchar();
    if (ferror(stdin) != 0) {
        fprintf(stderr, "Can't Read Input!");
        exit(1);
    }
    
    // Initialize an end of file tester
    int checkEOF = feof(stdin);
    
    // If this is not the end of file, then go into a while loop, read in stdin
    while (!checkEOF) {
        
        // Assign the first char to the first letter of word 1, allocate memory
        // for this word, and check error, and increment chars count.
        currWord[charsCount] = currIn;
        char* temp = (char*)realloc(currWord, (charsCount + 2) * sizeof(char));
        if (temp == NULL) {
            // free the memory
            free(currWord);
            fprintf(stderr, "Can't allocate memory!");
            exit(1);
        }
        currWord = temp;
        charsCount++;
        
        // If the input is a space, then this word is complete. Allocate memory
        // for the word array as temp array, check error, and assign it to the
        // real array, and increment total words count, and set chars count to 0
        // since we should restart the count for the word.
        if (currIn == ' ') {
            wordsArr[wordsCount] = currWord;
            char** tempArr = (char**) realloc(wordsArr, (wordsCount+2)*sizeof(char*));
            if (tempArr == NULL) {
                // free the memory
                free(wordsArr);
                fprintf(stderr, "Can't allocate memory!");
                exit(1);
            }
            
            wordsArr = tempArr;
            wordsCount++;
            currWord = NULL;
            currWord = (char*) malloc(sizeof(char));
            charsCount = 0;
        }
        
        // Check end of file again. Also check error in every step.
        // If there is a space left, and also end of the file, then end the loop
        // If there are two space together, then keep reading until get the fisrt char.
        // If it's end of the file, then save both the letter and word to the memory.
        checkEOF = feof(stdin);
        if (currIn == ' ' && checkEOF) {
            break;
        } else if (currIn == ' ' && nextIn == ' ') {
            
            while (currIn == ' ') {
                currIn = getchar();
                if (ferror(stdin) != 0) {
                    fprintf(stderr, "Can't Read Input!");
                    exit(1);
                }
            }
            
            nextIn = getchar();
            if (ferror(stdin) != 0) {
                fprintf(stderr, "Can't Read Input!");
                exit(1);
            }
            charsCount++;
            continue;
        } else if (checkEOF) {
            currIn = ' ';
            currWord[charsCount] = currIn;
            wordsArr[wordsCount] = currWord;
            
            char** tempArr = (char**) realloc(wordsArr, (wordsCount+2)*sizeof(char*));
            if (tempArr == NULL) {
                free(wordsArr);
                fprintf(stderr, "Can't allocate memory!");
                exit(1);
            }
            wordsArr = tempArr;
            wordsCount++;
            break;
        }
        
        // move forward one char
        currIn = nextIn;
        nextIn = getchar();
        if (ferror(stdin) != 0) {
            fprintf(stderr, "Can't Read Input!");
            exit(1);
        }
        
    }
    
    // after getting things in the memory, sort them
    qsort(wordsArr, wordsCount, sizeof(char*), compareFunc);
    
    for (int i = 0; i < wordsCount; i++) {
        for (int j = 0; ; j++) {
            putchar(wordsArr[i][j]);
            if (ferror(stdin) != 0) {
                fprintf(stderr, "Can't Read Input!");
                exit(1);
            }
            if (wordsArr[i][j] == ' ') {
                break;
            }
        }
    }
    
    // after done sorting, free the allocated memory space
    for (int i = 0; i < wordsCount; i++) {
        free(wordsArr[i]);
    }
    
    free(wordsArr);
    
}


