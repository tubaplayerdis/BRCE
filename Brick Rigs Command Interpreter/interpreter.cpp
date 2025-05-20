#include "interpreter.h"
#include "modules.h"
#include <thread>
#include <functional>
#include <SDK.hpp>
#include "global.h"
#include "hooks.h"

void modules::interpreter::Commands::Night(PlayerInfo info)
{
    using namespace global;
    auto cur = GetBrickGameState()->GetMatchSettings();
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.TimeOfDay = 0.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::interpreter::Commands::Day(PlayerInfo info)
{
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.TimeOfDay = 12.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::interpreter::Commands::Rain(PlayerInfo info)
{
}

void modules::interpreter::Commands::Sun(PlayerInfo info)
{
}

size_t hash_string(const std::string& str) {
    std::hash<std::string> hasher;
    return hasher(str);
}

constexpr size_t hs(const char* str) {
    std::size_t hash = 14695981039346656037ull;
    while (*str) {
        hash ^= static_cast<unsigned char>(*str++);
        hash *= 1099511628211ull;
    }
    return hash;
}

void modules::interpreter::interpretCommand(std::string command, PlayerInfo info)
{
	size_t hash_val = hash_string(command);

	switch (hash_val) {
		case hs("/night"):
            Commands::Night(info);
            break;
        case hs("/day"):
            Commands::Day(info);
            break;
        default:
            break;
	}
}

void modules::interpreter::sendUserSpecificMessage(PlayerInfo info, std::string message)
{
    
    SDK::FText Fmessage = SDK::UKismetTextLibrary::Conv_StringToText(UC::FString(global::to_wstring_n(message).c_str()));
    auto SMessage = SDK::FBrickChatMessage();
    SMessage.TextOption = Fmessage;
    SDK::ABrickPlayerController* cont = global::GetBrickPlayerControllerFromName(info.name);
    if (cont != nullptr) {
        hooks::constructors::FBrickChatMessageConstructor(&SMessage, SDK::EChatMessageType::Message, global::GetBrickPlayerControllerFromName(info.name));
        global::GetBrickGameSession()->AddChatMessage(&SMessage);
    }
    else {
        auto PlayerController = global::GetBrickPlayerController();
        SDK::FText FmessageN = SDK::UKismetTextLibrary::Conv_StringToText(SDK::UKismetStringLibrary::Concat_StrStr(UC::FString(L"Message Failed To Send To: "), UC::FString(global::to_wstring_n(info.name).c_str())));
        auto SMessageN = SDK::FBrickChatMessage();
        SMessageN.TextOption = FmessageN;
        global::GetBrickGameSession()->AddChatMessage(&SMessageN);
    }
}

void modules::interpreter::Commands::Command(PlayerInfo info)
{
    sendUserSpecificMessage(info, CommandList::message);
}

void modules::interpreter::Commands::Enable(PlayerInfo info, std::string command)
{
}

void modules::interpreter::Commands::Disable(PlayerInfo info, std::string command)
{
}

void modules::interpreter::Commands::Fly(PlayerInfo info)
{
}

void modules::interpreter::Commands::Walk(PlayerInfo info)
{
}

void modules::interpreter::Commands::Speed(PlayerInfo info, char level)
{
}

void modules::interpreter::Commands::Teleport(PlayerInfo info)
{
}

void modules::interpreter::Commands::Ghost(PlayerInfo info)
{
}
