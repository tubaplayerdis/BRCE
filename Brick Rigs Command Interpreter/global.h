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
	bool IsHost();
	inline bool NotHost() { return !IsHost(); };
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
		void clearModerationValues(); //Does it on the file and local instances.
	}
}