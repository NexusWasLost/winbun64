#include <stdio.h>
#include <windows.h>
#include "lumi.h"
#include "lumi_functions.h"

void getCurrentUsername(LUMI* lumi){
    DWORD size = sizeof(lumi->currentUserName);
    WINBOOL uName = GetUserNameA(lumi->currentUserName, &size);
    if(!uName){
        printf("Error Getting Username...");
        return;
    }
}
