#include <stdio.h>
#include <windows.h>
#include "wincore.h"
#include "wincore_functions.h"

void getMemory(WINCORE* core){
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);

    if(!GlobalMemoryStatusEx(&mem)){
        printf("Failed to Get Memory Information...");
        return;
    }

    core->totalMemory = mem.ullTotalPhys / (1024 * 1024);
    core->availableMemory = mem.ullAvailPhys / (1024 * 1024);
    core->memoryLoad = mem.dwMemoryLoad;
    core->totalUsedMemory = core->totalMemory - core->availableMemory;

}
