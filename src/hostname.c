#include <stdio.h>
#include <windows.h>
#include "lumi.h"
#include "lumi_functions.h"

void getHostName(LUMI* lumi){
    DWORD size = sizeof(lumi->host);

    WINBOOL res = GetComputerNameA(lumi->host, &size);
    if(!res){
        printf("Error Getting Host Name...");
        return;
    }
}
