#include <stdio.h>
#include <windows.h>
#include "winbun.h"
#include "winbun_functions.h"

void getLocale(WINBUN* bun){

    int lc = GetUserDefaultLocaleName(bun->locale, LOCALE_NAME_MAX_LENGTH);
    if(!lc){
        printf("Error Getting Locale...");
        return;
    }

}
