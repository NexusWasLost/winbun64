#include <stdio.h>
#include <windows.h>
#include "../headers/wincore.h"
#include "../headers/wincore_functions.h"

void getHostName(WINCORE* core){
    DWORD size = sizeof(core->host);

    WINBOOL res = GetComputerNameA(core->host, &size);
    if(!res){
        printf("Error Getting Host Name...");
        return;
    }
}
