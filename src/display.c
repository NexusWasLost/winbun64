#include <windows.h>
#include "wincore.h"
#include "wincore_functions.h"

void getDisplay(WINCORE* core){
    core->displayCount = 0;
    DISPLAY_DEVICE disp = { 0 };

    disp.cb = sizeof(disp);

    for(DWORD x = 0; x < 4; x++){
        if (!EnumDisplayDevices(NULL, x, &disp, 0)) break;

        // Skip inactive devices
        if (!(disp.StateFlags & DISPLAY_DEVICE_ACTIVE)) continue;

        DEVMODE devmode = { 0 };
        devmode.dmSize = sizeof(DEVMODE);
        if (EnumDisplaySettings(disp.DeviceName, ENUM_CURRENT_SETTINGS, &devmode)){
            //access each elements of the core->monitor for the core->displayCount index;
            core->monitors[core->displayCount].height = devmode.dmPelsHeight;
            core->monitors[core->displayCount].width = devmode.dmPelsWidth;
            core->monitors[core->displayCount].refreshRate = devmode.dmDisplayFrequency;
            core->displayCount++;
        }
    }
}
