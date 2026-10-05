#include <windows.h>
#include "lumi.h"
#include "lumi_functions.h"

void getUptime(LUMI* lumi){

    ULONGLONG uptime = GetTickCount64();
    lumi->uptime = uptime;

}
