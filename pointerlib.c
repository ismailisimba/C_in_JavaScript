// pointerlib.c
#include <stdlib.h>
#include <string.h>

// Allocates 1024 bytes on the heap and returns the pointer
char* createMemory() {
    char* buffer = (char*) malloc(1024);
    if (buffer == NULL) {
        return NULL; // Return NULL if allocation fails
    }
    // Optional: initialize memory for clarity
    // e.g., fill it with zeros
    memset(buffer, 0, 1024);
    return buffer;
}

// Frees memory created by createMemory()
void freeMemory(char* ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}
