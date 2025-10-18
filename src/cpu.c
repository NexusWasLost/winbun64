#include <stdio.h>
#include <windows.h>
#include <cpuid.h>
#include <string.h>
#include "winbun.h"
#include "winbun_functions.h"

void getCPU(WINBUN* bun){
    char CPU_brand_string[49];

    unsigned int eax, ebx, ecx, edx;

    for(int x = 0; x < 3; x++){
        __get_cpuid(0x80000002 + x, &eax, &ebx, &ecx, &edx);

        memcpy(CPU_brand_string + x * 16, &eax, 4);
        memcpy(CPU_brand_string + x * 16 + 4, &ebx, 4);
        memcpy(CPU_brand_string + x * 16 + 8, &ecx, 4);
        memcpy(CPU_brand_string + x * 16 + 12, &edx, 4);
    }

    CPU_brand_string[48] = '\0';
    memcpy(bun->CPU, CPU_brand_string, 49);

    // CPU Architecture
    SYSTEM_INFO CPU;
    GetNativeSystemInfo(&CPU);

    switch (CPU.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64:
        strncpy(bun->CPU_Architecture, "x86_64", 8);
        break;
    case PROCESSOR_ARCHITECTURE_ARM64:
        strncpy(bun->CPU_Architecture, "ARM64", 8);
        break;
    case PROCESSOR_ARCHITECTURE_INTEL:
        strncpy(bun->CPU_Architecture, "x86", 8);
        break;
    default:
        strncpy(bun->CPU_Architecture, "Unknown", 8);
        break;
    }
}

/*
cpuid logic (__get_cpuid();)

cpuid fills 4 registers with 4 integers. These integers are interpreted as raw ASCII bytes denoting characters of the CPU brand string.
The hex number that is passed as an arg is a function number. Not memory location or ID or pointer just function number that tells CPU what info to get.
It then takes 4 unsigned integers that get filled when the function is called.
The CPU brand string is a total of 47 characters and one null terminating character total 48 bytes.
Now for each call 4 bytes get filled and we make 3 calls, each call fills 16 bytes (4 bytes each) so 3 x 16 = 48 bytes in total.
We use offset to fill these bytes into our brand string buffer.
The offset denotes the start of filling for each call. First we start from 0 * 16 which is 0 so from index 0 we fill 4 bytes add + 4 and fill next 4 bytes, + 8 then + 12.
Similarly for the second call we do 1 * 16 which is 16 so now the starting point is 16 and then we continue.
Same with the third call we do 2 * 16 which is 32 so now the starting point is 32 and then we continue again till index 47 and 48 is '\0'.
Then we use memcpy to copy the whole brandstring into our bun struct.
*/
