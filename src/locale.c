#include <stdio.h>
#include <windows.h>
#include "lumi.h"
#include "lumi_functions.h"

void getLocale(LUMI* lumi){

    int lc = GetUserDefaultLocaleName(lumi->locale, LOCALE_NAME_MAX_LENGTH);
    if(!lc){
        printf("Error Getting Locale...");
        return;
    }

}
