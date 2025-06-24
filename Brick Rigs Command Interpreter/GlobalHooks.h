/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Aaron Wilk 2025, All rights reserved.                     */
/*                                                                            */
/*    Module:     GlobalHooks.h                                               */
/*    Author:     Aaron Wilk                                                  */
/*    Created:    27 May 2025                                                 */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma once
#include "SDK.hpp"
#include "windows.h"
#include <Psapi.h>

namespace hooks
{
    inline uintptr_t GetModuleBaseN() {
        return (uintptr_t)GetModuleHandle(NULL);
    }

    inline uintptr_t GetModuleBase(const wchar_t* moduleName) {
        return (uintptr_t)GetModuleHandle(moduleName);
    }

    inline size_t GetModuleSizeN() {
        MODULEINFO info = {};
        GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &info, sizeof(info));
        return info.SizeOfImage;
    }

    inline size_t GetModuleSize(const wchar_t* moduleName) {
        MODULEINFO info = {};
        GetModuleInformation(GetCurrentProcess(), GetModuleHandleW(moduleName), &info, sizeof(info));
        return info.SizeOfImage;
    }

    inline uintptr_t FindPattern(const char* pattern, const char* mask, uintptr_t base, size_t size) {
        size_t patternLen = strlen(mask);

        for (size_t i = 0; i < size - patternLen; i++) {
            bool found = true;

            for (size_t j = 0; j < patternLen; j++) {
                if (mask[j] != '?' && pattern[j] != *(char*)(base + i + j)) {
                    found = false;
                    break;
                }
            }

            if (found)
                return base + i;
        }

        return 0;
    }

	namespace BeginPlay
	{
		inline bool enabled = false;
		inline bool initalized = false;
		inline const char* pattern = "\x40\x53\x48\x83\xEC\x20\x48\x8B\xD9\x48\x8B\x89\x18\x01\x00\x00\x48\x85\xC9\x74\x1E\x48\x8B\x01";
		inline const char* mask = "xxxxxxxxxxxxxxxxxxxxxxx";
        inline uintptr_t BeginPlayFunctionPointer = 0; //Initalized in Init().

		using  BeginPlay_t = void(__fastcall*)(SDK::UWorld* This);
		inline  BeginPlay_t OriginalBeginPlayFunction = nullptr;

		void __fastcall HookedBeginPlayFunction(SDK::UWorld* This);

		bool Init();
		void Enable();
		void Disable();
	}

    //Use this to render primatives. Not currently used. The Signature should stay consistent unless UE version change
    namespace DrawTransition
    {
        inline bool enabled = false;
        inline bool initalized = false;
        inline const char* pattern = "\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x40\x80\xB9\x88\x00\x00\x00\x00\x48\x8B\xF2\x48\x8B\xF9\x0F\x85\x00\x00\x00\x00\x8B\x41\x08\x45\x33\xC0\xC1\xE8\x04\xA8\x01\x41\x8B\xC0";
        inline const char* mask = "xxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxx";
        inline uintptr_t DrawTransitionFunctionPointer = 0;

        using DrawTransition_t = void(__fastcall*)(SDK::UGameViewportClient* This, SDK::UCanvas* Canvas);
        inline DrawTransition_t OriginalDrawTransitionFunction = nullptr;

        void __fastcall HookedDrawTransitionFunction(SDK::UGameViewportClient* This, SDK::UCanvas* Canvas);

        bool Init();
        void Enable();
        void Disable();
    }

    namespace OpenMenu
    {
        inline bool enabled = false;
        inline bool initalized = false;
        inline const char* pattern = "\x48\x89\x54\x24\x10\x55\x53\x56\x57\x41\x54\x41\x55\x48\x8D\x6C\x24\xD1\x48\x81\xEC";
        inline const char* mask = "xxxxxxxxxxxxxxxxxxxx";
        inline uintptr_t OpenMenuFunctionPointer = 0;

        using OpenMenu_t = void(__fastcall*)(SDK::UMenuWidget* This, SDK::FName InMenu);
        inline OpenMenu_t OriginalOpenMenuFunction = nullptr;

        void __fastcall HookedOpenMenuFunction(SDK::UMenuWidget* This, SDK::FName InMenu);

        bool Init();
        void Enable();
        void Disable();
    }

    namespace OnPlayerJoined
    {
        inline bool enabled = false;
        inline bool initalized = false;
        inline const char* pattern = "\x48\x83\xEC\x48\x48\x89\x5C\x24\x58\x33\xDB\x48\x89\x74\x24\x68\x48\x89\x7C\x24\x40";
        inline const char* mask = "xxxxxxxxxxxxxxxxxxxx";
        inline uintptr_t OnPlayerJoinedFunctionPointer = 0;

        using OnPlayerJoined_t = void(__fastcall*)(SDK::ABrickGameSession* This, SDK::ABrickPlayerController* PC);
        inline OnPlayerJoined_t OriginalOnPlayerJoinedFunction = nullptr;

        void __fastcall HookedOnPlayerJoinedFunction(SDK::ABrickGameSession* This, SDK::ABrickPlayerController* PC);

        bool Init();
        void Enable();
        void Disable();
    }

    namespace LoadMap
    {
        inline bool enabled = false;
        inline bool initalized = false;
        inline const char* pattern = "\x48\x89\x5C\x24\x20\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\x80\x48\x81\xEC\x80\x01\x00\x00\x0F\x29\xBC\x24\x60\x01\x00\x00\x48\x8B\x05\x65\x77\xA7\x01";
        inline const char* mask = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
        inline uintptr_t LoadMapFunctionPointer = 0;

        using LoadMap_t = char(__fastcall*)(SDK::UEngine* This, SDK::FWorldContext* WorldContext, void* URL, void* Pending, void* Error);
        inline LoadMap_t OriginalLoadMapFunction = nullptr;

        char __fastcall HookedLoadMapFunction(SDK::UEngine* This, SDK::FWorldContext* WorldContext, void* URL, void* Pending, void* Error);

        bool Init();
        void Enable();
        void Disable();
    }

    namespace StartPlay
    {
        inline bool enabled = false;
        inline bool initalized = false;
        inline const char* pattern = "\x40\x53\x48\x83\xEC\x20\x48\x8B\xD9\x48\x8B\x89\x80\x02\x00\x00\x48\x8B\x01";
        inline const char* mask = "xxxxxxxxxxxxxxxxxxx";
        inline uintptr_t StartPlayFunctionPointer = 0;

        using StartPlay_t = void(__fastcall*)(SDK::AGameMode* This);
        inline StartPlay_t OriginalStartPlayFunction = nullptr;

        void __fastcall HookedStartPlayFunction(SDK::AGameMode* This);

        bool Init();
        void Enable();
        void Disable();
    }

    namespace Functions
    {
        namespace CreateWidget
        {
            SDK::UUserWidget* CreateWidget(SDK::UWorld* OwningObject, SDK::TSubclassOf<SDK::UUserWidget> UserWidgetClass, SDK::FName WidgetName);
        }

        namespace OpenPopup
        {
            char OpenPopup(SDK::UWindowManagerWidget* This, SDK::UClass* HandleT, SDK::UPopupParams* PopupParams, bool bToggleOpen);
        }

        namespace Initalize
        {
            char Initalize(SDK::UPopupContainerWidget* This);
        }

        namespace SynchronizeProperties
        {   
            inline const char* pattern = ""; //Signature is failng. Currently using raw address
            inline const char* mask = "";
            inline uintptr_t SynchronizePropertiesFunction = 0;//Calculated at first run.
            void SynchronizeProperties(SDK::UBrickBorder* This);
            bool Init(); //Find the address
        }

        namespace isServer
        {
            bool isServer(SDK::UNetDriver* driver);
        }

        namespace UpdateWorldSetupParams
        {
            void UpdateWorldSetupParams(bool fadeIn);
        }

    }
}
