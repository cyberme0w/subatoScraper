#include <unistd.h>

typedef struct {
    char *memory;
    size_t size;
} MemoryStruct;

MemoryStruct newMemoryStruct();

void cleanMemoryStructContent(MemoryStruct *mem);