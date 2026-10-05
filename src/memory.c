#include <stdio.h>
#include <windows.h>
#include "lumi.h"
#include "lumi_functions.h"

void getMemory(LUMI* lumi){
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);

    if(!GlobalMemoryStatusEx(&mem)){
        printf("Failed to Get Memory Information...");
        return;
    }

    lumi->totalMemory = mem.ullTotalPhys / (1024 * 1024);
    lumi->availableMemory = mem.ullAvailPhys / (1024 * 1024);
    lumi->memoryLoad = mem.dwMemoryLoad;
    lumi->usedMemory = lumi->totalMemory - lumi->availableMemory;

}
