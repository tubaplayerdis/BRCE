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
        inline uintptr_t BeginPlayFunctionPointer = 0; //This is found in init.

		using  BeginPlay_t = void(__fastcall*)(SDK::UWorld* This);
		inline  BeginPlay_t OriginalBeginPlayFunction = nullptr;

		void __fastcall HookedBeginPlayFunction(SDK::UWorld* This);

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
    }
}
