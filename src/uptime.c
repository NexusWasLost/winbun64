#include <windows.h>
#include "wincore.h"
#include "wincore_functions.h"

void getUptime(WINCORE* core){

    ULONGLONG uptime = GetTickCount64();
    core->uptime = uptime;

}
