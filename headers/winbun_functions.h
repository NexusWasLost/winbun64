#pragma once
#ifndef WINBUN_FUNCTIONS_H
#define WINBUN_FUNCTIONS_H

#include "winbun.h"

#ifdef __cplusplus
extern "C" {
#endif

void getMemory(WINBUN* bun);
void getCPU(WINBUN* bun);
void getGPU(WINBUN* bun);
void getOS(WINBUN* bun);
void getDisplay(WINBUN* bun);
void getCurrentUsername(WINBUN* bun);
void getHostName(WINBUN* bun);
void getUptime(WINBUN* bun);
void getLocale(WINBUN* bun);

#ifdef __cplusplus
}
#endif

#endif
