#include <stdio.h>
#include <windows.h>
#include "winbun.h"
#include "winbun_functions.h"

void getHostName(WINBUN* bun){
    DWORD size = sizeof(bun->host);

    WINBOOL res = GetComputerNameA(bun->host, &size);
    if(!res){
        printf("Error Getting Host Name...");
        return;
    }
}
