#include <stdio.h>
#include "./headers/sysFunctions.h"
#include "./headers/sysInfo.h"

int main(){

    sysInfo system;
    getMemory(&system);

    printf("Total Memory: %llu MB\n", system.totalMemory);
    printf("Available Memory: %llu MB\n", system.availableMemory);
    printf("Memory Load: %llu %%\n", system.memoryLoad);

    return 0;
}
