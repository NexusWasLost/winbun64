#include <stdio.h>
#include <windows.h>
#include "../headers/sysInfo.h"
#include "../headers/sysFunctions.h"

void getUptime(sysInfo* system){

    ULONGLONG uptime = GetTickCount64();
    system->uptime = uptime;

}
