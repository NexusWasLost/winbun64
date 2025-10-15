#pragma once
#ifndef WINCORE_FUNCTIONS_H
#define WINCORE_FUNCTIONS_H

#include "wincore.h"

#ifdef __cplusplus
extern "C" {
#endif

void getMemory(WINCORE* core);
void getCPU(WINCORE* core);
void getGPU(WINCORE* core);
void getOS(WINCORE* core);
void getDisplay(WINCORE* core);
void getCurrentUsername(WINCORE* core);
void getHostName(WINCORE* core);
void getUptime(WINCORE* core);
void getLocale(WINCORE* core);

#ifdef __cplusplus
}
#endif

#endif
