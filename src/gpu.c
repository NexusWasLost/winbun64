#include <stdio.h>
#include <windows.h>
#include <dxgi.h>
#include "../headers/sysFunctions.h"
#include "../headers/sysInfo.h"

void getGPU(sysInfo* system){
    IDXGIFactory1* factory = NULL;

    HRESULT result = CreateDXGIFactory1(&IID_IDXGIFactory1, (void**)&factory);
    if(FAILED(result)){
        printf("Unable to get GPU information...");
        return;
    }

    //create adapter pointer
    IDXGIAdapter1* adapter = NULL;
    UINT index = 0;
    int GPUcounter = 0;
    system->GPU1[0] = L'\0';
    system->GPU2[0] = L'\0';

    while(TRUE){
        if(GPUcounter >= 2) return;

        HRESULT hr = factory->lpVtbl->EnumAdapters1(factory, index, &adapter);

        //no more or any adapters found
        if(hr == DXGI_ERROR_NOT_FOUND) break;

        if(FAILED(hr)){
            printf("Failed to get GPU Information...");
            return;
        }

        DXGI_ADAPTER_DESC1 desc;
        adapter->lpVtbl->GetDesc1(adapter, &desc);
        UINT64 vram = desc.DedicatedVideoMemory / (1024ULL * 1024ULL);
        // wprintf(L"GPU: %ls, VRAM: %llu MB\n", desc.Description, vram);

        if(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE){
            adapter->lpVtbl->Release(adapter);
            adapter = NULL;
            index++;
            continue;
        }

        //switch index and store GPU informations
        switch (GPUcounter) {
        case 0:
            memcpy(system->GPU1, desc.Description, 128);
            system->totalVRAM1 = vram;
            GPUcounter++;
            break;

        case 1:
            memcpy(system->GPU2, desc.Description, 128);
            system->totalVRAM2 = vram;
            GPUcounter++;
            break;

        default:
            break;
        }

        adapter->lpVtbl->Release(adapter);
        adapter = NULL;

        index++;
    }
}
