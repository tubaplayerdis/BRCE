#include "global.h"
#include "SDK.hpp"
#include "Windows.h"
#include "modules.h"

SDK::UEngine* global::Engine = SDK::UEngine::GetEngine();
SDK::UWorld* global::World = SDK::UWorld::GetWorld();
SDK::ULevel* global::Level = World->PersistentLevel;
SDK::APlayerController* global::MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
std::string global::mapLevelName = "None So Far";
bool global::isChangingMapName = false;

float global::X = 0;
float global::Y = 0;
float global::Z = 0;
float global::H = 0;

bool global::isWorldHost = false;

bool global::ismapValid()
{
	std::string name = mapLevelName;
	if (name == "City2") return true;
	else if (name == "Canyon") return true;
	else if (name == "City") return true;
	else if (name == "Desert") return true;
	else if (name == "GridMap") return true;
	else if (name == "Raceway") return true;
	else if (name == "Space") return true;
	else return false;
}

void global::updateLocationVars()
{
	if (MyController->Pawn == nullptr || isChangingMapName) {
		X = -1;
		Y = -1;
		Z = -1;
		H = -1;
		return;
	}
	SDK::FVector CurrentLocation = SDK::FVector();
	CurrentLocation = MyController->Pawn->K2_GetActorLocation();
	X = CurrentLocation.X;
	Y = CurrentLocation.Y;
	Z = CurrentLocation.Z;

	if (MyController != nullptr) {
		SDK::FRotator CurrentRotation = MyController->GetControlRotation();
		H = CurrentRotation.Yaw;
	}
}

SDK::ABrickCharacter* global::GetBrickCharacter()
{
	return static_cast<SDK::ABrickCharacter*>(MyController->Character);
}

SDK::ABrickPlayerController* global::GetBrickPlayerController()
{
	return static_cast<SDK::ABrickPlayerController*>(MyController);
}

SDK::ABrickGameMode* global::GetBrickGameMode()
{
	return static_cast<SDK::ABrickGameMode*>(World->AuthorityGameMode);
}

SDK::ABrickGameState* global::GetBrickGameState()
{
	return SDK::ABrickGameState::Get(World);
}

SDK::ABrickGameSession* global::GetBrickGameSession()
{
	return SDK::ABrickGameSession::Get(World);
}

bool global::isMapValid()
{
	std::string name = mapLevelName;
	if (name == "City2") return true;
	else if (name == "Canyon") return true;
	else if (name == "City") return true;
	else if (name == "Desert") return true;
	else if (name == "GridMap") return true;
	else if (name == "Raceway") return true;
	else if (name == "Space") return true;
	else return false;
}

bool global::GetIsWorldHost()
{
	return isWorldHost;
}

void global::initPointers()
{
	Engine = SDK::UEngine::GetEngine();
	World = SDK::UWorld::GetWorld();
	Level = World->PersistentLevel;
	MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
	mapLevelName = "None So Far";
	isChangingMapName = false;
}

void global::verifyPointers()
{
	bool changePointerDueToLevelChange = false;

	if (SDK::UWorld::GetWorld() != World) { //I hate this. Hook UWorld::BeginPlay 
		changePointerDueToLevelChange = true;
		std::cout << "World Change" << std::endl;
	}

	if (changePointerDueToLevelChange) {
		isChangingMapName = true;
		mapLevelName = "Changing";
		isChangingMapName = false;
		Sleep(100);//Wait for new UWorld Load.
		World = SDK::UWorld::GetWorld();
		while (true)
		{
			if (World == nullptr) {
				Sleep(100);
				World = SDK::UWorld::GetWorld();
			}
			else break;
		}

		Level = World->PersistentLevel;
		isChangingMapName = true;
		mapLevelName = Level->Outer->GetName();
		std::cout << mapLevelName << std::endl;
		isChangingMapName = false;
		changePointerDueToLevelChange = false;
		MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;

		SDK::ABrickGameMode* GameMode = static_cast<SDK::ABrickGameMode*>(World->AuthorityGameMode);
		if (GameMode->GetName() == "None") isWorldHost = false;
		else isWorldHost = true;

	}

	//CHECK FOR CHANGED POINTERS
	if (MyController == nullptr || MyController != World->OwningGameInstance->LocalPlayers[0]->PlayerController) {
		MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
		std::cout << "Detected Change in PlayController! Switching." << std::endl;
	}
}