#pragma once
#ifndef WINCORE_FUNCTIONS_H

#include "wincore.h"

void getMemory(WINCORE* core);
void getCPU(WINCORE* core);
void getGPU(WINCORE* core);
void getOS(WINCORE* core);
void getDisplay(WINCORE* core);
void getCurrentUsername(WINCORE* core);
void getHostName(WINCORE* core);
void getUptime(WINCORE* core);
void getLocale(WINCORE* core);

#endif
