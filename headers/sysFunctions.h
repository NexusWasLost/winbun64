#pragma once
#ifndef SYSFUNCTIONS_H

#include "sysInfo.h"

void getMemory(sysInfo* system);
void getCPU(sysInfo* system);
void getGPU(sysInfo* system);
void getOS(sysInfo* system);
void getDisplay(sysInfo* system);
void getCurrentUsername(sysInfo* system);
void getHostName(sysInfo* system);
void getUptime(sysInfo* system);
void getLocale(sysInfo* system);

#endif
