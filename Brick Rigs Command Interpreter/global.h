#pragma once

#pragma once
#include <string>
#include "SDK.hpp"

namespace global
{
	extern bool isChangingMapName;
	extern std::string mapLevelName;

	extern SDK::UEngine* Engine;
	extern SDK::UWorld* World;
	extern SDK::ULevel* Level;
	extern SDK::APlayerController* MyController;

	extern float X;
	extern float Y;
	extern float Z;
	extern float H;

	extern bool isWorldHost;

	bool ismapValid();

	void updateLocationVars();

	void initPointers();

	void verifyPointers();

	SDK::ABrickCharacter* GetBrickCharacter();
	SDK::ABrickPlayerController* GetBrickPlayerController();
	SDK::ABrickGameMode* GetBrickGameMode();
	SDK::ABrickGameState* GetBrickGameState();
	SDK::ABrickGameSession* GetBrickGameSession();
	SDK::AWorldSetupActor* GetWorldSetupActor();
	
	std::wstring to_wstring_n(const std::string& str);
	SDK::ABrickPlayerController* GetBrickPlayerControllerFromName(std::string name);

	bool isMapValid();
	bool GetIsWorldHost();
}