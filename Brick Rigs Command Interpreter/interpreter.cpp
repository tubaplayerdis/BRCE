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

#define Message(info, message) modules::interpreter::sendUserSpecificMessage(info, message)
#define MIF(cond, info, message) (cond ? Message(info, message) : (void)0)

bool modules::interpreter::Commands::Night(PlayerInfo info)
{
    if (!isNight) { sendUserSpecificMessageCommandFailed(info, "The /night command is currently disabled!"); RETF; }
    using namespace global;
    auto cur = GetBrickGameState()->GetMatchSettings();
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.TimeOfDay = 0.00f;
    GetBrickGameState()->SetMatchSettings(cur);
    RETT;
}

bool modules::interpreter::Commands::Day(PlayerInfo info)
{
    if (!isDay) { sendUserSpecificMessageCommandFailed(info, "The /day command is currently disabled!"); RETF; }
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.TimeOfDay = 12.00f;
    GetBrickGameState()->SetMatchSettings(cur);
    RETT;
}

bool modules::interpreter::Commands::Rain(PlayerInfo info)
{
    if (!isRain) { sendUserSpecificMessageCommandFailed(info, "The /rain command is currently disabled!"); RETF; }
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
    cur.WorldSetupParams.Weather->Weather.PrecipitationType = SDK::EPrecipitationType::Rain;
    cur.WorldSetupParams.Weather->Weather.PrecipitationIntensity = 100.00f;
    GetBrickGameState()->SetMatchSettings(cur);
    RETT;
}

bool modules::interpreter::Commands::Sun(PlayerInfo info)
{
    if (!isSun) { sendUserSpecificMessageCommandFailed(info, "The /sun command is currently disabled!"); RETF; }
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
    cur.WorldSetupParams.Weather->Weather.PrecipitationType = SDK::EPrecipitationType::None;
    cur.WorldSetupParams.Weather->Weather.PrecipitationIntensity = 0.00f;
    GetBrickGameState()->SetMatchSettings(cur);
    RETT;
}

