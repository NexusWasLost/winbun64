#pragma once
#ifndef WINCORE_H

#define OS_PRODUCT_NAME_SIZE 64
#define OS_BUILD_NUMBER_SIZE 32
#define OS_VERSION_SIZE 8
#define MAX_DISPLAY_COUNT 4
#define MAX_GPU_COUNT 4

typedef struct Display_Monitors{

    int width;
    int height;
    int refreshRate;

} display;

typedef struct Graphics_Adapter{

    wchar_t GPU_Name[128];
    unsigned long long totalVRAM;

} GPU;

typedef struct Windows_System_Information{

    char CPU[49];
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
    unsigned long long uptime;

    GPU gpu[MAX_GPU_COUNT];
    int gpuCount;

    display monitors[MAX_DISPLAY_COUNT];
    int displayCount;

} WINCORE;

#endif
