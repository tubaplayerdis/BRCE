#pragma once
#include "ChatMessageHooks.h"
#include "GlobalHooks.h"

namespace hooks
{
	inline void EnableAllHooks() {
		AddChatMessage::Enable();
		BeginPlay::Enable();
	}

	inline void DisableAllHooks() {
		//Disable all hooks in one place
		AddChatMessage::Disable();
		BeginPlay::Disable();
	}
}