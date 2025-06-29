/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Aaron Wilk 2025, All rights reserved.                     */
/*                                                                            */
/*    Module:     main.cpp                                                    */
/*    Author:     Aaron Wilk                                                  */
/*    Created:    3 May 2025                                                  */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "main.h"
#include "modules.h"
#include "interpreter.h"
#include <windows.h>
#include "global.h"
#include "hooks.h"
#include <MinHook.h>
#include <psapi.h>
#include "SDK.hpp"

#define PRESSED 0x8000

#ifdef _DEBUG
#define UninjectPress() GetAsyncKeyState(VK_DIVIDE) & 1
#define TogglePress() GetAsyncKeyState(VK_MULTIPLY) & 1
#else
#define UninjectPress() (IsActiveWindow() && (GetAsyncKeyState(VK_CONTROL) & PRESSED) && (GetAsyncKeyState('U') & PRESSED))
#define TogglePress() (IsActiveWindow() && (GetAsyncKeyState(VK_CONTROL) & PRESSED) && (GetAsyncKeyState('T') & PRESSED))
#endif

#define ContinuePress() (IsActiveWindow() && (GetAsyncKeyState(VK_RETURN) & 1))

using namespace global;

void mainLoop()
{
	std::cout << reinterpret_cast<const char*>(CommandLineLogo) << std::endl;

	//Find a way to alert the user that BRCE is loaded without using the console. Maybe try to make a notification out of a text border. a watermark is currently used but it might not be enough.

	if (!hooks::InitAllHooks()) {
		if (MessageBox(GetActiveWindow(), L"Failed To Hook Critical Functions. Uninjecting BCRE. Would you like to look at the crash log?", L"Uninjecting BRCE", MB_YESNO) == IDYES) hooks::OpenCrashFile();
		return;
	}

	global::InitPointers();

	hooks::EnableAllHooks();

	global::watermark::InitalizeWaterMark();

	if(IsHost()) global::welcome::SendWelcomeMessage();

	std::cout << "Starting Main Loop!" << std::endl;

	while (true) {

		Sleep(10);

		if (ContinuePress()) {
			std::cout << IsActiveWindow() << std::endl;
			continue;
		}

		if (UninjectPress() || doUninject) break;

		if (TogglePress()) {
			if (hooks::AddChatMessage::enabled) {
				hooks::AddChatMessage::Disable();
				SendNotificationLocal(L"Disabled Chat Commands!", 1); //Explore the icon atlas more
			}
			else {
				hooks::AddChatMessage::Enable();
				SendNotificationLocal(L"Enabled Chat Commands!", 0);
			}
		}
	}

	global::watermark::HideWaterWark();
	global::watermark::UnInitalizeWaterMark();

	modules::interpreter::sendMessageToAdmin("Uninjecting BRCE!");
	SendNotificationLocal(L"Uninjecting BRCE", 9);
}
