#include <stdio.h>
#include <windows.h>
#include "winbun.h"
#include "winbun_functions.h"

void getMemory(WINBUN* bun){
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);

    if(!GlobalMemoryStatusEx(&mem)){
        printf("Failed to Get Memory Information...");
        return;
    }

    bun->totalMemory = mem.ullTotalPhys / (1024 * 1024);
    bun->availableMemory = mem.ullAvailPhys / (1024 * 1024);
    bun->memoryLoad = mem.dwMemoryLoad;
    bun->usedMemory = bun->totalMemory - bun->availableMemory;

}
