#pragma once
#include "SDK.hpp"
#include "windows.h"

namespace hooks
{
	namespace AddChatMessage
	{
		inline bool enabled = false;
		inline bool initalized = false;
		inline const char* pattern =
			"\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x40\x48\x8B\xFA\x48\x8B\xF1"
			"\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00";
		inline const char* mask =
			"xxxxxxxxxxxxxxxxx????xxxx????";
		inline uintptr_t AddChatMessageFunctionPointer = 0;//Initalized in Init()

		using  AddChatMessage_t = void(__fastcall*)(SDK::ABrickGameSession* This, SDK::FBrickChatMessage& ChatMessage);
		inline  AddChatMessage_t OriginalAddChatMessageFunction = nullptr;

		void __fastcall HookedAddChatMessageFunction(SDK::ABrickGameSession* This, SDK::FBrickChatMessage& ChatMessage);

		bool Init();
		void Enable();
		void Disable();
	}

	namespace constructors
	{
		//Use this by passing a valid structure created with the default constructor. The last player controller is the intended recipiet of the message.
		void FBrickChatMessageConstructor(SDK::FBrickChatMessage* This, SDK::EChatMessageType ChatType, SDK::ABrickPlayerController* PC);

		void FSlateColorConstructor(SDK::FSlateColor* This, SDK::FLinearColor* InColor);

		/*
		* Colors are 0-255 and A is 0-1
		* FLinearColor expect values from 0-1 not 0-255, given that, 0-255 values are taken and mapped down in the function.
		*/
		SDK::FLinearColor CreateLinearColor(float R, float G, float B, float A);


		/*
		* Colors are 0-1 and A is 0-1
		* FLinearColor expect values from 0-1 not 0-255, and since this is the normal function, inputs are 0-1.
		*/
		SDK::FLinearColor CreateLinearColorNorm(float R, float G, float B, float A);

		/*
		* Colors are 0-255 and A is 0-1
		*/
		SDK::FSlateColor CreateSlateColor(float R, float G, float B, float A);
	}
}
