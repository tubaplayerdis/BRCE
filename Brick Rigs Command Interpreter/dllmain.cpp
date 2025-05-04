// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "kiero.h"
#include "imgui.h"
#include "stdio.h"
#include <d3d11.h>
#include <dxgi.h>
#include "menu.h"
#include "main.h"
#include <MinHook.h>

#pragma comment(lib, "MinHook.x64.lib")

FILE* pStdIn = nullptr;
FILE* pStdOut = nullptr;
FILE* pStdErr = nullptr;

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    #ifdef _DEBUG //If in debug version enable console.
        AllocConsole();
        freopen_s(&pStdIn, "CONIN$", "r", stdin);
        freopen_s(&pStdOut, "CONOUT$", "w", stdout);
        freopen_s(&pStdErr, "CONOUT$", "w", stderr);
        SetConsoleTitleW(L"Brick Rigs Command Interpreter");
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

    mainLoop();

    kiero::shutdown();
    MH_Uninitialize();
    
    #ifdef _DEBUG
        fclose(pStdIn);
        fclose(pStdOut);
        fclose(pStdErr);
        SetStdHandle(STD_INPUT_HANDLE, nullptr);
        SetStdHandle(STD_OUTPUT_HANDLE, nullptr);
        SetStdHandle(STD_ERROR_HANDLE, nullptr);
        FreeConsole();
        PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
    #endif 

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
        break;
    case DLL_PROCESS_DETACH:
        ImGui::DestroyContext();
        FreeLibraryAndExitThread(hModule, 0);
        break;
    }
    return TRUE;
}

