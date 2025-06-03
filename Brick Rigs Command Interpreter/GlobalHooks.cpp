/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Aaron Wilk 2025, All rights reserved.                     */
/*                                                                            */
/*    Module:     GlobalHooks.cpp                                             */
/*    Author:     Aaron Wilk                                                  */
/*    Created:    27 May 2025                                                 */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "GlobalHooks.h"
#include "MinHook.h"
#include "global.h"
#include "ChatMessageHooks.h"

void __fastcall hooks::BeginPlay::HookedBeginPlayFunction(SDK::UWorld* This)
{
	OriginalBeginPlayFunction(This);
	global::UpdatePointers(This);
	if (global::isMapValid()) global::watermark::HideWaterWark();
	else global::watermark::ShowWaterMark();
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

char hooks::Functions::OpenPopup::OpenPopup(SDK::UWindowManagerWidget* This, SDK::UClass* HandleT, SDK::UPopupParams* PopupParams, bool bToggleOpen)
{
	uintptr_t OpenPopupFunction = (uintptr_t)GetModuleHandle(NULL) + 0x0DCBA60;

	using OpenPopupFn = char (__fastcall*)(SDK::UWindowManagerWidget* Thiss, SDK::UClass* HandleTT, SDK::UPopupParams* PopupParamss, bool bToggleOpenn);
	OpenPopupFn OnOpenPopupFunction = reinterpret_cast<OpenPopupFn>(OpenPopupFunction);

	return OnOpenPopupFunction(This, HandleT, PopupParams, bToggleOpen);
}

char hooks::Functions::Initalize::Initalize(SDK::UPopupContainerWidget* This)
{
	uintptr_t InitalizeFunction = (uintptr_t)GetModuleHandle(NULL) + 0x0D59D10;

	using InitalizeFn = char(__fastcall*)(SDK::UPopupContainerWidget* Thiss);
	InitalizeFn OnInitalizeFunction = reinterpret_cast<InitalizeFn>(InitalizeFunction);

	return OnInitalizeFunction(This);
}

void __fastcall hooks::DrawTransition::HookedDrawTransitionFunction(SDK::UGameViewportClient* This, SDK::UCanvas* Canvas)
{
	SDK::FVector2D loc = SDK::FVector2D();
	loc.X = 100;
	loc.Y = 100;
	SDK::FVector2D size = SDK::FVector2D();
	size.X = 100;
	size.Y = 100;
	Canvas->K2_DrawBox(loc, size, 10, hooks::constructors::CreateLinearColor(255, 0, 0, 1));
	OriginalDrawTransitionFunction(This, Canvas);
}

bool hooks::DrawTransition::Init()
{
	if (initalized) return false;
	DrawTransitionFunctionPointer = FindPattern(pattern, mask, GetModuleBaseN(), GetModuleSizeN());
	if (DrawTransitionFunctionPointer == 0) return false;
	MH_STATUS ret = MH_CreateHook((LPVOID)DrawTransitionFunctionPointer, &HookedDrawTransitionFunction, (void**)&OriginalDrawTransitionFunction);
	initalized = true;
	return ret == MH_OK;
}

void hooks::DrawTransition::Enable()
{
	if (!initalized || enabled) return;
	MH_EnableHook((LPVOID)DrawTransitionFunctionPointer);
	enabled = true;
}

void hooks::DrawTransition::Disable()
{
	if (!initalized || !enabled) return;
	MH_DisableHook((LPVOID)DrawTransitionFunctionPointer);
	enabled = false;
}

void hooks::Functions::SynchronizeProperties::SynchronizeProperties(SDK::UBrickBorder* This)
{
	if (SynchronizePropertiesFunction == 0) {
		std::cout << "Finding first time signature for syncprops!" << std::endl;
		SynchronizePropertiesFunction = FindPattern(pattern, mask, GetModuleBaseN(), GetModuleSizeN());
		std::cout << "Found signature!" << std::endl;
	}

	using SynchronizePropertiesFn = void(__fastcall*)(SDK::UBrickBorder* Thiss);
	SynchronizePropertiesFn OnInitalizeFunction = reinterpret_cast<SynchronizePropertiesFn>(SynchronizePropertiesFunction);

	OnInitalizeFunction(This);
}

void __fastcall hooks::OpenMenu::HookedOpenMenuFunction(SDK::UMenuWidget* This, SDK::FName InMenu)
{
	std::cout << InMenu.GetRawString() << std::endl;
	if (InMenu.GetRawString() == "InGameMenu") global::watermark::ShowWaterMark();
	if (InMenu.GetRawString() == "None" && global::isMapValid()) global::watermark::HideWaterWark();
	OriginalOpenMenuFunction(This, InMenu);
}

bool hooks::OpenMenu::Init()
{
	if (initalized) return false;
	OpenMenuFunctionPointer = FindPattern(pattern, mask, GetModuleBaseN(), GetModuleSizeN());
	if (OpenMenuFunctionPointer == 0) return false;
	MH_STATUS ret = MH_CreateHook((LPVOID)OpenMenuFunctionPointer, &HookedOpenMenuFunction, (void**)&OriginalOpenMenuFunction);
	initalized = true;
	return ret == MH_OK;
}

void hooks::OpenMenu::Enable()
{
	if (!initalized || enabled) return;
	MH_EnableHook((LPVOID)OpenMenuFunctionPointer);
	enabled = true;
}

void hooks::OpenMenu::Disable()
{
	if (!initalized || !enabled) return;
	MH_DisableHook((LPVOID)OpenMenuFunctionPointer);
	enabled = false;
}
