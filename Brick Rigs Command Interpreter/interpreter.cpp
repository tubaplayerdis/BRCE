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
    if (!isNight) { sendUserSpecificMessageCommandFailed(info, "The /night command is currently disabled!"); return; }
    using namespace global;
    auto cur = GetBrickGameState()->GetMatchSettings();
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.TimeOfDay = 0.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::interpreter::Commands::Day(PlayerInfo info)
{
    if (!isDay) { sendUserSpecificMessageCommandFailed(info, "The /day command is currently disabled!"); return; }
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.TimeOfDay = 12.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::interpreter::Commands::Rain(PlayerInfo info)
{
    if (!isRain) { sendUserSpecificMessageCommandFailed(info, "The /rain command is currently disabled!"); return; }
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
    cur.WorldSetupParams.Weather->Weather.PrecipitationType = SDK::EPrecipitationType::Rain;
    cur.WorldSetupParams.Weather->Weather.PrecipitationIntensity = 100.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::interpreter::Commands::Sun(PlayerInfo info)
{
    if (!isSun) { sendUserSpecificMessageCommandFailed(info, "The /sun command is currently disabled!"); return; }
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
    cur.WorldSetupParams.Weather->Weather.PrecipitationType = SDK::EPrecipitationType::None;
    cur.WorldSetupParams.Weather->Weather.PrecipitationIntensity = 0.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::interpreter::Commands::BombGun(PlayerInfo info)
{
    if (!isBombGun) { sendUserSpecificMessageCommandFailed(info, "The /bombgun command is currently disabled!"); return; }
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

/*
* TODO: For all commands with arguments, if the amount of arguments are too small, send the respective help message back to the player.
*/
void modules::interpreter::interpretCommand(std::string command, std::vector<std::string> args, PlayerInfo info, std::string originalMessage)
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
        case hs("/pm"):
            Commands::PersonalMessage(info, originalMessage);
            break;
        case hs("/mute"):
            if (args.size() < 1) break;
            Commands::Moderation::ToggleMute(info, PlayerInfo(args[0]), true);
            break;
        case hs("/unmute"):
            if (args.size() < 1) break;
            Commands::Moderation::ToggleMute(info, PlayerInfo(args[0]), false);
            break;
        case hs("/silence"):
            Commands::Moderation::ToggleSilence(info, true);
            break;
        case hs("/unsilence"):
            Commands::Moderation::ToggleSilence(info, false);
            break;
        case hs("/block"):
            if (args.size() < 1) break;
            Commands::Moderation::ToggleBlock(info, PlayerInfo(args[0]), true);
            break;
        case hs("/unblock"):
            if (args.size() < 1) break;
            Commands::Moderation::ToggleBlock(info, PlayerInfo(args[0]), true);
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
        SMessage.Player.PlayerId = cont->GetPlayerId();
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
        SMessage.Player.PlayerId = cont->GetPlayerId();
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
    sendUserSpecificMessageWithContext(global::GetPlayerInfoFromController(global::GetBrickPlayerController()), message, SDK::EChatContext::Admin, L"Command Interpreter");
}

void modules::interpreter::Commands::Command(PlayerInfo info)
{
    sendUserSpecificMessage(info, CommandList::message);
}

void modules::interpreter::Commands::Toggle(PlayerInfo info, std::string command, bool toggle)
{
    using namespace global;
    if (!GetIsPlayerAdminFromName(info.name)) {
        sendUserSpecificMessageCommandFailed(info, "Only admins can use this command!");
        return;
    } 
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

/*
* Preconditions:
* The user has managed to correctly input /pm and a space
* originalMessage is the raw original message
*/
void modules::interpreter::Commands::PersonalMessage(PlayerInfo info, std::string originalMessage)
{
    if (!isPM) { sendUserSpecificMessageCommandFailed(info, "The /pm command is currently disabled!"); return; }

    //Send the user back thier original message for context.
    sendUserSpecificMessageWithContext(info, originalMessage, SDK::EChatContext::Global, L"(Only you can see this)");

    size_t firstSpace = originalMessage.find_first_of(' ');
    if (firstSpace == std::string::npos) { sendUserSpecificMessageCommandFailed(info, "There was a formatting error when using /pm! Usage Example: /pm john123 Whats Up!"); return; } //This realisitclly shouldnt happen, but edge cases are edge cases

    std::string sub = originalMessage.substr(firstSpace + 1);
    size_t second = sub.find_first_of(' ');
    if (second == std::string::npos) { sendUserSpecificMessageCommandFailed(info, "There was a formatting error when using /pm! use a space after the intended recipient!"); return; }

    std::string recipient = sub.substr(0, second);

    SDK::ABrickPlayerController* otherCont = global::GetBrickPlayerControllerFromName(recipient);
    if(!otherCont) { sendUserSpecificMessageCommandFailed(info, "The intended recipient was not found! Please try agian."); return; }

    if (global::moderation::isPlayerBlockedBy(info, PlayerInfo(recipient))) { return; }
    if (global::moderation::isPlayerOnSilence(info)) { return; }

    std::string message = sub.substr(second + 1);
    std::wstring contextmessage = global::to_wstring_n(info.name);
    contextmessage += L" (Personal Message)";
    sendUserSpecificMessageWithContext(PlayerInfo(recipient), message, SDK::EChatContext::Global, contextmessage.c_str());
    
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
    if(isFly) { sendUserSpecificMessageCommandFailed(info, "The /fly command is currently disabled!"); return; }
    using namespace global;
    auto BrickPlayerController = GetBrickPlayerControllerFromName(info.name);
    if (BrickPlayerController == nullptr) return;
    if (canModifyMovement(BrickPlayerController)) {
        BrickPlayerController->Character->CharacterMovement->MaxFlySpeed = 3000;
        BrickPlayerController->Character->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_None, 0);
        BrickPlayerController->Character->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Flying, 0);
        BrickPlayerController->Character->CharacterMovement->Velocity = SDK::FVector(0, 0);
    }
    else sendUserSpecificMessageCommandFailed(info, "Movement commands can only be used when controlling an independent character (walking around).");
    //Change accel and speed values to appropriate levels
}

void modules::interpreter::Commands::Walk(PlayerInfo info)
{
    using namespace global;
    if (!isWalk) { sendUserSpecificMessageCommandFailed(info, "The /walk command is currently disabled!"); return; }
    auto BrickPlayerController = GetBrickPlayerControllerFromName(info.name);
    if (BrickPlayerController == nullptr) return;
    if (canModifyMovement(BrickPlayerController)) {
        BrickPlayerController->Character->CharacterMovement->MaxAcceleration = 750; //This is the default value
        BrickPlayerController->Character->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Walking, 0);
    }
    else sendUserSpecificMessageCommandFailed(info, "Movement commands can only be used when controlling an independent character (walking around).");
    //Return speed and accel to regular values
}

void modules::interpreter::Commands::Speed(PlayerInfo info, char level)
{
    if (!isSpeed) { sendUserSpecificMessageCommandFailed(info, "The /speed command is currently disabled!"); return; }
}

void modules::interpreter::Commands::Teleport(PlayerInfo info)
{
    if (!isTeleport) { sendUserSpecificMessageCommandFailed(info, "The /tp command is currently disabled!"); return; }
}

void modules::interpreter::Commands::Ghost(PlayerInfo info)
{
    if (!isGhost) { sendUserSpecificMessageCommandFailed(info, "The /ghost command is currently disabled!"); return; }
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

void modules::interpreter::Commands::Moderation::ToggleMute(PlayerInfo info, PlayerInfo other, bool on_off)
{
    using namespace global;
    using namespace global::moderation;
    using namespace modules::interpreter;
    if (!GetIsPlayerAdminFromName(info.name)) { sendUserSpecificMessageCommandFailed(info, "Only admins can use this command!"); return; }
    if (on_off) {
        if (GetBrickPlayerControllerFromName(info.name)) { AddMutedPlayer(other); }
        else { sendUserSpecificMessageCommandFailed(info, "The user you wanted to mute was not found!"); return; }
        sendUserSpecificMessageWithContext(info, std::string("Successfully Muted: ") + other.name, SDK::EChatContext::Admin, L"Admin");
    }
    else { RemoveMutedPlayer(other); sendUserSpecificMessageWithContext(info, std::string("Successfully Unmuted: ") + other.name, SDK::EChatContext::Admin, L"Admin"); }
}

void modules::interpreter::Commands::Moderation::ToggleBlock(PlayerInfo info, PlayerInfo other, bool on_off)
{
    using namespace global;
    using namespace global::moderation;
    if (on_off) {
        if (GetBrickPlayerControllerFromName(info.name)) { AddBlockedPlayer(BlockedPlayer(info, other)); }
        else { sendUserSpecificMessageCommandFailed(info, "The user you wanted to block was not found!"); return; }
        sendUserSpecificMessageWithContext(info, std::string("Successfully Blocked: ") + other.name, SDK::EChatContext::Admin, L"Admin");
    }
    else { RemoveBlockedPlayer(BlockedPlayer(info, other)); sendUserSpecificMessageWithContext(info, std::string("Successfully Unblocked: ") + other.name, SDK::EChatContext::Admin, L"Admin"); }
}

void modules::interpreter::Commands::Moderation::ToggleSilence(PlayerInfo info, bool on_off)
{
    using namespace global::moderation;
    if (on_off) {
        AddPMSilencePlayer(info);
        sendUserSpecificMessageWithContext(info, std::string("Disallowed incoming personal messages!"), SDK::EChatContext::Global, L"BRCI Moderation");
    }
    else { RemovePMSilencePlayer(info); sendUserSpecificMessageWithContext(info, std::string("Disallowed incoming personal messages!"), SDK::EChatContext::Global, L"BRCI Moderation"); }
}
