#include "main.h"
#include "global.h"
#include "modules.h"
#include <windows.h>
#include <MinHook.h>
#include "hooks.h"

using namespace global;

void mainLoop()
{
	std::cout << "BRCI Injected! Starting Setup.\n" << std::endl;

	Engine = SDK::UEngine::GetEngine();
	World = SDK::UWorld::GetWorld();
	Level = World->PersistentLevel;
	MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
	mapLevelName = Level->Outer->GetName();
	isChangingMapName = false;

	if (GetModuleHandle(L"MinHook.x64.dll") == NULL) {
		MessageBox(NULL, L"Please Inject MinHook.x64.dll Before Loading. Uninjecting.", L"Uninjecting BRCI", MB_OK);
		return;
	}

	if (!hooks::ClientRecieveChatMessage::Init()) {
		MessageBox(NULL, L"Failed To Hook Critical Functions. Uninjecting.", L"Uninjecting BRCI", MB_OK);
		return;
	}
	hooks::ClientRecieveChatMessage::Enable();

	while (true) {

		Sleep(10);

		if (GetAsyncKeyState(VK_DIVIDE) & 1) break;

		verifyPointers(); //Check For World Changes
		if (MyController != nullptr) updateLocationVars(); //Check For PlayerControllerChanges

		if (!isWorldHost) continue;

		if (!isMapValid()) continue;
	}

	//uninit hooks
	hooks::ClientRecieveChatMessage::Disable();
	MH_Uninitialize();

	std::cout << "Uninjecting!" << std::endl;
}
