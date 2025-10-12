#include <stdio.h>
#include <windows.h>
#include "../headers/wincore.h"
#include "../headers/wincore_functions.h"

void getCurrentUsername(WINCORE* core){
    DWORD size = sizeof(core->currentUserName);
    WINBOOL uName = GetUserNameA(core->currentUserName, &size);
    if(!uName){
        printf("Error Getting Username...");
        return;
    }
}
