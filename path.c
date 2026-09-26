#include <stdlib.h>
#include <string.h>

char* simplifyPath(char* path) {
    int n = strlen(path);
    
    // Allocate space for the stack arrays to store tokens
    // At most, there can be n/2 directories
    char** stack = (char**)malloc(n * sizeof(char*));
    int top = 0;
    
    // Use strtok to split the string cleanly by '/'
    char* token = strtok(path, "/");
    while (token != NULL) {
        if (strcmp(token, ".") == 0 || strcmp(token, "") == 0) {
            // Do nothing for current directory markers
        } else if (strcmp(token, "..") == 0) {
            // Move up one directory level if possible
            if (top > 0) {
                top--;
            }
        } else {
            // Push valid directory name to the stack
            stack[top++] = token;
        }
        token = strtok(NULL, "/");
    }
    
    // Allocate memory for the final canonical path output
    char* result = (char*)malloc((n + 1) * sizeof(char));
    result[0] = '\0'; // Initialize as empty string
    
    if (top == 0) {
        strcpy(result, "/");
    } else {
        for (int i = 0; i < top; i++) {
            strcat(result, "/");
            strcat(result, stack[i]);
        }
    }
    
    // Free the temporary pointer stack array tracking directory tiers
    free(stack);
    
    return result;
}
