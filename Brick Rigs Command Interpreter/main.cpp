#include "main.h"
#include "modules.h"
#include "interpreter.h"
#include <windows.h>
#include "global.h"
#include "hooks.h"
#include <MinHook.h>
#include <psapi.h>
#include "SDK.hpp"

using namespace global;

void mainLoop()
{
	std::cout << reinterpret_cast<const char*>(CommandLineLogo) << std::endl;

	//Find a way to alert the user that BRCI is loaded without using the console. Maybe try to make a notification out of a text border. a watermark is currently used but it might not be enough.

	if (!hooks::InitAllHooks()) {
		MessageBox(GetActiveWindow(), L"Failed To Hook Critical Functions. Uninjecting BCRI.", L"Uninjecting BRCI", MB_OK);
		return;
	}

	global::InitPointers();

	hooks::EnableAllHooks(); //Excludes the rendering hook.

	global::watermark::InitalizeWaterMark();

	std::cout << "Starting Main Loop!" << std::endl;

	while (true) {

		Sleep(10);

		if (GetAsyncKeyState(VK_RETURN) & 1) continue;

		if (GetAsyncKeyState(VK_DIVIDE) & 1) break;

		if (GetAsyncKeyState(VK_MULTIPLY) & 1) {
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

	modules::interpreter::sendMessageToAdmin("Uninjecting BRCI!");
	SendNotificationLocal(L"Uninjecting BRCI", 9);

	std::cout << "Uninjecting!" << std::endl;
}
