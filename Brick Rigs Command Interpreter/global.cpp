/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Aaron Wilk 2025, All rights reserved.                     */
/*                                                                            */
/*    Module:     global.cp                                                   */
/*    Author:     Aaron Wilk                                                  */
/*    Created:    2 May 2025                                                  */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "global.h"
#include "SDK.hpp"
#include "Windows.h"
#include "modules.h"
#include "interpreter.h"
#include <codecvt>
#include <locale>
#include "GlobalHooks.h"
#include <iostream>
#include <fstream>

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

SDK::UBrickAssetManager* global::GetBrickAssetManager()
{
	return SDK::UBrickAssetManager::Get();
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

SDK::ABrickPlayerController* global::GetBrickPlayerControllerFromID(std::string ID)
{
	int playerID = -1;
	try {
		playerID = std::stoi(ID);
	}
	catch (...) {
		return nullptr;
	}
	UC::TArray<SDK::AActor*> raw = UC::TArray<SDK::AActor*>();
	UC::TArray<SDK::AActor*>* what = &raw;
	SDK::UGameplayStatics::GetAllActorsOfClass(World, SDK::ABrickPlayerController::StaticClass(), what);
	for (int i = 0; i < raw.Num(); i++)
	{
		SDK::ABrickPlayerController* cast = static_cast<SDK::ABrickPlayerController*>(raw[i]);
		SDK::ABrickPlayerState* state = static_cast<SDK::ABrickPlayerState*>(cast->PlayerState);
		if (state->PlayerId == playerID) return cast;
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

bool global::IsHost(SDK::UNetDriver* driver)
{
	if(updatingPointers || !hooks::Functions::isServer::isServer(driver)) return false;
	return true;
}

void global::SendNotificationLocal(std::wstring notif, int slot)
{
	//WidgetSkib->SetColorAndOpacity(hooks::constructors::CreateLinearColor(0, 135, 255, 1)); //Change Color
	SDK::FName nameS = SDK::UKismetStringLibrary::Conv_StringToName(L"None");
	if (SDK::UGameOverlayWidget::Get(World) == nullptr) return;
	SDK::UHUDNotificationWidget* WidgetSkib = SDK::UGameOverlayWidget::Get(World)->CreateHUDNotification(nameS, true);
	WidgetSkib->TextBlock->SetText(SDK::UKismetTextLibrary::Conv_StringToText(notif.c_str()));
	WidgetSkib->TextBlock->SetTextStyle(SDK::EBrickUITextStyle::Default);
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

std::string global::GetPlayerNameFromID(std::string ID)
{
	return GetPlayerInfoFromController(GetBrickPlayerControllerFromID(ID)).name;
}

std::string global::GetPlayerNameFromIDORName(std::string input)
{
	SDK::ABrickPlayerController* controller = nullptr;
	controller = GetBrickPlayerControllerFromName(input);
	if (!controller) controller = GetBrickPlayerControllerFromID(input);
	if (!controller) { return std::string("None"); }
	return GetPlayerInfoFromController(controller).name;
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

bool global::watermark::InitalizeWaterMark()
{
	//Basic Init
	if (!World) return false;
	RootPanel = static_cast<SDK::UPanelWidget*>(SDK::UWindowManagerWidget::Get(World)->WidgetTree->RootWidget);
	if (!RootPanel) return false;
	for (int i = 0; i < RootPanel->GetChildrenCount(); ++i) {
		SDK::UWidget* child = RootPanel->GetChildAt(i);
		if (child->IsA(SDK::UCanvasPanel::StaticClass())) {
			panel = static_cast<SDK::UCanvasPanel*>(child);
			break;
		}
	}
	if (!panel) return false;

	//Text Block/Border Init
	SDK::UBrickTextBlock* TextBlock = static_cast<SDK::UBrickTextBlock*>(SDK::UGameplayStatics::SpawnObject(SDK::UBrickTextBlock::StaticClass(), panel));
	if (!TextBlock) return false;
	#undef TEXT
	#define TEXT(text) SDK::UKismetTextLibrary::Conv_StringToText(SDK::FString(text))

	#ifdef _DEBUG
	TextBlock->SetText(TEXT(L"(DEV)Brick Rigs Command Interpreter V1.0 (BRCI)"));
	#else
	TextBlock->SetText(TEXT(L"Brick Rigs Command Interpreter V1.0 (BRCI)"));
	#endif // _DEBUG

	TextBlock->SetColorStyle(SDK::EBrickUIColorStyle::Default);
	TextBlock->SetTextStyle(SDK::EBrickUITextStyle::Bold);
	TextBlock->SetStyleState(SDK::EBrickUIStyleState::Foreground);


	TextBorder = static_cast<SDK::UBrickBorder*>(SDK::UGameplayStatics::SpawnObject(SDK::UBrickBorder::StaticClass(), panel));
	if (!TextBorder) return false;
	TextBorder->SetContent(TextBlock);
	SDK::UCanvasPanelSlot* slot2 = panel->AddChildToCanvas(TextBorder);
	slot2->SetAutoSize(true);
	SDK::FAnchors anchor = SDK::FAnchors();
	anchor.Maximum = SDK::FVector2D(1.0f, 0.0f);
	anchor.Minimum = SDK::FVector2D(1.0f, 0.0f);
	slot2->SetAnchors(anchor);  // Top-Right Align
	// 2. Align to the top-right of the widget
	slot2->SetAlignment(SDK::FVector2D(1.f, 0.f));

	// 3. Offset inward from top-right screen corner
	slot2->SetPosition(SDK::FVector2D(-20.f, 20.f));  // x: 20px left, y: 20px down
	hooks::Functions::SynchronizeProperties::SynchronizeProperties(TextBorder);

	return true;
}

void global::watermark::ShowWaterMark()
{
	TextBorder->SetVisibility(SDK::ESlateVisibility::Visible);
}

void global::watermark::HideWaterWark()
{
	TextBorder->SetVisibility(SDK::ESlateVisibility::Hidden);
}

void global::watermark::UnInitalizeWaterMark()
{
	if (TextBorder) TextBorder->RemoveFromParent();
	TextBorder = nullptr;
	RootPanel = nullptr;
	panel = nullptr;
}

bool global::moderation::isPlayerBlockedBy(PlayerInfo blocker, PlayerInfo blocked)
{
	std::cout << "Searching in blocked users!" << std::endl;
	BlockedPlayer player = BlockedPlayer(blocked, blocker); //This is reversed for some reason. This should work.
	for (BlockedPlayer blocked : BlockedPlayers) {
		if (player == blocked) return true;
	}
	return false;
}

bool global::moderation::isPlayerMuted(PlayerInfo player)
{
	for (PlayerInfo info : MutedPlayers) {
		if (player == info) return true;
	}
	return false;
}

bool global::moderation::isPlayerOnSilence(PlayerInfo player)
{
	for (PlayerInfo info : PlayersOnPMSilence) {
		if (player == info) return true;
	}
	return false;
}

bool global::moderation::AddMutedPlayer(PlayerInfo info)
{
	if (isPlayerMuted(info)) return false;
	MutedPlayers.push_back(info);
	return true;
}

bool global::moderation::RemoveMutedPlayer(PlayerInfo info)
{
	size_t old = MutedPlayers.size();
	MutedPlayers.erase(std::remove(MutedPlayers.begin(), MutedPlayers.end(), info), MutedPlayers.end());
	size_t news = MutedPlayers.size();
	return (news < old);
}

bool global::moderation::AddPMSilencePlayer(PlayerInfo info)
{
	if (isPlayerOnSilence(info)) return false;
	PlayersOnPMSilence.push_back(info);
	return true;
}

bool global::moderation::RemovePMSilencePlayer(PlayerInfo info)
{
	size_t old = PlayersOnPMSilence.size();
	PlayersOnPMSilence.erase(std::remove(PlayersOnPMSilence.begin(), PlayersOnPMSilence.end(), info), PlayersOnPMSilence.end());
	size_t news = PlayersOnPMSilence.size();
	return (news < old);
}

bool global::moderation::AddBlockedPlayer(BlockedPlayer info)
{
	if (isPlayerBlockedBy(info.Blocker, info.Blocked)) return false;
	BlockedPlayers.push_back(info);
	return true;
}

bool global::moderation::RemoveBlockedPlayer(BlockedPlayer info)
{
	size_t old = BlockedPlayers.size();
	BlockedPlayers.erase(std::remove(BlockedPlayers.begin(), BlockedPlayers.end(), info), BlockedPlayers.end());
	size_t news = BlockedPlayers.size();
	return (news < old);
}

bool global::moderation::saveModerationValues()
{
	std::fstream saveFile;
	saveFile.open("MutedPlayers.txt", std::ios::out);
	if (!saveFile.bad() && !saveFile.fail() && saveFile.is_open()) {
		for (PlayerInfo info : MutedPlayers) {
			saveFile << info.name << std::endl;
		}
		saveFile.close();
		return true;
	}
	return false;
}

bool global::moderation::loadModerationValues()
{
	std::fstream saveFile;
	saveFile.open("MutedPlayers.txt", std::ios::in);
	if (!saveFile.bad() && !saveFile.fail() && saveFile.is_open()) {
		std::string line;
		while (std::getline(saveFile, line)) {
			AddMutedPlayer(PlayerInfo(line));
		}
		return true;
	}
	return false;
}

void global::welcome::SendWelcomeMessage()
{
	if (isMapValid()) modules::interpreter::sendUserSpecificMessageWithContext(GetPlayerInfoFromController(GetBrickPlayerController()), WelcomeServerMessage, SDK::EChatContext::Global, L"BRCI");
}

void global::welcome::SendWelcomeMessageA()
{
	modules::interpreter::sendUserSpecificMessageWithContext(GetPlayerInfoFromController(GetBrickPlayerController()), WelcomeServerMessage, SDK::EChatContext::Global, L"BRCI");
}
