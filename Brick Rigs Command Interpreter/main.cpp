#include "main.h"
#include "global.h"
#include "modules.h"
#include "interpreter.h"
#include <windows.h>
#include "hooks.h"
#include <MinHook.h>
#include "kiero.h"

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

	if (!hooks::AddChatMessage::Init()) {
		MessageBox(NULL, L"Failed To Hook Critical Functions. Uninjecting.", L"Uninjecting BRCI", MB_OK);
		return;
	}
	hooks::AddChatMessage::Enable();

	std::cout << "Starting Main Loop!" << std::endl;

	while (true) {

		Sleep(10);

		if (GetAsyncKeyState(VK_DIVIDE) & 1) break;

		verifyPointers(); //Check For World Changes
		if (MyController != nullptr) updateLocationVars(); //Check For PlayerControllerChanges

		if (!isWorldHost) continue;

		if (!isMapValid()) continue;
	}

	//uninit hooks
	hooks::DisableAllHooks();

	std::cout << "Uninjecting!" << std::endl;
}
