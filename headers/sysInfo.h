#pragma once
#ifndef SYSINFO_H

#define OS_PRODUCT_NAME_SIZE 64
#define OS_BUILD_NUMBER_SIZE 32
#define OS_VERSION_SIZE 8

typedef struct Display_Monitors{

    int width;
    int height;
    int refreshRate;

}display;

typedef struct System_Information{
    //Memory Information (RAM)
    unsigned long long totalMemory;
    unsigned long long availableMemory;
    unsigned long long totalUsedMemory;
    unsigned long long memoryLoad;

    //CPU information
    char CPU[49];

    //GPU information
    wchar_t GPU1[128];
    unsigned long long totalVRAM1;
    wchar_t GPU2[128];
    unsigned long long totalVRAM2;

    //OS based system information
    char OS_ProductName[OS_PRODUCT_NAME_SIZE];
    char OS_version[OS_VERSION_SIZE];
    char OS_buildNumber[OS_BUILD_NUMBER_SIZE];

    char host[16];
    wchar_t locale[16];
    unsigned long long uptime;
    char currentUserName[32];

    //monitors
    display monitors[4];
    int displayCount;

} sysInfo;

#endif
