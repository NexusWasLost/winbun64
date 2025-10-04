#include <stdio.h>
#include "../headers/sysFunctions.h"
#include "../headers/sysInfo.h"

int main(){

    sysInfo system;
    getMemory(&system);

    printf("Total Memory: %llu MB\n", system.totalMemory);
    printf("Available Memory: %llu MB\n", system.availableMemory);
    printf("Memory Load: %llu %%\n", system.memoryLoad);

    getGPU(&system);

    if(system.GPU1[0] != '\0'){
        wprintf(L"GPU1: %ls @ %llu MB\n", system.GPU1, system.totalVRAM1);
    }
    if(system.GPU2[0] != '\0'){
        wprintf(L"GPU2: %ls @ %llu MB\n", system.GPU2, system.totalVRAM2);
    }

    getCPU(&system);
    printf("CPU: %s", system.CPU);
    return 0;
}
