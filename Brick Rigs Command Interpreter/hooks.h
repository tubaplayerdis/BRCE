#pragma once
#include "ChatMessageHooks.h"
#include "GlobalHooks.h"
#include <chrono>

namespace hooks
{
	inline bool InitAllHooks() {
		std::cout << "Finding Hooks!" << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		bool ACMHook = AddChatMessage::Init();
		bool BPHook = BeginPlay::Init();
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Elapsed Time Finding Hooks: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
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