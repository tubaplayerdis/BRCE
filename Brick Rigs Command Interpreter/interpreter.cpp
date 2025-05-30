#include "interpreter.h"
#include "modules.h"
#include <thread>
#include <functional>
#include <SDK.hpp>
#include "global.h"
#include "hooks.h"

void modules::interpreter::Commands::Night(PlayerInfo info)
{
    if (!isNight) return;
    using namespace global;
    auto cur = GetBrickGameState()->GetMatchSettings();
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.TimeOfDay = 0.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::interpreter::Commands::Day(PlayerInfo info)
{
    if (!isDay) return;
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.TimeOfDay = 12.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::interpreter::Commands::Rain(PlayerInfo info)
{
    if (!isRain) return;
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.Weather->Weather.PrecipitationType = SDK::EPrecipitationType::Rain;
    cur.WorldSetupParams.Weather->Weather.PrecipitationIntensity = 100.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::interpreter::Commands::Sun(PlayerInfo info)
{
    if (!isSun) return;
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.Weather->Weather.PrecipitationType = SDK::EPrecipitationType::None;
    cur.WorldSetupParams.Weather->Weather.PrecipitationIntensity = 0.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::interpreter::Commands::BombGun(PlayerInfo info)
{
    if (!isBombGun) return;
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

void modules::interpreter::interpretCommand(std::string command, std::vector<std::string> args, PlayerInfo info)
{
	size_t hash_val = hash_string(command);

	switch (hash_val) {
        case hs("/enable"):
            //Hook the function that provides immediate feedback like when a vehicle is too large or sum. That would be better immediate feedback that works natively
            if (args.size() < 1) break;
            Commands::Toggle(info, args[0], true);
            break;
        case hs("/disable"):
            if (args.size() < 1) break;
            Commands::Toggle(info, args[0], false);
            break;
		case hs("/night"):
            Commands::Night(info);
            break;
        case hs("/day"):
            Commands::Day(info);
            break;
        case hs("/rain"):
            Commands::Rain(info);
            break;
        case hs("/sun"):
            Commands::Sun(info);
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

void modules::interpreter::sendMessageToAdmin(std::string message)
{
    SDK::FText Fmessage = SDK::UKismetTextLibrary::Conv_StringToText(UC::FString(global::to_wstring_n(message).c_str()));
    auto SMessage = SDK::FBrickChatMessage();
    hooks::constructors::FBrickChatMessageConstructor(&SMessage, SDK::EChatMessageType::Message, global::GetBrickPlayerController());
    SMessage.TextOption = Fmessage;
    global::GetBrickGameSession()->AddChatMessage(&SMessage);
}

void modules::interpreter::Commands::Command(PlayerInfo info)
{
    sendUserSpecificMessage(info, CommandList::message);
}

void modules::interpreter::Commands::Toggle(PlayerInfo info, std::string command, bool toggle)
{
    using namespace global;
    if (GetBrickPlayerControllerFromName(info.name) != GetBrickPlayerController()) return;
    size_t hash_val = hash_string(command);

    switch (hash_val) {
    case hs("night"):
        isNight = toggle;
        break;
    case hs("day"):
        isDay = toggle;
        break;
    case hs("rain"):
        isRain = toggle;
        break;
    case hs("sun"):
        isSun = toggle;
        break;
    default:
        break;
    }
}

void modules::interpreter::Commands::PersonalMessage(PlayerInfo info, std::string message)
{
    if (!isPM) return;
}

void modules::interpreter::Commands::Help(PlayerInfo info)
{
    
}

void modules::interpreter::Commands::Fly(PlayerInfo info)
{
    using namespace global;
    auto BrickPlayerController = GetBrickPlayerControllerFromName(info.name);
    if (BrickPlayerController == nullptr) return;
    BrickPlayerController->Character->CharacterMovement->MovementMode = SDK::EMovementMode::MOVE_Flying;
    //Change accel and speed values to appropriate levels
}

void modules::interpreter::Commands::Walk(PlayerInfo info)
{
    using namespace global;
    if (!isWalk) return;
    auto BrickPlayerController = GetBrickPlayerControllerFromName(info.name);
    if (BrickPlayerController == nullptr) return;
    BrickPlayerController->Character->CharacterMovement->MovementMode = SDK::EMovementMode::MOVE_Walking;
    //Return speed and accel to regular values
}

void modules::interpreter::Commands::Speed(PlayerInfo info, char level)
{
    if (!isSpeed) return;
}

void modules::interpreter::Commands::Teleport(PlayerInfo info)
{
    if (!isTeleport) return;
}

void modules::interpreter::Commands::Ghost(PlayerInfo info)
{
    if (!isGhost) return;
}

/*
Replace code with varius things.
*/
void modules::interpreter::Commands::Debug(PlayerInfo info)
{
    sendMessageToAdmin("This is a testing message. If you can see this, please tell me.");
}
