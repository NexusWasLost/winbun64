#include <stdio.h>
#include <windows.h>
#include "../headers/sysInfo.h"
#include "../headers/sysFunctions.h"

void getCurrentUsername(sysInfo* system){
    DWORD size = sizeof(system->currentUserName);
    WINBOOL uName = GetUserNameA(system->currentUserName, &size);
    if(!uName){
        printf("Error Getting Username...");
        return;
    }
}
