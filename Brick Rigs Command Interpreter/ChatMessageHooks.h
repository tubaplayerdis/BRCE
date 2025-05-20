#pragma once
#include "SDK.hpp"
#include "windows.h"

namespace hooks
{
	//DO NOT USE THIS HOOK. It is called when distributing messages not when a new on is added.
	namespace ClientRecieveChatMessage
	{
		inline bool enabled = false;
		inline bool initalized = false;
		inline uintptr_t ClientRecieveChatMessageFunctionPointer = (uintptr_t)GetModuleHandle(NULL) + 0x0E3CB30;

		using  ClientRecieveChatMessage_t = void(__fastcall*)(SDK::ABrickPlayerController* This, SDK::FBrickChatMessage& ChatMessage);
		inline  ClientRecieveChatMessage_t OriginalClientRecieveChatMessageFunction = nullptr;

		void __fastcall HookedClientRecieveChatMessageFunction(SDK::ABrickPlayerController* This, SDK::FBrickChatMessage& ChatMessage);

		bool Init();
		void Enable();
		void Disable();
	}

	namespace AddChatMessage
	{
		inline bool enabled = false;
		inline bool initalized = false;
		inline uintptr_t AddChatMessageFunctionPointer = (uintptr_t)GetModuleHandle(NULL) + 0x0CF5390;

		using  AddChatMessage_t = void(__fastcall*)(SDK::ABrickPlayerController* This, SDK::FBrickChatMessage& ChatMessage);
		inline  AddChatMessage_t OriginalAddChatMessageFunction = nullptr;

		void __fastcall HookedAddChatMessageFunction(SDK::ABrickPlayerController* This, SDK::FBrickChatMessage& ChatMessage);

		bool Init();
		void Enable();
		void Disable();
	}

	namespace constructors
	{
		//Use this by passing a valid structure created with the default constructor. The last player controller is the intended recipiet of the message.
		void FBrickChatMessageConstructor(SDK::FBrickChatMessage* This, SDK::EChatMessageType ChatType, SDK::ABrickPlayerController* PC);
	}
}
