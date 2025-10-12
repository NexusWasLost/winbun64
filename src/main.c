#include <stdio.h>
#include "../headers/wincore.h"
#include "../headers/wincore_functions.h"

void displayALLData(WINCORE* core);

int main(){

    WINCORE core;

    getMemory(&core);
    getCPU(&core);
    getGPU(&core);
    getOS(&core);
    getDisplay(&core);
    getCurrentUsername(&core);
    getHostName(&core);
    getUptime(&core);
    getLocale(&core);

    displayALLData(&core);
    return 0;
}

void displayALLData(WINCORE* core){

    // ===== HOST =====
    printf("===== %s =====\n", core->host);

    // ===== OS =====
    printf("OS: %s %s (build %s)\n", core->OS_ProductName, core->OS_version, core->OS_buildNumber);

    // ===== Username =====
    printf("User: %s\n", core->currentUserName);

    // ===== Uptime =====
    double minutes = (core->uptime / 1000) / 60;
    printf("Uptime: %d hours %d minutes\n", (int)(minutes / 60), (int)minutes % 60);

    // ===== Memory (RAM) =====
    printf("Memory Used: %llu MB / %llu MB (%llu %%)\n", core->totalUsedMemory, core->totalMemory, core->memoryLoad);
    printf("Available Memory: %llu MB\n", core->availableMemory);

    // ===== Resolution =====
    printf("Resolution: ");
    for(int x = 0; x < core->displayCount; x++){
        //check for last display and dont end with a comma
        if(x == core->displayCount - 1){
            printf("%dx%d @ %dHz\n",
            core->monitors[x].width,
            core->monitors[x].height,
            core->monitors[x].refreshRate);
            break;
        }

        printf("%dx%d @ %dHz, ",
            core->monitors[x].width,
            core->monitors[x].height,
            core->monitors[x].refreshRate);
    }

    // ===== CPU =====
    printf("CPU: %s\n", core->CPU);

    // ===== GPU =====
    for(int x = 0; x < core->gpuCount; x++){
        wprintf(L"GPU%d: %ls @ %llu MB\n", x + 1, core->gpu[x].GPU_Name, core->gpu[x].totalVRAM);
    }

    // if(core->GPU1[0] != '\0'){
    //     wprintf(L"GPU1: %ls @ %llu MB\n", core->GPU1, core->totalVRAM1);
    // }
    // if(core->GPU2[0] != '\0'){
    //     wprintf(L"GPU2: %ls @ %llu MB\n", core->GPU2, core->totalVRAM2);
    // }

    // ===== Locale =====
    wprintf(L"Locale: %ls\n", core->locale);

    return;
}
