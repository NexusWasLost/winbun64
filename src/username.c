#include <stdio.h>
#include <windows.h>
#include "winbun.h"
#include "winbun_functions.h"

void getCurrentUsername(WINBUN* bun){
    DWORD size = sizeof(bun->currentUserName);
    WINBOOL uName = GetUserNameA(bun->currentUserName, &size);
    if(!uName){
        printf("Error Getting Username...");
        return;
    }
}
