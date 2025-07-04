/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Aaron Wilk 2025, All rights reserved.                     */
/*                                                                            */
/*    Module:     hooks.h                                                     */
/*    Author:     Aaron Wilk                                                  */
/*    Created:    3 May 2025                                                  */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma once
#include "ChatMessageHooks.h"
#include "GlobalHooks.h"
#include <chrono>
#include <fstream>
#include <windows.h>
#include <shellapi.h>

#pragma comment(lib, "shell32.lib")

namespace hooks
{
	inline bool InitAllHooks() {
		std::cout << "Finding Hooks!" << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		bool ACMHook = AddChatMessage::Init();
		bool BPHook = BeginPlay::Init();
		bool OMHook = OpenMenu::Init();
		bool SYNCHook = Functions::SynchronizeProperties::Init();//0
		bool ONJHook = OnPlayerJoined::Init();//0
		bool RGHook = StartPlay::Init();
		bool LMHook = LoadMap::Init();
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Elapsed Time Finding Hooks: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
		if (!ACMHook || !BPHook || !OMHook || !SYNCHook || !ONJHook || !RGHook || !LMHook) {
			//print cases
			std::cout << "ACMHOOK: " << ACMHook << std::endl;
			std::cout << "BPHOOK: " << BPHook << std::endl;
			std::cout << "OMHOOK: " << OMHook << std::endl;
			std::cout << "SYNCHOOK: " << SYNCHook << std::endl;
			std::cout << "ONJHOOK:" << ONJHook << std::endl;
			std::cout << "RGHOOK:" << RGHook << std::endl;
			std::cout << "LMHook" << LMHook << std::endl;

			//Print cases to file
			std::ofstream saveFile;
			saveFile.open("BRCECRASH.txt", std::ios::trunc);
			if (!saveFile.bad() && !saveFile.fail() && saveFile.is_open()) {
				saveFile << "Hooks have a possibility of loading incorrectly given a version change for BR. This is normal an update should be out soon fixing this if that is the case." << std::endl;
				saveFile << "ACMHOOK: " << ACMHook << std::endl;
				saveFile << "BPHOOK: " << BPHook << std::endl;
				saveFile << "OMHOOK: " << OMHook << std::endl;
				saveFile << "SYNCHOOK: " << SYNCHook << std::endl;
				saveFile << "ONJHOOK:" << ONJHook << std::endl;
				saveFile << "RGHOOK:" << RGHook << std::endl;
				saveFile << "LMHook" << LMHook << std::endl;
				saveFile.close();
			}
			return false;
		}
		return true;
	}

	inline void EnableAllHooks() {
		AddChatMessage::Enable();
		BeginPlay::Enable();
		OpenMenu::Enable();
		OnPlayerJoined::Enable();
		StartPlay::Enable();
		LoadMap::Enable();
		//PossessedBy::Enable();
	}

	//This is should not be used anymore
	inline void DisableAllHooks() {
		//Disable all hooks in one place
		AddChatMessage::Disable();
		BeginPlay::Disable();
		OpenMenu::Disable();
		OnPlayerJoined::Disable();
		StartPlay::Disable();
		//LoadMap::Disable();
		//PossessedBy::Disable();
	}

	inline void OpenCrashFile() {
		DWORD bufsize = GetCurrentDirectory(0, NULL);
		std::wstring curDir(bufsize, L'\0');
		GetCurrentDirectory(bufsize, &curDir[0]);

		// Remove trailing null char left by GetCurrentDirectory
		curDir.resize(wcslen(curDir.c_str()));

		// Add backslash if missing
		if (!curDir.empty() && curDir.back() != L'\\') {
			curDir += L'\\';
		}
		curDir += L"BRCECRASH.txt";
		ShellExecute(NULL, L"open", curDir.c_str(), NULL, NULL, SW_SHOW);
	}
}