/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Aaron Wilk 2025, All rights reserved.                     */
/*                                                                            */
/*    Module:     global.h                                                    */
/*    Author:     Aaron Wilk                                                  */
/*    Created:    2 May 2025                                                  */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma once
#undef TEXT
#define TEXT(text) SDK::UKismetTextLibrary::Conv_StringToText(SDK::FString(text))
#define STRING(string) UC::FString(string)
#define NAME(text) SDK::UKistmetStringLibrary::Conv_StringToName(SDK::FString(text));
#define GetBoolString(text) (text ? "true" : "false")
#define RETF return false
#define RETT return true
#define RET0 return 0
#define RET1 return 1
#include <string>
#include "SDK.hpp"
#include "interpreter.h"

namespace global
{
	//Useful "Global" Variables
	extern std::string mapLevelName;
	extern SDK::UEngine* Engine;
	extern SDK::UWorld* World;
	extern SDK::ULevel* Level;
	extern SDK::APlayerController* MyController;

	//Pointer Stuff
	inline bool updatingPointers = false;
	void InitPointers();
	void UpdatePointers(SDK::UWorld* NewWorld);

	//SDK Helpers
	SDK::ABrickCharacter* GetBrickCharacter();
	SDK::ABrickPlayerController* GetBrickPlayerController();
	SDK::ABrickPlayerState* GetBrickPlayerState();
	SDK::ABrickGameMode* GetBrickGameMode();
	SDK::ABrickGameState* GetBrickGameState();
	SDK::ABrickGameSession* GetBrickGameSession();
	SDK::AWorldSetupActor* GetWorldSetupActor();
	SDK::ABrickPlayerController* GetBrickPlayerControllerFromName(std::string name);

	//General Helpers
	std::wstring to_wstring_n(const std::string& str);
	bool GetIsPlayerAdminFromName(std::string name);

	/*
	* Returns true if a map that is loaded is playable, false if otherwise.
	*/
	bool isMapValid();
	bool IsHost(SDK::UNetDriver* driver);
	inline bool IsHost() { return IsHost(World->NetDriver); }
	inline bool NotHost() { return !IsHost(World->NetDriver); }
	void SendNotificationLocal(std::wstring notif, int slot);
	PlayerInfo GetPlayerInfoFromController(SDK::ABrickPlayerController* controller);

	//Watermark
	namespace watermark
	{
		inline SDK::UCanvasPanel* panel = nullptr;
		inline SDK::UPanelWidget* RootPanel = nullptr;
		inline SDK::UBrickBorder* TextBorder = nullptr;
		bool InitalizeWaterMark();
		void ShowWaterMark();
		void HideWaterWark();
		void UnInitalizeWaterMark();
	}

	namespace welcome
	{
		void SendWelcomeMessage();
		void SendWelcomeMessageA(); 
	}

	namespace moderation
	{
		inline std::vector<PlayerInfo> MutedPlayers = std::vector<PlayerInfo>();
		inline std::vector<PlayerInfo> PlayersOnPMSilence = std::vector<PlayerInfo>();
		inline std::vector<BlockedPlayer> BlockedPlayers = std::vector<BlockedPlayer>();

		//basic set and getters
		inline void AddMutedPlayer(PlayerInfo info) { MutedPlayers.push_back(info); }
		inline void RemoveMutedPlayer(PlayerInfo info) { MutedPlayers.erase(std::remove(MutedPlayers.begin(), MutedPlayers.end(), info), MutedPlayers.end()); }
		inline void AddPMSilencePlayer(PlayerInfo info) { PlayersOnPMSilence.push_back(info); }
		inline void RemovePMSilencePlayer(PlayerInfo info) { PlayersOnPMSilence.erase(std::remove(PlayersOnPMSilence.begin(), PlayersOnPMSilence.end(), info), PlayersOnPMSilence.end()); }
		inline void AddBlockedPlayer(BlockedPlayer info) { BlockedPlayers.push_back(info); }
		inline void RemoveBlockedPlayer(BlockedPlayer info) { BlockedPlayers.erase(std::remove(BlockedPlayers.begin(), BlockedPlayers.end(), info), BlockedPlayers.end()); }

		bool isPlayerBlockedBy(PlayerInfo blocker, PlayerInfo blocked);
		bool isPlayerMuted(PlayerInfo player);
		bool isPlayerOnSilence(PlayerInfo player);

		bool saveModerationValues();
		bool loadModerationValues();
	}
}