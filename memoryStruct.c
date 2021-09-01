#include "memoryStruct.h"
#include <stdlib.h>

MemoryStruct newMemoryStruct() {
    MemoryStruct mem;
    mem.memory = malloc(1); // will be grown as necessary with realloc
    mem.size = 0; // since there is no data yet
    return mem;
}

void cleanMemoryStructContent(MemoryStruct *mem) {
    free(mem->memory);
    mem->memory = malloc(1);
    mem->size = 0;
}