bool modules::interpreter::Commands::AmmoType(PlayerInfo info, std::string ammotype)
{
    //todo implement ammo types change
    if (!isBombGun) { sendUserSpecificMessageCommandFailed(info, "The /bombgun command is currently disabled!"); RETF; }
    UC::TArray<SDK::AActor*> raw = UC::TArray<SDK::AActor*>();
    UC::TArray<SDK::AActor*>* what = &raw;
    SDK::UGameplayStatics::GetAllActorsOfClass(global::World, SDK::AFirearm::StaticClass(), what);
    for (int i = 0; i < raw.Num(); i++)
    {
        SDK::AFirearm* cast = static_cast<SDK::AFirearm*>(raw[i]);
        if (cast->FirearmComponent->ControllingCharacter.Get() != global::GetBrickPlayerControllerFromName(info.name)->Character) continue;
        cast->FirearmComponent->FirearmState.AmmoType = SDK::EAmmoType::HighExplosive;
    }
    RETT;
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

void modules::interpreter::interpretCommand(std::string command, std::vector<std::string> args, PlayerInfo info, std::string originalMessage)
{
	size_t hash_val = hash_string(command);

    for (std::string i : args) {
        std::cout << i << std::endl;
    }

	switch (hash_val) {
        case hs("/help"):
            if (args.size() < 1) {
                Commands::Help(info, "master");
                break;
            }
            Commands::Help(info, args[0]);
            break;
        case hs("/info"):
            sendUserSpecificMessageWithContext(info, InfoMessage, SDK::EChatContext::Global, L"Info ABout BRCI:");
            break;
        case hs("/on"):
            if (args.size() < 1) { ToFewArgs(info, "/on", "moderation"); break; }
            Commands::Toggle(info, args[0], true);
            break;
        case hs("/off"):
            if (args.size() < 1) { ToFewArgs(info, "/off", "moderation"); break; }
            Commands::Toggle(info, args[0], false);
            break;
		case hs("/night"):
            MIF(Commands::Night(info), info, "Set the time to night!");
            break;
        case hs("/day"):
            MIF(Commands::Day(info), info, "Set the time to day!");
            break;
        case hs("/rain"):
            MIF(Commands::Rain(info), info, "Set the weather to rain!");
            break;
        case hs("/sun"):
            MIF(Commands::Sun(info), info, "Set the weather to sunny!");
            break;
        case hs("/fly"):
            MIF(Commands::Fly(info), info, "You feel lighter...");
            break;
        case hs("/walk"):
            MIF(Commands::Walk(info), info, "Your feet are heavy...");
            break;
        case hs("/pm"):
            Commands::PersonalMessage(info, originalMessage);
            break;
        case hs("/mute"):
            if (args.size() < 1) { ToFewArgs(info, "/mute", "moderation"); break; }
            Commands::Moderation::ToggleMute(info, originalMessage, true);
            break;
        case hs("/unmute"):
            if (args.size() < 1) { ToFewArgs(info, "/unmute", "moderation"); break; }
            Commands::Moderation::ToggleMute(info, originalMessage, false);
            break;
        case hs("/silence"):
            Commands::Moderation::ToggleSilence(info, true);
            break;
        case hs("/unsilence"):
            Commands::Moderation::ToggleSilence(info, false);
            break;
        case hs("/block"):
            if (args.size() < 1) { ToFewArgs(info, "/block", "main"); break; }
            Commands::Moderation::ToggleBlock(info, originalMessage, true);
            break;
        case hs("/unblock"):
            if (args.size() < 1) { ToFewArgs(info, "/unblock", "main"); break; }
            Commands::Moderation::ToggleBlock(info, originalMessage, false);
            break;
        case hs("/ghost"):
            MIF(Commands::Ghost(info), info, "Set the movement mode to ghost!");
            break;
        case hs("/save"):
            Commands::Moderation::Save(info);
            break;
        case hs("/load"):
            Commands::Moderation::Load(info);
            break;
        case hs("/blocked"):
            Commands::Moderation::ListBlocked(info);
            break;
        case hs("/muted"):
            Commands::Moderation::ListMuted(info);
            break;
        case hs("/silenced"):
            Commands::Moderation::IsOnSilence(info);
            break;
        case hs("/pid"):
            Commands::Moderation::ListPlayerIDS(info);
            break;
        case hs("/ammotype"):
            if (args.size() < 1) { ToFewArgs(info, "/ammotype", "weapons"); break; }
            MIF(Commands::AmmoType(info, args[0]), info, "Changed ammo type to: " + args[0]);
            break;
        default:
            sendUserSpecificMessageCommandFailed(info, "The command: " + command + " was not found! Use /help to view all commands!");
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
        SMessage.Player.PlayerName = STRING(L"BRCI");
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

void modules::interpreter::Commands::Toggle(PlayerInfo info, std::string command, bool toggle)
{
    using namespace global;
    if (!GetIsPlayerAdminFromName(info.name)) {
        sendUserSpecificMessageCommandFailed(info, "Only admins can use this command!");
        return;
    } 
    size_t hash_val = hash_string(command);
    bool defa = false;

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
        case hs("ghost"):
            isGhost = toggle;
            break;
        default:
            defa = true;
            break;
    }
    if(!defa) sendUserSpecificMessage(info, "Toggled: " + command + " to" + GetBoolString(toggle));
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
    if (!otherCont) otherCont = global::GetBrickPlayerControllerFromID(recipient);
    if(!otherCont) { sendUserSpecificMessageCommandFailed(info, "The intended recipient was not found! Please try agian."); return; }

    if (global::moderation::isPlayerBlockedBy(info, PlayerInfo(recipient))) { return; }
    if (global::moderation::isPlayerOnSilence(info)) { return; }

    std::string message = sub.substr(second + 1);
    std::wstring contextmessage = global::to_wstring_n(info.name);
    contextmessage += L" (Personal Message)";
    sendUserSpecificMessageWithContext(PlayerInfo(recipient), message, SDK::EChatContext::Global, contextmessage.c_str());
    
}

void modules::interpreter::Commands::Help(PlayerInfo info, std::string arg)
{
    size_t hash_val = hash_string(arg);
    switch (hash_val) {
        case hs("master"):
            sendUserSpecificMessageWithContext(info, MasterHelpMessage, SDK::EChatContext::Global, L"Help Command List:");
            break;
        case hs("main"):
            sendUserSpecificMessageWithContext(info, MainHelpMessage, SDK::EChatContext::Global, L"Main Command List:");
            break;
        case hs("moderation"):
            sendUserSpecificMessageWithContext(info, ModerationHelpMessage, SDK::EChatContext::Global, L"Moderation Command List:");
            break;
        case hs("movement"):
            sendUserSpecificMessageWithContext(info, MovementHelpMessage, SDK::EChatContext::Global, L"Movement Command List:");
            break;
        case hs("enviroment"):
            sendUserSpecificMessageWithContext(info, EnviromentHelpMessage, SDK::EChatContext::Global, L"Enviroment Command List:");
            break;
        case hs("weapons"):
            sendUserSpecificMessageWithContext(info, WeaponsHelpMessage, SDK::EChatContext::Global, L"Weapons Command List:");
            break;
        default:
            sendUserSpecificMessageWithContext(info, MasterHelpMessage, SDK::EChatContext::Global, L"Help Command List:");
            break;
    }
}

//Verifies that the playercontroller is ok to have its movement changed, which is only when it is not null.
bool canModifyMovement(SDK::ABrickPlayerController* Controller)
{
    return (Controller->Character != nullptr && Controller->Character->CharacterMovement != nullptr);
}

bool modules::interpreter::Commands::Fly(PlayerInfo info)
{
    if (!isFly) { sendUserSpecificMessageCommandFailed(info, "The /fly command is currently disabled!"); RETF; }
    using namespace global;
    auto BrickPlayerController = GetBrickPlayerControllerFromName(info.name);
    if (global::GetBrickPlayerControllerFromName(info.name)) global::GetBrickPlayerControllerFromName(info.name)->Character->SetActorEnableCollision(true);
    if (BrickPlayerController == nullptr) RETF;
    if (canModifyMovement(BrickPlayerController)) { BrickPlayerController->Character->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Flying, 0); RETT; }
    else sendUserSpecificMessageCommandFailed(info, "Movement commands can only be used when controlling an independent character (not in a vehicle).");
    RETF;
    //Change accel and speed values to appropriate levels
}

bool modules::interpreter::Commands::Walk(PlayerInfo info)
{
    using namespace global;
    if (!isWalk) { sendUserSpecificMessageCommandFailed(info, "The /walk command is currently disabled!"); RETF; }
    auto BrickPlayerController = GetBrickPlayerControllerFromName(info.name);
    if (global::GetBrickPlayerControllerFromName(info.name)) global::GetBrickPlayerControllerFromName(info.name)->Character->SetActorEnableCollision(true);
    if (BrickPlayerController == nullptr) RETF;
    if (canModifyMovement(BrickPlayerController)) {
        BrickPlayerController->Character->CharacterMovement->MaxAcceleration = 750; //This is the default value
        BrickPlayerController->Character->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Walking, 0);
        RETT;
    }
    else sendUserSpecificMessageCommandFailed(info, "Movement commands can only be used when controlling an independent character (not in a vehicle).");
    RETF;
    //Return speed and accel to regular values
}

