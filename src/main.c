#include <stdio.h>
#include "../headers/sysInfo.h"
#include "../headers/sysFunctions.h"

void displayALLData(sysInfo* system);

int main(){

    sysInfo system;

    getMemory(&system);
    getCPU(&system);
    getGPU(&system);
    getOS(&system);
    getDisplay(&system);
    getCurrentUsername(&system);
    getHostName(&system);
    getUptime(&system);
    getLocale(&system);

    displayALLData(&system);
    return 0;
}

void displayALLData(sysInfo* system){

    // ===== HOST =====
    printf("===== %s =====\n", system->host);

    // ===== OS =====
    printf("OS: %s %s (build %s)\n", system->OS_ProductName, system->OS_version, system->OS_buildNumber);

    // ===== Username =====
    printf("User: %s\n", system->currentUserName);

    // ===== Uptime =====
    double minutes = (system->uptime / 1000) / 60;
    printf("Uptime: %d hours %d minutes\n", (int)(minutes / 60), (int)minutes % 60);

    // ===== Memory (RAM) =====
    printf("Memory Used: %llu MB / %llu MB (%llu %%)\n", system->totalUsedMemory, system->totalMemory, system->memoryLoad);
    printf("Available Memory: %llu MB\n", system->availableMemory);

    // ===== Resolution =====
    printf("Resolution: ");
    for(unsigned x = 0; x < system->displayCount; x++){
        //check for last display and dont end with a comma
        if(x == system->displayCount - 1){
            printf("%dx%d @ %dHz\n",
            system->monitors[x].width,
            system->monitors[x].height,
            system->monitors[x].refreshRate);
            break;
        }

        printf("%dx%d @ %dHz, ",
            system->monitors[x].width,
            system->monitors[x].height,
            system->monitors[x].refreshRate);
    }

    // ===== CPU =====
    printf("CPU: %s\n", system->CPU);

    // ===== GPU =====
    if(system->GPU1[0] != '\0'){
        wprintf(L"GPU1: %ls @ %llu MB\n", system->GPU1, system->totalVRAM1);
    }
    if(system->GPU2[0] != '\0'){
        wprintf(L"GPU2: %ls @ %llu MB\n", system->GPU2, system->totalVRAM2);
    }

    // ===== Locale =====
    wprintf(L"Locale: %ls\n", system->locale);

    return;
}
