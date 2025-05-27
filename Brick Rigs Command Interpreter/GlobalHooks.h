#pragma once
#include "SDK.hpp"
#include "windows.h"

namespace hooks
{
	namespace BeginPlay
	{
		inline bool enabled = false;
		inline bool initalized = false;
		inline uintptr_t BeginPlayFunctionPointer = (uintptr_t)GetModuleHandle(NULL) + 0x08A3120; //IDA lists the base of the this function as 142 instead of 140. My assumption is that it is static address tied to the engine.

		using  BeginPlay_t = void(__fastcall*)(SDK::UWorld* This);
		inline  BeginPlay_t OriginalBeginPlayFunction = nullptr;

		void __fastcall HookedBeginPlayFunction(SDK::UWorld* This);

		bool Init();
		void Enable();
		void Disable();
	}
}
