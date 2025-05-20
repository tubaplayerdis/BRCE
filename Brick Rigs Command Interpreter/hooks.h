#pragma once
#include "ChatMessageHooks.h"

namespace hooks
{
	inline void DisableAllHooks() {
		//Disable all hooks in one place
		AddChatMessage::Disable();
	}
}