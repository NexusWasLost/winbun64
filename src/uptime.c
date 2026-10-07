#include <windows.h>
#include "lumi.h"
#include "lumi_functions.h"

typedef struct _SYSTEM_TIME_INFORMATION {
    LARGE_INTEGER BootTime;
    LARGE_INTEGER CurrentTime;
    LARGE_INTEGER TimeZoneBias;
    ULONG CurrentTimeZoneId;
    ULONG Reserved;
} SYSTEM_TIME_INFORMATION;

typedef LONG (WINAPI *pfnNtQuerySystemInformation)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
);

void getUptime(LUMI* lumi){
    lumi->uptime = 0;

    /**
     This one is sort of a wild thing I learned today
     I wrote what I understood
     So view my Rant here:

     https://nexus.bearblog.dev/querying-uptime-in-c/

     */

    HMODULE hNTDLL = GetModuleHandleA("ntdll.dll");
    if(!hNTDLL) return;

    pfnNtQuerySystemInformation NtQuerySystemInformation =
        (pfnNtQuerySystemInformation)GetProcAddress(hNTDLL, "NtQuerySystemInformation");

    if(!NtQuerySystemInformation) return;

    SYSTEM_TIME_INFORMATION timeInfo = {0};
    ULONG returnLen = 0;

    LONG status = NtQuerySystemInformation(3, &timeInfo, sizeof(timeInfo), &returnLen);
    if(status == 0 && timeInfo.CurrentTime.QuadPart > timeInfo.BootTime.QuadPart){
        LONGLONG diff = timeInfo.CurrentTime.QuadPart - timeInfo.BootTime.QuadPart;
        // diff is chunks of nano seconds (each chunk is 100ns) !
        // Divide the div by 10,000,000 to get seconds
        // printf("Uptime: %llu\n", (unsigned long long)(diff / 10000000LL));
        lumi->uptime = (unsigned long long)(diff / 10000000LL);
    }
    else {
        lumi->uptime = 0;
        return;
    }

}

void getKernelUptime(LUMI* lumi){
    lumi->kernelUptime = GetTickCount64() / 1000ULL;
}
