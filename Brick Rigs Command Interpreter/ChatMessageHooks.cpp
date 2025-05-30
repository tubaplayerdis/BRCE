#include "ChatMessageHooks.h"
#include "interpreter.h"
#include <MinHook.h>
#include "global.h"
#include <iostream>
#include <sstream>
#include <vector>

void __fastcall hooks::ClientRecieveChatMessage::HookedClientRecieveChatMessageFunction(SDK::ABrickPlayerController* This, SDK::FBrickChatMessage& ChatMessage)
{
    std::cout << ChatMessage.TextOption.ToString() << std::endl;
    PlayerInfo info;
    info.name = ChatMessage.Player.PlayerName.ToString();
    //modules::interpreter::interpretCommand(ChatMessage.TextOption.ToString(), info);
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
    std::cout << ChatMessage.TextOption.ToString() << std::endl;
    PlayerInfo info;
    info.name = ChatMessage.Player.PlayerName.ToString();
    if (ChatMessage.Type == SDK::EChatMessageType::Message && ChatMessage.TextOption.ToString().at(0) == '/') {
        std::string raw = ChatMessage.TextOption.ToString();
        std::string command = "";//grab the word after the slash and ending at the space.
        std::vector<std::string> args = std::vector<std::string>(); //Grab all strings passed after the first one as seperated by a space
        if (raw.length() > 2) {
            int numSpaces = std::count(raw.begin(), raw.end(), ' ');
            if (numSpaces == 0) {
                //no arguments
                command = raw.substr(1);
            }
            else {
                //arguments
                std::string rawArgs = raw.substr(raw.find_first_of(' '));
                std::istringstream iss(rawArgs);
                std::string word;

                while (iss >> word) {
                    args.push_back(word);
                }
            }
        }
        modules::interpreter::interpretCommand(ChatMessage.TextOption.ToString(), args, info);
    }
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
