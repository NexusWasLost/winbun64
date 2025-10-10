#include <stdio.h>
#include <windows.h>
#include "../headers/sysFunctions.h"
#include "../headers/sysInfo.h"

void getMemory(sysInfo* system){
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);

    if(!GlobalMemoryStatusEx(&mem)){
        printf("Failed to Get Memory Information...");
        return;
    }

    system->totalMemory = mem.ullTotalPhys / (1024 * 1024);
    system->availableMemory = mem.ullAvailPhys / (1024 * 1024);
    system->memoryLoad = mem.dwMemoryLoad;
    system->totalUsedMemory = system->totalMemory - system->availableMemory;

}
