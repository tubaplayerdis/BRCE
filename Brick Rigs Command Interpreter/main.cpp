#include "main.h"
#include "global.h"
#include "modules.h"
#include "interpreter.h"
#include <windows.h>
#include "hooks.h"
#include <MinHook.h>
#include "kiero.h"
#include <psapi.h>

using namespace global;

void mainLoop()
{
	std::cout << "BRCI Injected! Starting Setup.\n" << std::endl;

	if (!hooks::InitAllHooks()) {
		MessageBox(GetActiveWindow(), L"Failed To Hook Critical Functions. Uninjecting BCRI.", L"Uninjecting BRCI", MB_OK);
		return;
	}

	Engine = SDK::UEngine::GetEngine();
	World = SDK::UWorld::GetWorld();
	Level = World->PersistentLevel;
	MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;
	mapLevelName = Level->Outer->GetName();
	isChangingMapName = false;

	hooks::EnableAllHooks();

	std::cout << "Starting Main Loop!" << std::endl;

	while (true) {

		Sleep(10);

		if (GetAsyncKeyState(VK_DIVIDE) & 1) break;

		if (updatingPointers) continue;

		if(doVerifyPointers) global::verifyPointers();

		updateLocationVars();

		if (!isWorldHost) continue;

		if (!isMapValid()) continue;
	}

	//uninit hooks
	hooks::DisableAllHooks();

	std::cout << "Uninjecting!" << std::endl;
}
