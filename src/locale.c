#include <stdio.h>
#include <windows.h>
#include "wincore.h"
#include "wincore_functions.h"

void getLocale(WINCORE* core){

    int lc = GetUserDefaultLocaleName(core->locale, LOCALE_NAME_MAX_LENGTH);
    if(!lc){
        printf("Error Getting Locale...");
        return;
    }

}
