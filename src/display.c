#include <windows.h>
#include "winbun.h"
#include "winbun_functions.h"

void getDisplay(WINBUN* bun){
    bun->displayCount = 0;
    DISPLAY_DEVICE disp = { 0 };

    disp.cb = sizeof(disp);

    for(DWORD x = 0; x < 4; x++){
        if (!EnumDisplayDevices(NULL, x, &disp, 0)) break;

        // Skip inactive devices
        if (!(disp.StateFlags & DISPLAY_DEVICE_ACTIVE)) continue;

        DEVMODE devmode = { 0 };
        devmode.dmSize = sizeof(DEVMODE);
        if (EnumDisplaySettings(disp.DeviceName, ENUM_CURRENT_SETTINGS, &devmode)){
            //access each elements of the bun->monitor for the bun->displayCount index;
            bun->monitors[bun->displayCount].height = devmode.dmPelsHeight;
            bun->monitors[bun->displayCount].width = devmode.dmPelsWidth;
            bun->monitors[bun->displayCount].refreshRate = devmode.dmDisplayFrequency;
            bun->displayCount++;
        }
    }
}
