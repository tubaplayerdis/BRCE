#pragma once
#include "ChatMessageHooks.h"

namespace hooks
{
	inline void DisableAllHooks() {
		ClientRecieveChatMessage::Disable();
	}
}