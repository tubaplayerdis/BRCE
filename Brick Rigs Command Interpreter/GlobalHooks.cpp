#include "GlobalHooks.h"
#include "MinHook.h"
#include "global.h"
#include "ChatMessageHooks.h"

void __fastcall hooks::BeginPlay::HookedBeginPlayFunction(SDK::UWorld* This)
{
	OriginalBeginPlayFunction(This);
	global::UpdatePointers(This);
}

bool hooks::BeginPlay::Init()
{
	if (initalized) return false;
	BeginPlayFunctionPointer = FindPattern(pattern, mask, GetModuleBaseN(), GetModuleSizeN());
	if (BeginPlayFunctionPointer == 0) return false;
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

SDK::UUserWidget* hooks::Functions::CreateWidget::CreateWidget(SDK::UWorld* OwningObject, SDK::TSubclassOf<SDK::UUserWidget> UserWidgetClass, SDK::FName WidgetName)
{
	uintptr_t CreateWidgetFunction = (uintptr_t)GetModuleHandle(NULL) + 0x0CA5CC0;

	using CreateWidgetFn = SDK::UUserWidget*(__fastcall*)(SDK::UWorld* OwningObject, SDK::TSubclassOf<SDK::UUserWidget> UserWidgetClass, SDK::FName WidgetName);
	CreateWidgetFn OnCreateWidgetFunction = reinterpret_cast<CreateWidgetFn>(CreateWidgetFunction);

	return OnCreateWidgetFunction(OwningObject, UserWidgetClass, WidgetName);
}
