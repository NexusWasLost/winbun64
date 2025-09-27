#pragma once

typedef struct System_Information{
    //Memory Information (RAM)
    unsigned long long totalMemory;
    unsigned long long availableMemory;
    unsigned long long memoryLoad;

    //CPU information
    char CPU[48];
    //GPU information
    char GPU[100];

    //OS based system information
    char OS[100];
    char host[30];
    char locale[30];
    char resolution[15];
    long uptime;

} sysInfo;
