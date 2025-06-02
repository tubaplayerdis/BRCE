#include "main.h"
#include "global.h"
#include "modules.h"
#include "interpreter.h"
#include <windows.h>
#include "hooks.h"
#include <MinHook.h>
#include "kiero.h"
#include <psapi.h>
#include "SDK.hpp"
#include "menu.h"

using namespace global;

void mainLoop()
{
	std::cout << reinterpret_cast<const char*>(CommandLineLogo) << std::endl;

	//Find a way to alert the user that BRCI is loaded without using the console.

	if (!hooks::InitAllHooks()) {
		MessageBox(GetActiveWindow(), L"Failed To Hook Critical Functions. Uninjecting BCRI.", L"Uninjecting BRCI", MB_OK);
		menu::shouldExit = true;
		return;
	}

	if (SDK::UWindowManagerWidget::Get(World) != nullptr) {
		SDK::UNetworkErrorPopupParams parms = SDK::UNetworkErrorPopupParams();
		auto wm = SDK::UWindowManagerWidget::Get(World);
		std::cout << wm->PopupContainerWidgets.Num() << std::endl;
	}


	global::InitPointers();

	hooks::EnableAllHooks();

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

	modules::interpreter::sendMessageToAdmin("Uninjecting BRCI!");
	SendNotificationLocal(L"Uninjecting BRCI", 9);

	menu::shouldExit = true;

	std::cout << "Uninjecting!" << std::endl;
}
