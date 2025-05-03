#include "main.h"
#include "global.h"
#include "modules.h"
#include <windows.h>

using namespace global;

void mainLoop()
{
	std::cout << "BRHack Loaded! Starting Setup.\n" << std::endl;

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

	while (true) {

		Sleep(10);

		verifyPointers(); //Check For World Changes
		if (MyController != nullptr) updateLocationVars(); //Check For PlayerControllerChanges

		if (!isWorldHost) continue;

		//Seutp Hooks
	}
}
