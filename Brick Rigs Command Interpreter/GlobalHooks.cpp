#include "GlobalHooks.h"
#include "MinHook.h"
#include "global.h"

void __fastcall hooks::BeginPlay::HookedBeginPlayFunction(SDK::UWorld* This)
{
	OriginalBeginPlayFunction(This);
	global::doVerifyPointers = true; //Workaround to have verifyPointers() run on the main thread
}

bool hooks::BeginPlay::Init()
{
	if (initalized) return false;
	if (!BeginPlayFunctionPointer) return false;
	MH_STATUS ret = MH_CreateHook((LPVOID)BeginPlayFunctionPointer, &HookedBeginPlayFunction, (void**)&OriginalBeginPlayFunction);
	initalized = true;
	return ret == MH_OK;
}

void hooks::BeginPlay::Enable()
{
	if (!initalized || enabled) return;
	MH_EnableHook((LPVOID)BeginPlayFunctionPointer);
	enabled = true;
}

void hooks::BeginPlay::Disable()
{
	if (!initalized || !enabled) return;
	MH_DisableHook((LPVOID)BeginPlayFunctionPointer);
	enabled = false;
}

void __fastcall hooks::PossessedBy::HookedPossessedByFunction(SDK::APawn* This, SDK::AController* NewController)
{
	std::cout << "Actor Possessed!" << std::endl;
	OriginalPossessedByFunction(This, NewController);
}

bool hooks::PossessedBy::Init()
{
	if (initalized) return false;
	if (!PossessedByFunctionPointer) return false;
	MH_STATUS ret = MH_CreateHook((LPVOID)PossessedByFunctionPointer, &HookedPossessedByFunction, (void**)&OriginalPossessedByFunction);
	initalized = true;
	return ret == MH_OK;
}

void hooks::PossessedBy::Enable()
{
	if (!initalized || enabled) return;
	MH_EnableHook((LPVOID)PossessedByFunctionPointer);
	enabled = true;
}

void hooks::PossessedBy::Disable()
{
	if (!initalized || !enabled) return;
	MH_DisableHook((LPVOID)PossessedByFunctionPointer);
	enabled = false;
}

SDK::UUserWidget* hooks::Functions::CreateWidget::CreateWidget(SDK::UWorld* OwningObject, SDK::TSubclassOf<SDK::UUserWidget> UserWidgetClass, SDK::FName WidgetName)
{
	uintptr_t CreateWidgetFunction = (uintptr_t)GetModuleHandle(NULL) + 0x0CA5CC0;

	using CreateWidgetFn = SDK::UUserWidget*(__fastcall*)(SDK::UWorld* OwningObject, SDK::TSubclassOf<SDK::UUserWidget> UserWidgetClass, SDK::FName WidgetName);
	CreateWidgetFn OnCreateWidgetFunction = reinterpret_cast<CreateWidgetFn>(CreateWidgetFunction);

	return OnCreateWidgetFunction(OwningObject, UserWidgetClass, WidgetName);
}
