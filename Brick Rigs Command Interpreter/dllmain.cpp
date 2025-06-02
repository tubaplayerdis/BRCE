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
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#pragma comment(lib, "MinHook.x64.lib")

FILE* pStdIn = nullptr;
FILE* pStdOut = nullptr;
FILE* pStdErr = nullptr;

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    HMODULE hModule = static_cast<HMODULE>(lpReserved);

    #ifdef _DEBUG //If in debug version enable console.
        AllocConsole();
        freopen_s(&pStdIn, "CONIN$", "r", stdin);
        freopen_s(&pStdOut, "CONOUT$", "w", stdout);
        freopen_s(&pStdErr, "CONOUT$", "w", stderr);
        SetConsoleTitleW(L"Brick Rigs Command Interpreter");
        SetConsoleOutputCP(CP_UTF8);
    #endif // _DEBUG

    if (GetModuleHandle(L"MinHook.x64.dll") == NULL) {
        MessageBox(GetActiveWindow(), L"Please Inject MinHook.x64.dll Before Loading. Uninjecting BRCI.", L"Uninjecting BRCI", MB_OK);
        FreeLibraryAndExitThread(hModule, 0);
        return 0;
    }

    #ifdef _DEBUG //If in debug use imgui. otherwise dont
        bool init_hook = false;
        do
        {
            if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
            {
                kiero::bind(8, (void**)&menu::oPresent, menu::renderLoop);
                init_hook = true;
            }
        } while (!init_hook);
    #endif // _DEBUG

    #ifdef _RELEASE
        MH_Initialize(); //Kiero normally calls this, but in release we need to call it.
    #endif // _RELEASE

    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST); //Prevent random freezes

    mainLoop();

    Sleep(200); //Let render thread stop

    #ifdef _DEBUG //No need to shutdown kiero(dx11 hook) if it was never ran.
        kiero::unbind(8);
        ImGui_ImplWin32_Shutdown();
        ImGui_ImplDX11_Shutdown();
        ImGui::DestroyContext();
        kiero::shutdown();
    #endif // _DEBUG

    
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
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

    FreeLibraryAndExitThread(hModule, 0);
    return 0;

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
    }
    return TRUE;
}

