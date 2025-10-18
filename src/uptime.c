#include <windows.h>
#include "winbun.h"
#include "winbun_functions.h"

void getUptime(WINBUN* bun){

    ULONGLONG uptime = GetTickCount64();
    bun->uptime = uptime;

}
