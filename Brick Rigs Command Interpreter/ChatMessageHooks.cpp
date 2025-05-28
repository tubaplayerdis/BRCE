#include "ChatMessageHooks.h"
#include "interpreter.h"
#include <MinHook.h>
#include "global.h"

void __fastcall hooks::ClientRecieveChatMessage::HookedClientRecieveChatMessageFunction(SDK::ABrickPlayerController* This, SDK::FBrickChatMessage& ChatMessage)
{
    std::cout << ChatMessage.TextOption.ToString() << std::endl;
    PlayerInfo info;
    info.name = ChatMessage.Player.PlayerName.ToString();
    modules::interpreter::interpretCommand(ChatMessage.TextOption.ToString(), info);
    OriginalClientRecieveChatMessageFunction(This, ChatMessage);
}

bool hooks::ClientRecieveChatMessage::Init()
{
    if (initalized) return false;
    MH_STATUS ret = MH_CreateHook((LPVOID)ClientRecieveChatMessageFunctionPointer, &HookedClientRecieveChatMessageFunction, (void**)&OriginalClientRecieveChatMessageFunction);
    initalized = true;
    return ret == MH_OK;
}

void hooks::ClientRecieveChatMessage::Enable()
{
    if (!initalized || enabled) return;
    MH_EnableHook((LPVOID)ClientRecieveChatMessageFunctionPointer);
    enabled = true;
}

void hooks::ClientRecieveChatMessage::Disable()
{
    if (!initalized || !enabled) return;
    MH_DisableHook((LPVOID)ClientRecieveChatMessageFunctionPointer);
    enabled = false;
}

void __fastcall hooks::AddChatMessage::HookedAddChatMessageFunction(SDK::ABrickPlayerController* This, SDK::FBrickChatMessage& ChatMessage)
{
    std::cout << "Imcoming Chat Message!" << std::endl;
    std::cout << ChatMessage.TextOption.ToString() << std::endl;
    PlayerInfo info;
    info.name = ChatMessage.Player.PlayerName.ToString();
    if(ChatMessage.Type == SDK::EChatMessageType::Message) modules::interpreter::interpretCommand(ChatMessage.TextOption.ToString(), info);
    OriginalAddChatMessageFunction(This, ChatMessage);
}

bool hooks::AddChatMessage::Init()
{
    if (initalized) return false;
    MH_STATUS ret = MH_CreateHook((LPVOID)AddChatMessageFunctionPointer, &HookedAddChatMessageFunction, (void**)&OriginalAddChatMessageFunction);
    initalized = true;
    return ret == MH_OK;
}

void hooks::AddChatMessage::Enable()
{
    if (!initalized || enabled) return;
    MH_EnableHook((LPVOID)AddChatMessageFunctionPointer);
    enabled = true;
}

void hooks::AddChatMessage::Disable()
{
    if (!initalized || !enabled) return;
    MH_DisableHook((LPVOID)AddChatMessageFunctionPointer);
    enabled = false;
}

void hooks::constructors::FBrickChatMessageConstructor(SDK::FBrickChatMessage* This, SDK::EChatMessageType ChatType, SDK::ABrickPlayerController* PC)
{
    uintptr_t FBrickChatMessageConstructor = (uintptr_t)GetModuleHandle(NULL) + 0x0CEF980;

    using SetLoadoutAccessorFn = void(__fastcall*)(SDK::FBrickChatMessage* Thiss, SDK::EChatMessageType ChatTypee, SDK::ABrickPlayerController* PCC);
    SetLoadoutAccessorFn OnFBrickChatMessageConstructor = reinterpret_cast<SetLoadoutAccessorFn>(FBrickChatMessageConstructor);

    OnFBrickChatMessageConstructor(This, ChatType, PC);
}
