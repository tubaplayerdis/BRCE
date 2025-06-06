/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Aaron Wilk 2025, All rights reserved.                     */
/*                                                                            */
/*    Module:     hooks.h                                                     */
/*    Author:     Aaron Wilk                                                  */
/*    Created:    3 May 2025                                                  */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

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
		bool OMHook = OpenMenu::Init();
		bool SYNCHook = Functions::SynchronizeProperties::Init();
		bool ONJHook = OnPlayerJoined::Init();
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Elapsed Time Finding Hooks: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
		if (!ACMHook || !BPHook || !OMHook || !SYNCHook || !ONJHook) {
			//print cases
			std::cout << "ACMHOOK: " << ACMHook << std::endl;
			std::cout << "BPHOOK: " << BPHook << std::endl;
			std::cout << "OMHOOK: " << OMHook << std::endl;
			std::cout << "SYNCHOOK: " << SYNCHook << std::endl;
			std::cout << "ONJHOOK:" << ONJHook << std::endl;
			return false;
		}
		return true;
	}

	inline void EnableAllHooks() {
		AddChatMessage::Enable();
		BeginPlay::Enable();
		OpenMenu::Enable();
		OnPlayerJoined::Enable();
		//PossessedBy::Enable();
	}

	inline void DisableAllHooks() {
		//Disable all hooks in one place
		AddChatMessage::Disable();
		BeginPlay::Disable();
		OpenMenu::Disable();
		//PossessedBy::Disable();
	}
}