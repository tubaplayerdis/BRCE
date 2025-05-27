#pragma once
#include "SDK.hpp"
#include "windows.h"

namespace hooks
{
	namespace BeginPlay
	{
		inline bool enabled = false;
		inline bool initalized = false;
		inline uintptr_t BeginPlayFunctionPointer = (uintptr_t)GetModuleHandle(NULL) + 0x8A3120; //Function is aprart of engine dll and has 142 base address in binary so use the dll module handle.

		using  BeginPlay_t = void(__fastcall*)(SDK::UWorld* This);
		inline  BeginPlay_t OriginalBeginPlayFunction = nullptr;

		void __fastcall HookedBeginPlayFunction(SDK::UWorld* This);

		bool Init();
		void Enable();
		void Disable();
	}
}
