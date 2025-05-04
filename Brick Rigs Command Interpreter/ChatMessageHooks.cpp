#include "ChatMessageHooks.h"
#include "modules.h"
#include <MinHook.h>
#include "global.h"

void __fastcall hooks::ClientRecieveChatMessage::HookedClientRecieveChatMessageFunction(SDK::ABrickPlayerController* This, SDK::FBrickChatMessage& ChatMessage)
{
    std::cout << ChatMessage.TextOption.ToString() << std::endl;
    modules::CommandInterpreter::interpretCommand(ChatMessage.TextOption.ToString());
    OriginalClientRecieveChatMessageFunction(This, ChatMessage);
}

bool hooks::ClientRecieveChatMessage::Init()
{
    MH_STATUS ret = MH_CreateHook((LPVOID)ClientRecieveChatMessageFunctionPointer, &HookedClientRecieveChatMessageFunction, (void**)&OriginalClientRecieveChatMessageFunction);
    if (ret == MH_OK) return 1;
    return 0;
}

void hooks::ClientRecieveChatMessage::Enable()
{
    MH_EnableHook((LPVOID)ClientRecieveChatMessageFunctionPointer);
}

void hooks::ClientRecieveChatMessage::Disable()
{
    MH_DisableHook((LPVOID)ClientRecieveChatMessageFunctionPointer);
}
