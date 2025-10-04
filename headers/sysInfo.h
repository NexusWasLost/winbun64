#pragma once

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
    char OS[100];
    char host[30];
    char locale[30];
    char resolution[15];
    long uptime;

} sysInfo;
