// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "kiero.h"
#include "imgui.h"
#include "stdio.h"
#include <d3d11.h>
#include <dxgi.h>
#include "menu.h"

#pragma comment(lib, "MinHook.x64.lib")

FILE* p_file{ nullptr };

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    #ifdef _DEBUG //If in debug version enable console.
        AllocConsole();
        freopen_s(&p_file, "CONIN$", "r", stdin);
        freopen_s(&p_file, "CONOUT$", "w", stdout);
        freopen_s(&p_file, "CONOUT$", "w", stderr);
    #endif // _DEBUG

    bool init_hook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&menu::oPresent, menu::renderLoop);
            init_hook = true;
        }
    } while (!init_hook);

    //Run Main Loop Logic To Be Abstracted into another class/namespace. Most Likley Global.

    return TRUE;

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        ImGui::DestroyContext();
        kiero::shutdown();
        break;
    }
    return TRUE;
}

