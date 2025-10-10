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

    char CPU[49];
    wchar_t GPU1[128];
    wchar_t GPU2[128];
    char OS_ProductName[OS_PRODUCT_NAME_SIZE];
    char OS_version[OS_VERSION_SIZE];
    char OS_buildNumber[OS_BUILD_NUMBER_SIZE];
    char host[16];
    wchar_t locale[16];
    char currentUserName[32];
    char CPU_Architecture[8];

    unsigned long long totalMemory;
    unsigned long long availableMemory;
    unsigned long long totalUsedMemory;
    unsigned long long memoryLoad;
    unsigned long long totalVRAM1;
    unsigned long long totalVRAM2;
    unsigned long long uptime;

    display monitors[4];
    int displayCount;

} sysInfo;

#endif
