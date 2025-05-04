#pragma once
#include "SDK.hpp"
#include "windows.h"

namespace hooks
{
	namespace ClientRecieveChatMessage
	{
		inline uintptr_t ClientRecieveChatMessageFunctionPointer = (uintptr_t)GetModuleHandle(NULL) + 0x0E3CB30;

		using  ClientRecieveChatMessage_t = void(__fastcall*)(SDK::ABrickPlayerController* This, SDK::FBrickChatMessage& ChatMessage);
		inline  ClientRecieveChatMessage_t OriginalClientRecieveChatMessageFunction = nullptr;

		void __fastcall HookedClientRecieveChatMessageFunction(SDK::ABrickPlayerController* This, SDK::FBrickChatMessage& ChatMessage);

		bool Init();
		void Enable();
		void Disable();
	}
}
