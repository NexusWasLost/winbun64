#include <windows.h>
#include "../headers/sysInfo.h"
#include "../headers/sysFunctions.h"

void getDisplay(sysInfo* system){
    system->displayCount = 0;
    DISPLAY_DEVICE disp = { 0 };

    disp.cb = sizeof(disp);

    for(DWORD x = 0; x < 4; x++){
        if (!EnumDisplayDevices(NULL, x, &disp, 0)) break;

        // Skip inactive devices
        if (!(disp.StateFlags & DISPLAY_DEVICE_ACTIVE)) continue;

        DEVMODE devmode = { 0 };
        devmode.dmSize = sizeof(DEVMODE);
        if (EnumDisplaySettings(disp.DeviceName, ENUM_CURRENT_SETTINGS, &devmode)){
            //access each elements of the system->monitor for the system->displayCount index;
            system->monitors[system->displayCount].height = devmode.dmPelsHeight;
            system->monitors[system->displayCount].width = devmode.dmPelsWidth;
            system->monitors[system->displayCount].refreshRate = devmode.dmDisplayFrequency;
            system->displayCount++;
        }
    }
}
