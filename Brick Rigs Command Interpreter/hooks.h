#pragma once
#include "ChatMessageHooks.h"
#include "GlobalHooks.h"

namespace hooks
{
	inline bool InitAllHooks() {
		std::cout << "Starting Hook Searches!" << std::endl;
		bool ACMHook = AddChatMessage::Init();
		bool BPHook = BeginPlay::Init();
		std::cout << "Completed!" << std::endl;
		if (!ACMHook || !BPHook) {
			//print cases
			std::cout << "ACMHOOK: " << ACMHook << std::endl;
			std::cout << "BPHOOK: " << BPHook << std::endl;
			return false;
		}
		return true;
	}

	inline void EnableAllHooks() {
		AddChatMessage::Enable();
		BeginPlay::Enable();
		//PossessedBy::Enable();
	}

	inline void DisableAllHooks() {
		//Disable all hooks in one place
		AddChatMessage::Disable();
		BeginPlay::Disable();
		//PossessedBy::Disable();
	}
}