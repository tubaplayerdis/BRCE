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

bool global::IsHost()
{
	if(updatingPointers || World->NetDriver == nullptr && World->NetDriver->ServerConnection != nullptr) return false;
	return true;
}

void global::SendNotificationLocal(std::wstring notif, int slot)
{
	//WidgetSkib->SetColorAndOpacity(hooks::constructors::CreateLinearColor(0, 135, 255, 1)); //Change Color
	SDK::FName nameS = SDK::UKismetStringLibrary::Conv_StringToName(L"None");
	if (SDK::UGameOverlayWidget::Get(World) == nullptr) return;
	SDK::UHUDNotificationWidget* WidgetSkib = SDK::UGameOverlayWidget::Get(World)->CreateHUDNotification(nameS, true);
	WidgetSkib->TextBlock->SetText(SDK::UKismetTextLibrary::Conv_StringToText(notif.c_str()));
	WidgetSkib->TextBlock->SetTextStyle(SDK::EBrickUITextStyle::Bold);
	WidgetSkib->TextBlock->SetStyleState(SDK::EBrickUIStyleState::Foreground);
	SDK::FBrickUIIconSlot slots = WidgetSkib->IconImage->IconSlot;
	slots.Index = slot;
	WidgetSkib->IconImage->SetIconSlot(slots);
	SDK::UGameOverlayWidget::Get(global::World)->AddHUDNotification(WidgetSkib, 0);
}

PlayerInfo global::GetPlayerInfoFromController(SDK::ABrickPlayerController* controller)
{
	if (controller == nullptr) return PlayerInfo();
	PlayerInfo ret = PlayerInfo();
	SDK::ABrickPlayerState* state = static_cast<SDK::ABrickPlayerState*>(controller->PlayerState);
	ret.name = state->GetPlayerNameText().ToString();
	return ret;
}

void global::InitPointers()
{
	Engine = SDK::UEngine::GetEngine();
	World = SDK::UWorld::GetWorld();
	Level = World->PersistentLevel;
	MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
	mapLevelName = Level->Outer->GetName();
}

void global::UpdatePointers(SDK::UWorld* NewWorld)
{
	std::cout << "Updating Pointers!" << std::endl;
	updatingPointers = true;
	mapLevelName = "Changing";
	World = NewWorld;
	
	Level = World->PersistentLevel;
	mapLevelName = Level->Outer->GetName();
	std::cout << "New Map Name: " << mapLevelName << std::endl;
	MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;

	if (MyController == nullptr || MyController != World->OwningGameInstance->LocalPlayers[0]->PlayerController) {
		MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
		std::cout << "Detected Change in PlayController! Switching." << std::endl;
	}

	updatingPointers = false;
}