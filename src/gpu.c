#include <stdio.h>
#include <windows.h>
#include <dxgi.h>
#include "winbun.h"
#include "winbun_functions.h"

void getGPU(WINBUN* bun){
    IDXGIFactory1* factory = NULL;

    HRESULT result = CreateDXGIFactory1(&IID_IDXGIFactory1, (void**)&factory);
    if(FAILED(result)){
        printf("Unable to get GPU information...");
        return;
    }

    //create adapter pointer
    IDXGIAdapter1* adapter = NULL;
    UINT index = 0;
    bun->gpuCount = 0;

    while(TRUE){
        if(bun->gpuCount >= MAX_GPU_COUNT) return;

        HRESULT hr = factory->lpVtbl->EnumAdapters1(factory, index, &adapter);

        //no more or any adapters found
        if(hr == DXGI_ERROR_NOT_FOUND) break;

        if(FAILED(hr)){
            printf("Failed to get GPU Information...");
            return;
        }

        DXGI_ADAPTER_DESC1 desc;
        adapter->lpVtbl->GetDesc1(adapter, &desc);
        // wprintf(L"GPU: %ls, VRAM: %llu MB\n", desc.Description, vram); //used for debugging

        //dont account for any software renderer GPU like VMWare and Microsoft renderer
        if(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE){
            adapter->lpVtbl->Release(adapter);
            adapter = NULL;
            index++;
            continue;
        }

        //looks a bit too cursed, so here is the explanation for the below line.
        /*
        bun->gpu is an array to GPU struct and we use bun->gpuCount as index.
        bun->gpuCount is an integer.
        Now gpu is a struct containing a wchar_t array called GPU_Name therefore passing it
        to a function will result in a decay to a pointer and thats what memcpy expects.
        */
        memcpy(bun->gpu[bun->gpuCount].GPU_Name, desc.Description, 128);
        bun->gpu[bun->gpuCount].GPU_Name[127] = L'\0';
        bun->gpu[bun->gpuCount].totalVRAM = (desc.DedicatedVideoMemory / (1024ULL * 1024ULL));
        ++bun->gpuCount;

        adapter->lpVtbl->Release(adapter);
        adapter = NULL;

        index++;
    }
}