bool modules::interpreter::Commands::Speed(PlayerInfo info, char level)
{
    if (!isSpeed) { sendUserSpecificMessageCommandFailed(info, "The /speed command is currently disabled!"); RETF; }
    if (global::GetBrickPlayerControllerFromName(info.name)) global::GetBrickPlayerControllerFromName(info.name)->Character->SetActorEnableCollision(true);
    RETT;
}

bool modules::interpreter::Commands::Teleport(PlayerInfo info)
{
    if (!isTeleport) { sendUserSpecificMessageCommandFailed(info, "The /tp command is currently disabled!"); RETF; }
    if(global::GetBrickPlayerControllerFromName(info.name)) global::GetBrickPlayerControllerFromName(info.name)->Character->SetActorEnableCollision(true);
    RETT;
}

bool modules::interpreter::Commands::Ghost(PlayerInfo info)
{
    if (!isGhost) { sendUserSpecificMessageCommandFailed(info, "The /ghost command is currently disabled!"); RETF; }
    using namespace global;
    auto BrickPlayerController = GetBrickPlayerControllerFromName(info.name);
    if (BrickPlayerController == nullptr) RETF;
    if (canModifyMovement(BrickPlayerController)) {
        BrickPlayerController->Character->SetActorEnableCollision(false);
        BrickPlayerController->Character->CharacterMovement->SetMovementMode(SDK::EMovementMode::MOVE_Flying, 0);
        RETT;
    }
    else sendUserSpecificMessageCommandFailed(info, "Movement commands can only be used when controlling an independent character (not in a vehicle).");
    RETF;
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

void modules::interpreter::Commands::Moderation::ToggleMute(PlayerInfo info, std::string originalMessage, bool on_off)
{
    using namespace global;
    using namespace global::moderation;
    using namespace modules::interpreter;
    if (!GetIsPlayerAdminFromName(info.name)) { sendUserSpecificMessageCommandFailed(info, "Only admins can use this command!"); return; }
    std::string input = originalMessage.substr(originalMessage.find_first_of(' ') + 1);
    SDK::ABrickPlayerController* controller = nullptr;
    controller = GetBrickPlayerControllerFromName(input);
    if (!controller) controller = GetBrickPlayerControllerFromID(input);
    if (!controller) { sendUserSpecificMessageCommandFailed(info, "The user you wanted to block was not found!"); return; }
    PlayerInfo other = GetPlayerInfoFromController(controller);
    if (on_off) {
        if (!AddMutedPlayer(other)) sendUserSpecificMessageWithContext(info, other.name + " is already muted!", SDK::EChatContext::Admin, L"Admin");
        else sendUserSpecificMessageWithContext(info, std::string("Successfully Muted: ") + other.name, SDK::EChatContext::Admin, L"Admin");
    }
    else {
        if (!RemoveMutedPlayer(other)) sendUserSpecificMessageWithContext(info, other.name + "is already unmuted", SDK::EChatContext::Admin, L"Admin");
        else sendUserSpecificMessageWithContext(info, std::string("Successfully Unmuted: ") + other.name, SDK::EChatContext::Admin, L"Admin");
    }
}

void modules::interpreter::Commands::Moderation::ToggleBlock(PlayerInfo info, std::string originalMessage, bool on_off)
{
    using namespace global;
    using namespace global::moderation;
    std::string input = originalMessage.substr(originalMessage.find_first_of(' ') + 1);
    SDK::ABrickPlayerController* controller = nullptr;
    controller = GetBrickPlayerControllerFromName(input);
    if (!controller) controller = GetBrickPlayerControllerFromID(input);
    if(!controller) { sendUserSpecificMessageCommandFailed(info, "The user you wanted to block was not found!"); return; }
    PlayerInfo other = GetPlayerInfoFromController(controller);
    if (on_off) {
        if (!AddBlockedPlayer(BlockedPlayer(info, other))) sendUserSpecificMessageWithContext(info, std::string("You have already blocked: ") + other.name, SDK::EChatContext::Admin, L"Admin");
        else sendUserSpecificMessageWithContext(info, std::string("Successfully Blocked: ") + other.name, SDK::EChatContext::Admin, L"Admin");
    }
    else { 
        if(!RemoveBlockedPlayer(BlockedPlayer(info, other)))  sendUserSpecificMessageWithContext(info, std::string("You have already unblocked: ") + other.name, SDK::EChatContext::Admin, L"Admin");
        else sendUserSpecificMessageWithContext(info, std::string("Successfully Unblocked: ") + other.name, SDK::EChatContext::Admin, L"Admin");
    }
}

void modules::interpreter::Commands::Moderation::ToggleSilence(PlayerInfo info, bool on_off)
{
    using namespace global::moderation;
    if (on_off) {
        if(!AddPMSilencePlayer(info)) sendUserSpecificMessageWithContext(info, std::string("You are already on silence!"), SDK::EChatContext::Global, L"BRCI Moderation");
        else sendUserSpecificMessageWithContext(info, std::string("Disallowed incoming personal messages!"), SDK::EChatContext::Global, L"BRCI Moderation");
    }
    else {
        if(!RemovePMSilencePlayer(info)) sendUserSpecificMessageWithContext(info, std::string("You are already not on silence!"), SDK::EChatContext::Global, L"BRCI Moderation");
        else sendUserSpecificMessageWithContext(info, std::string("Allowed incoming personal messages!"), SDK::EChatContext::Global, L"BRCI Moderation");
    }
}

void modules::interpreter::Commands::Moderation::Save(PlayerInfo info)
{
    using namespace global;
    using namespace global::moderation;
    if (!GetIsPlayerAdminFromName(info.name)) { sendUserSpecificMessageCommandFailed(info, "Only admins can use this command!"); return; }
    if (saveModerationValues()) sendUserSpecificMessage(info, "Successfully saved the current moderation values to the disk!");
    else sendUserSpecificMessageCommandFailed(info, "Failed to save the current moderation values to the disk!");
}

void modules::interpreter::Commands::Moderation::Load(PlayerInfo info)
{
    using namespace global;
    using namespace global::moderation;
    if (!GetIsPlayerAdminFromName(info.name)) { sendUserSpecificMessageCommandFailed(info, "Only admins can use this command!"); return; }
    if(loadModerationValues()) sendUserSpecificMessage(info, "Successfully loaded the current moderation values from the disk!");
    else sendUserSpecificMessageCommandFailed(info, "Failed to load the current moderation values from the disk!");
}

void modules::interpreter::Commands::Moderation::ListMuted(PlayerInfo info)
{
    using namespace global;
    using namespace global::moderation;
    if (!GetIsPlayerAdminFromName(info.name)) { sendUserSpecificMessageCommandFailed(info, "Only admins can use this command!"); return; }
    std::string message = "Currently Muted Players:";
    for (PlayerInfo infou : MutedPlayers) {
        message += "\n" + infou.name;
    }
    sendUserSpecificMessage(info, message);
}

void modules::interpreter::Commands::Moderation::ListBlocked(PlayerInfo info)
{
    using namespace global;
    using namespace global::moderation;
    std::string message = "Currently Blocked Players:";
    for (BlockedPlayer player : BlockedPlayers) {
        if (player.Blocker == info) {
            message += "\n" + info.name;
        }
    }
    sendUserSpecificMessage(info, message);
}

void modules::interpreter::Commands::Moderation::IsOnSilence(PlayerInfo info)
{
    using namespace global;
    using namespace global::moderation;
    for (PlayerInfo player : PlayersOnPMSilence) {
        if (player.name == info) {
            sendUserSpecificMessage(info, "You are on silence. You will not recieve Personal Messages(PM)");
            return;
        }
    }
    sendUserSpecificMessage(info, "You are not on silence. You will recieve Personal Messages(PM)");
}

void modules::interpreter::Commands::Moderation::ListPlayerIDS(PlayerInfo info)
{
    std::string message = "Player IDS:";
    UC::TArray<SDK::AActor*> raw = UC::TArray<SDK::AActor*>();
    UC::TArray<SDK::AActor*>* what = &raw;
    SDK::UGameplayStatics::GetAllActorsOfClass(global::World, SDK::ABrickPlayerController::StaticClass(), what);
    for (int i = 0; i < raw.Num(); i++)
    {
        SDK::ABrickPlayerController* cast = static_cast<SDK::ABrickPlayerController*>(raw[i]);
        SDK::ABrickPlayerState* state = static_cast<SDK::ABrickPlayerState*>(cast->PlayerState);
        message += "\n" + state->GetPlayerNameText().ToString() + ": " + std::to_string(state->PlayerId);
    }
    sendUserSpecificMessage(info, message);
}
