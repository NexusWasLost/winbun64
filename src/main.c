#include <stdio.h>
#include "../headers/sysFunctions.h"
#include "../headers/sysInfo.h"

int main(){

    sysInfo system;
    getMemory(&system);

    printf("Memory: %llu MB / %llu MB (%llu %%)\n", system.totalUsedMemory, system.totalMemory, system.memoryLoad);
    printf("Available Memory: %llu MB\n", system.availableMemory);
    // printf("Total Memory: %llu MB\n", system.totalMemory);
    // printf("Memory Load: %llu %%\n", system.memoryLoad);

    getGPU(&system);
    if(system.GPU1[0] != '\0'){
        wprintf(L"GPU1: %ls @ %llu MB\n", system.GPU1, system.totalVRAM1);
    }
    if(system.GPU2[0] != '\0'){
        wprintf(L"GPU2: %ls @ %llu MB\n", system.GPU2, system.totalVRAM2);
    }

    getCPU(&system);
    printf("CPU: %s\n", system.CPU);

    getOS(&system);
    printf("OS: %s %s (build %s.%d)\n", system.OS_ProductName, system.OS_version, system.OS_buildNumber);

    getLocale(&system);
    wprintf(L"Locale: %ls\n", system.locale);

    getHostName(&system);
    printf("Host: %s\n", system.host);

    getUptime(&system);
    double minutes = (system.uptime / 1000) / 60;
    printf("Uptime: %d hours %d minutes\n", (int)(minutes / 60), (int)minutes % 60);

    getDisplay(&system);
    printf("Resolution: ");
    for(unsigned x = 0; x < system.displayCount; x++){
        //check for last display and dont end with a comma
        if(x == system.displayCount - 1){
            printf("%dx%d @ %dHz\n",
            system.monitors[x].width,
            system.monitors[x].height,
            system.monitors[x].refreshRate);
            break;
        }

        printf("%dx%d @ %dHz, ",
            system.monitors[x].width,
            system.monitors[x].height,
            system.monitors[x].refreshRate);
    }

    getCurrentUsername(&system);
    printf("User: %s", system.currentUserName);

    return 0;
}
