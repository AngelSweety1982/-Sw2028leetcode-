#include <stdlib.h>
#include <string.h>

// A simple hash table node structure for chaining
typedef struct HashNode {
    char* key;
    char* value;
    struct HashNode* next;
} HashNode;

#define HASH_SIZE 2047

// Polynomial rolling hash function for strings
unsigned int getHash(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = hash * 31 + *str;
        str++;
    }
    return hash % HASH_SIZE;
}

char* evaluate(char* s, char*** knowledge, int knowledgeSize, int* knowledgeColSize) {
    // 1. Initialize the Hash Map
    HashNode** hashTable = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));
    
    // 2. Populate the Hash Map with knowledge pairs
    for (int i = 0; i < knowledgeSize; i++) {
        char* key = knowledge[i][0];
        char* val = knowledge[i][1];
        unsigned int h = getHash(key);
        
        HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
        newNode->key = key;
        newNode->value = val;
        newNode->next = hashTable[h];
        hashTable[h] = newNode;
    }
    
    // 3. Pre-allocate buffer for the result string
    // In worst case, keys like (a) could expand if value is very long, 
    // but usually string length + sum of values is safe. 
    int sLen = strlen(s);
    int bufferSize = sLen * 2 + 1000; // Safe dynamic buffer baseline
    char* result = (char*)malloc(sizeof(char) * bufferSize);
    int resIdx = 0;
    
    // 4. Parse the input string
    for (int i = 0; i < sLen; i++) {
        if (s[i] == '(') {
            int start = i + 1;
            // Find the matching closing bracket
            while (s[i] != ')') {
                i++;
            }
            int keyLen = i - start;
            
            // Extract the key inside the bracket
            char* key = (char*)malloc(sizeof(char) * (keyLen + 1));
            strncpy(key, &s[start], keyLen);
            key[keyLen] = '\0';
            
            // Look up the key in the Hash Map
            unsigned int h = getHash(key);
            HashNode* curr = hashTable[h];
            char* replacement = "?"; // Default if key is not found
            
            while (curr != NULL) {
                if (strcmp(curr->key, key) == 0) {
                    replacement = curr->value;
                    break;
                }
                curr = curr->next;
            }
            
            // Append the replacement value to our result buffer
            int repLen = strlen(replacement);
            // Resize buffer if running out of space
            if (resIdx + repLen >= bufferSize) {
                bufferSize *= 2;
                result = (char*)realloc(result, sizeof(char) * bufferSize);
            }
            strcpy(&result[resIdx], replacement);
            resIdx += repLen;
            
            free(key);
        } else {
            // Append normal characters
            if (resIdx >= bufferSize - 1) {
                bufferSize *= 2;
                result = (char*)realloc(result, sizeof(char) * bufferSize);
            }
            result[resIdx++] = s[i];
        }
    }
    result[resIdx] = '\0';
    
    // 5. Free the hash table nodes
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* curr = hashTable[i];
        while (curr != NULL) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(hashTable);
    
    return result;
}
