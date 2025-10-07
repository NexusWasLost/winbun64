#pragma once

typedef struct Display_Monitors{

    int width;
    int height;
    int refreshRate;

}display;

typedef struct System_Information{
    //Memory Information (RAM)
    unsigned long long totalMemory;
    unsigned long long availableMemory;
    unsigned long long memoryLoad;

    //CPU information
    char CPU[49];

    //GPU information
    wchar_t GPU1[128];
    unsigned long long totalVRAM1;
    wchar_t GPU2[128];
    unsigned long long totalVRAM2;

    //OS based system information
    char OS_ProductName[64];
    char OS_version[8];
    char OS_buildNumber[32];

    char host[16];
    wchar_t locale[16];
    unsigned long long uptime;
    char currentUserName[32];

    //monitors
    display monitors[4];
    int displayCount;

} sysInfo;
