#include "ChatMessageHooks.h"
#include "interpreter.h"
#include <MinHook.h>
#include "global.h"
#include <iostream>
#include <sstream>
#include "SDK.hpp"
#include <vector>
#include "GlobalHooks.h"

void __fastcall hooks::AddChatMessage::HookedAddChatMessageFunction(SDK::ABrickGameSession* This, SDK::FBrickChatMessage& ChatMessage)
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
                command = raw.substr(0);
            }
            else {
                //arguments
                command = raw.substr(0, raw.find_first_of(' '));
                std::string rawArgs = raw.substr(raw.find_first_of(' '));
                std::istringstream iss(rawArgs);
                std::string word;

                while (iss >> word) {
                    word.erase(std::remove(word.begin(), word.end(), ' '));
                    args.push_back(word);
                }
            }
        }
        if(global::IsHost()) modules::interpreter::interpretCommand(command, args, info);
    }
    OriginalAddChatMessageFunction(This, ChatMessage);
}

bool hooks::AddChatMessage::Init()
{
    if (initalized) return false;
    AddChatMessageFunctionPointer = (uintptr_t)GetModuleHandle(NULL) + 0x0E3CB30;//FindPattern(pattern, mask, GetModuleBaseN(), GetModuleSizeN());
    if (AddChatMessageFunctionPointer == 0) return false;
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
    uintptr_t FBrickChatMessageConstructorP = (uintptr_t)GetModuleHandle(NULL) + 0x0CEF980;

    using SetLoadoutAccessorFn = void(__fastcall*)(SDK::FBrickChatMessage* Thiss, SDK::EChatMessageType ChatTypee, SDK::ABrickPlayerController* PCC);
    SetLoadoutAccessorFn OnFBrickChatMessageConstructor = reinterpret_cast<SetLoadoutAccessorFn>(FBrickChatMessageConstructorP);

    OnFBrickChatMessageConstructor(This, ChatType, PC);
}

void hooks::constructors::FSlateColorConstructor(SDK::FSlateColor* This, SDK::FLinearColor* InColor)
{
    const char* pattern =
        "\x0F\x10\x02\x33\xC0\x0F\x11\x01"
        "\x48\x89\x41\x18\x48\x89\x41\x20"
        "\x48\x8B\xC1\xC6\x41\x10\x00\xC3";
    const char* mask = "xxxxxxxxxxxxxxxxxxxxxxxx";

    uintptr_t FSlateColorConstructorPointer = FindPattern(pattern, mask, GetModuleBaseN(), GetModuleSizeN());

    using FSlateColorConstructorFn = void(__fastcall*)(SDK::FSlateColor* Thiss, SDK::FLinearColor* InColorr);
    FSlateColorConstructorFn OnFSlateColorConstructor = reinterpret_cast<FSlateColorConstructorFn>(FSlateColorConstructorPointer);

    OnFSlateColorConstructor(This, InColor);
}

SDK::FLinearColor hooks::constructors::CreateLinearColor(float R, float G, float B, float A)
{
    SDK::FLinearColor ret = SDK::FLinearColor();
    ret.A = A;
    ret.R = R/255.0f;
    ret.G = G/255.0f;
    ret.B = B/255.0f;
    return ret;
}

SDK::FLinearColor hooks::constructors::CreateLinearColorNorm(float R, float G, float B, float A)
{
    SDK::FLinearColor ret = SDK::FLinearColor();
    ret.A = A;
    ret.R = R;
    ret.G = G;
    ret.B = B;
    return ret;
}

SDK::FSlateColor hooks::constructors::CreateSlateColor(float R, float G, float B, float A)
{
    SDK::FSlateColor ret;
    SDK::FLinearColor col = CreateLinearColor(R, G, B, A);
    FSlateColorConstructor(&ret, &col);
    return ret;
}
