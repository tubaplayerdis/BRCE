/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Aaron Wilk 2025, All rights reserved.                     */
/*                                                                            */
/*    Module:     Interpreter.cpp                                             */
/*    Author:     Aaron Wilk                                                  */
/*    Created:    19 May 2025                                                 */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "interpreter.h"
#include "modules.h"
#include <thread>
#include <functional>
#include <SDK.hpp>
#include "hooks.h"
#include "global.h"

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
    cur.WorldSetupParams.Weather->Weather.PrecipitationType = SDK::EPrecipitationType::Rain;
    cur.WorldSetupParams.Weather->Weather.PrecipitationIntensity = 100.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::interpreter::Commands::Sun(PlayerInfo info)
{
    if (!isSun) return;
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
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

    for (std::string i : args) {
        std::cout << i << std::endl;
    }

	switch (hash_val) {
        case hs("/on"):
            if (args.size() < 1) break;
            Commands::Toggle(info, args[0], true);
            break;
        case hs("/off"):
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
        case hs("/fly"):
            Commands::Fly(info);
            break;
        case hs("/walk"):
            Commands::Walk(info);
            break;
        default:
            break;
	}
}

void modules::interpreter::sendUserSpecificMessage(PlayerInfo info, std::string message)
{
    if (!global::isMapValid()) return;
    SDK::FText Fmessage = TEXT(global::to_wstring_n(message).c_str());
    SDK::FBrickChatMessage SMessage;
    SDK::ABrickPlayerController* cont = global::GetBrickPlayerControllerFromName(info.name);
    if (cont != nullptr) {
        hooks::constructors::FBrickChatMessageConstructor(&SMessage, SDK::EChatMessageType::Message, cont);
        SMessage.TextOption = Fmessage;
        SMessage.Type = SDK::EChatMessageType::Message;
        SMessage.IntOption = 1;//Equates to SDK::EChatContext. use this to get admin messages or other types of messages.
        SMessage.Player.PlayerId = global::GetBrickPlayerController()->GetPlayerId();
        SMessage.Player.PlayerName = STRING(L"Command Interpreter");
        cont->ClientReceiveChatMessage(SMessage);
    }
    else {
        auto PlayerController = global::GetBrickPlayerController();
        if (PlayerController == nullptr) return;
        SDK::FText FmessageN = SDK::UKismetTextLibrary::Conv_StringToText(SDK::UKismetStringLibrary::Concat_StrStr(UC::FString(L"Message Failed To Send To: "), UC::FString(global::to_wstring_n(info.name).c_str())));
        auto SMessageN = SDK::FBrickChatMessage();
        SMessageN.TextOption = FmessageN;
        PlayerController->ClientReceiveChatMessage(SMessageN);
    }
}

void modules::interpreter::sendUserSpecificMessageWithContext(PlayerInfo info, std::string message, SDK::EChatContext context, const wchar_t* sender)
{
    if (!global::isMapValid()) return;
    SDK::FText Fmessage = TEXT(global::to_wstring_n(message).c_str());
    SDK::FBrickChatMessage SMessage;
    SDK::ABrickPlayerController* cont = global::GetBrickPlayerControllerFromName(info.name);
    if (cont != nullptr) {
        hooks::constructors::FBrickChatMessageConstructor(&SMessage, SDK::EChatMessageType::Message, cont);
        SMessage.TextOption = Fmessage;
        SMessage.Type = SDK::EChatMessageType::Message;
        SMessage.IntOption = (int)context;
        SMessage.Player.PlayerId = global::GetBrickPlayerController()->GetPlayerId();
        SMessage.Player.PlayerName = STRING(sender);
        cont->ClientReceiveChatMessage(SMessage);
    }
    else {
        auto PlayerController = global::GetBrickPlayerController();
        if (PlayerController == nullptr) return;
        SDK::FText FmessageN = SDK::UKismetTextLibrary::Conv_StringToText(SDK::UKismetStringLibrary::Concat_StrStr(UC::FString(L"Message Failed To Send To: "), UC::FString(global::to_wstring_n(info.name).c_str())));
        auto SMessageN = SDK::FBrickChatMessage();
        SMessageN.TextOption = FmessageN;
        PlayerController->ClientReceiveChatMessage(SMessageN);
    }
}

void modules::interpreter::sendMessageToAdmin(std::string message)
{
    if (!global::isMapValid()) return;
    sendUserSpecificMessage(global::GetPlayerInfoFromController(global::GetBrickPlayerController()), message);
}

void modules::interpreter::Commands::Command(PlayerInfo info)
{
    sendUserSpecificMessage(info, CommandList::message);
}

void modules::interpreter::Commands::Toggle(PlayerInfo info, std::string command, bool toggle)
{
    using namespace global;
    if (!GetIsPlayerAdminFromName(info.name)) return;
    size_t hash_val = hash_string(command);

    std::cout << "We Made It!" << std::endl;

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
        case hs("fly"):
            isFly = toggle;
            break;
        case hs("walk"):
            isWalk = toggle;
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

//Verifies that the playercontroller is ok to have its movement changed, which is only when it is not null.
bool canModifyMovement(SDK::ABrickPlayerController* Controller)
{
    return (Controller->Character != nullptr && Controller->Character->CharacterMovement != nullptr);
}

void modules::interpreter::Commands::Fly(PlayerInfo info)
{
    using namespace global;
    auto BrickPlayerController = GetBrickPlayerControllerFromName(info.name);
    if (BrickPlayerController == nullptr) return;
    if (canModifyMovement(BrickPlayerController)) {
        BrickPlayerController->Character->CharacterMovement->MovementMode = SDK::EMovementMode::MOVE_Flying;
        BrickPlayerController->Character->CharacterMovement->MaxAcceleration = 1000;
        BrickPlayerController->Character->CharacterMovement->MaxFlySpeed = 5000;
    }
    else sendUserSpecificMessageWithContext(info, "Movement commands can only be used when controlling an independent character (walking around).", SDK::EChatContext::Global, L"Command Failed!");
    //Change accel and speed values to appropriate levels
}

void modules::interpreter::Commands::Walk(PlayerInfo info)
{
    using namespace global;
    if (!isWalk) return;
    auto BrickPlayerController = GetBrickPlayerControllerFromName(info.name);
    if (BrickPlayerController == nullptr) return;
    if (canModifyMovement(BrickPlayerController)) {
        BrickPlayerController->Character->CharacterMovement->MaxAcceleration = 750; //This is the default value
        BrickPlayerController->Character->CharacterMovement->MovementMode = SDK::EMovementMode::MOVE_Walking;
    }
    else sendUserSpecificMessageWithContext(info, "Movement commands can only be used when controlling an independent character (walking around).", SDK::EChatContext::Global, L"Command Failed!");
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
    sendMessageToAdmin("This message is really sad!");
}

/*
* FailedToSpawnVehicleFormat
* Failed to spawn your vehicle
* VehicleSpawnFail
* ProjectileCam
* MoneyPlus
* MoneyMinus
* VehicleCam
* FirstPersonCamera
* VehicleCamera
* First Person
* ThirdPersonCamera
* Third Person
* save
* CameraSpeed
* zoom
* slomo
*/
