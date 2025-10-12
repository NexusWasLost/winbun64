#include <stdio.h>
#include <windows.h>
#include "../headers/wincore.h"
#include "../headers/wincore_functions.h"

void getUptime(WINCORE* core){

    ULONGLONG uptime = GetTickCount64();
    core->uptime = uptime;

}
