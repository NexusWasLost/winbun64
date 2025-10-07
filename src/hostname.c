#include <stdio.h>
#include <windows.h>
#include "../headers/sysInfo.h"
#include "../headers/sysFunctions.h"

void getHostName(sysInfo* system){
    DWORD size = sizeof(system->host);

    WINBOOL res = GetComputerNameA(system->host, &size);
    if(!res){
        printf("Error Getting Host Name...");
        return;
    }
}
