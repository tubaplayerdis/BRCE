#include "global.h"
#include "SDK.hpp"
#include "Windows.h"
#include "modules.h"
#include "interpreter.h"
#include <codecvt>
#include <locale>

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
	if (isChangingMapName || updatingPointers || World == nullptr || SDK::UWorld::GetWorld() != World || MyController == nullptr || MyController->Pawn == nullptr) {
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

SDK::ABrickPlayerState* global::GetBrickPlayerState()
{
	return static_cast<SDK::ABrickPlayerState*>(MyController->PlayerState);
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

SDK::AWorldSetupActor* global::GetWorldSetupActor()
{
	return SDK::AWorldSetupActor::Get(World);
}

//Manually written helper functions in the big 25? are we serious.
std::wstring global::to_wstring_n(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
	wstr.pop_back(); // remove null terminator
	return wstr;
}

SDK::ABrickPlayerController* global::GetBrickPlayerControllerFromName(std::string name)
{
	UC::TArray<SDK::AActor*> raw = UC::TArray<SDK::AActor*>();
	UC::TArray<SDK::AActor*>* what = &raw;
	SDK::UGameplayStatics::GetAllActorsOfClass(World, SDK::ABrickPlayerController::StaticClass(), what);
	for (int i = 0; i < raw.Num(); i++)
	{
		SDK::ABrickPlayerController* cast = static_cast<SDK::ABrickPlayerController*>(raw[i]);
		SDK::ABrickPlayerState* state = static_cast<SDK::ABrickPlayerState*>(cast->PlayerState);
		if (state->GetPlayerNameText().ToString() == name) return cast;
	}
	return nullptr;
}

bool global::GetIsPlayerAdminFromName(std::string name)
{
	if (GetBrickPlayerControllerFromName(name) == nullptr) return false;
	return static_cast<SDK::ABrickPlayerState*>(GetBrickPlayerControllerFromName(name)->PlayerState)->IsAdmin();
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
	updatingPointers = true;
	isChangingMapName = true;
	mapLevelName = "Changing";
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
	std::cout << "New Map Name: " << mapLevelName << std::endl;
	MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;

	SDK::ABrickGameMode* GameMode = static_cast<SDK::ABrickGameMode*>(World->AuthorityGameMode);
	if (GameMode->GetName() == "None") isWorldHost = false;
	else isWorldHost = true;

	if (MyController == nullptr || MyController != World->OwningGameInstance->LocalPlayers[0]->PlayerController) {
		MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
		std::cout << "Detected Change in PlayController! Switching." << std::endl;
	}

	updatingPointers = false;
	isChangingMapName = false;
	doVerifyPointers = false;
}