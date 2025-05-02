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
	bool GetIsWorldHost();
}