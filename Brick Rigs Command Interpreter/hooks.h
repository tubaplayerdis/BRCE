#pragma once
#include "ChatMessageHooks.h"
#include "GlobalHooks.h"

namespace hooks
{
	inline bool InitAllHooks() {
		bool ACMHook = AddChatMessage::Init();
		bool BPHook = BeginPlay::Init();
		bool PBHook = PossessedBy::Init();
		if (!ACMHook || !BPHook || !PBHook) {
			//print cases
			std::cout << "ACMHOOK: " << ACMHook << std::endl;
			std::cout << "BPHOOK: " << BPHook << std::endl;
			std::cout << "PBHOOK: " << PBHook << std::endl;
			return false;
		}
		return true;
	}

	inline void EnableAllHooks() {
		AddChatMessage::Enable();
		BeginPlay::Enable();
		PossessedBy::Enable();
	}

	inline void DisableAllHooks() {
		//Disable all hooks in one place
		AddChatMessage::Disable();
		BeginPlay::Disable();
		PossessedBy::Disable();
	}
}