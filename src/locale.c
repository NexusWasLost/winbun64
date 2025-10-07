#include <stdio.h>
#include <windows.h>
#include "../headers/sysInfo.h"
#include "../headers/sysFunctions.h"

void getLocale(sysInfo* system){

    int lc = GetUserDefaultLocaleName(system->locale, LOCALE_NAME_MAX_LENGTH);
    if(!lc){
        printf("Error Getting Locale...");
        return;
    }

}
