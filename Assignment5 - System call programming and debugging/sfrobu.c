// Zhubo Deng
// 605186231

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

bool caseBool = false;
struct stat buffer;

unsigned char decrypt(char a) {
    a = a ^ 42;
    if (caseBool) {
        a = toupper((unsigned char)a);
    }
    
    return a;
}

int frobcmp (char const *a, char const *b) {
    int aIndex = 0;
    int bIndex = 0;
    
    while (!!(strncmp(&a[aIndex], " ", 1)) && !!(strncmp(&b[bIndex], " ", 1))) {
        if (decrypt(a[aIndex]) > decrypt(b[bIndex])) {
            return 1;
        } else if (decrypt(a[aIndex]) < decrypt(b[bIndex])) {
            return -1;
        } else {
            aIndex++;
            bIndex++;
        }
    }
    
    if (!!(strncmp(&a[aIndex], " ", 1)))
        return 1;
    else if (!!(strncmp(&b[bIndex], " ", 1)))
        return -1;
    else
        return 0;
}

int compareFunc(const void *a, const void *b) {
    return frobcmp(*(char**)a, *(char**)b);
}

int main(int argc, char *argv[]) {
    
    // check argument legal
    if(argc > 2) {
        fprintf(stderr, "Error! Command arguments error!");
        exit(1);
    } else if (argc == 2) {
        const char *optionCheck = argv[1];
        if (strlen(optionCheck) != 2) {
            fprintf(stderr, "Error! Command arguments error!");
            exit(1);
        }
        else if (optionCheck[0] == '-' &&
                 optionCheck[1] == 'f')
            caseBool = true;
        else {
            fprintf(stderr, "Error! Command arguments error!");
            exit(1);
        }
    }
    
    // declare all the variables
    char currChar;
    char* nextInput;
    char** lineBuffer;
    char readBuffer[2];
    
    int bufferSize = 0;
    int lineNum = 0;
    int lineSize = 0;
    int checkEOF = 0;
    
    int (* cmp) (const void*, const void*) = &compareFunc;
    
    // Check return value positive
    int retVal = fstat(STDIN_FILENO, &buffer);
    if(retVal < 0) {
        fprintf(stderr, "Error! I/O error!");
        exit(1);
    }
    
    // set file size == buffer, and then check input
    int fileSize = buffer.st_size + 1;
    char* input = (char*) malloc(sizeof(char) * fileSize);
    if(input == NULL) {
        fprintf(stderr, "Error! Allocate memory error!");
        exit(1);
    }
    
    char* line = input;
    
    // start while loop by checking EOF is available
    while (!checkEOF) {
        
        retVal = read(STDIN_FILENO, readBuffer, 1);
        if(retVal < 0) {
            fprintf(stderr, "Error! I/O error!");
            exit(1);
        }
        
        // set current char to readBuffer[0]
        currChar = readBuffer[0];
        // check space or no space
        int isSpace = currChar == ' ';
        // reset check EOF
        checkEOF = !retVal;
        
        // continue only if size != SP
        if (isSpace && !lineSize) {
            continue;
        }
        
        // new input; next input
        if (bufferSize == fileSize) {
            fileSize *= 2;
            nextInput = (char*) realloc(input,
                                          sizeof(char) * fileSize);
            
            if(nextInput == NULL) {
                fprintf(stderr, "Error! Allocate memory error!");
                exit(1);
            }
            
            input = nextInput;     // if no error then assign it
        }
        
        // if this is not EOF
        if (!checkEOF) {
            input[bufferSize++] = currChar;
            lineSize++;
            
            // check sp and eof or not
            if (!isSpace)
                continue;
        } else {
            if (!bufferSize) {
                free(input);
                return 0;
            }
            
            // check last buf is sp
            if (input[bufferSize-1] != ' ') {
                input[bufferSize++] = ' ';
            }
            
            // check line size available
            if (!lineSize)
                break;
        }
        
        lineSize = 0;
        lineNum++;
    }  // end of while loop
    
    
    // allocate the line buffer
    lineBuffer = (char**) malloc(sizeof(char*) * lineNum);
    if(lineBuffer == NULL) {
        fprintf(stderr, "Error! Allocate memory error!");
        exit(1);
    }
    
    // Check the line count is the same or not
    char* liner = input;
    int i = 0;
    int num = 0;
    for (i, num; i < bufferSize; i++) {
        if (input[i] == ' ') {
            lineBuffer[num++] = liner;
            liner = input + i + 1;
        }
    }
    
    if (lineNum != num) {
        fprintf(stderr, "Error! Line number error!");
        exit(1);
    }
    
    // start to sort and compare
    qsort(lineBuffer, lineNum, sizeof(char*), cmp);
    
    // check conditions and write to the output
    for (int i = 0; i < lineNum; i++) {
        int ret = 0;
        for (;;) {
            ret = write(STDOUT_FILENO, lineBuffer[i], 1);
            
            if(ret < 0) {
                fprintf(stderr, "Error! I/O error!");
                exit(1);
            }
            
            if (*lineBuffer[i]++ == ' ')
                break;
        }
    }
    
    // free the allocated memory
    free(lineBuffer);
    free(input);
    
    return 0;
}
