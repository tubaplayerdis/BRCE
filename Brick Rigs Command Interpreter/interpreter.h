/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Aaron Wilk 2025, All rights reserved.                     */
/*                                                                            */
/*    Module:     Interpreter.h                                               */
/*    Author:     Aaron Wilk                                                  */
/*    Created:    19 May 2025                                                 */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma once
#include <string>
#include <vector>
#include "SDK/BrickRigs_structs.hpp"

struct PlayerInfo
{
	std::string name;

	PlayerInfo() {
		name = "None";
	}

	PlayerInfo(std::string cname) {
		name = cname;
	}
};

namespace modules
{
	namespace interpreter
	{
		namespace Commands
		{
			//Management
			void Command(PlayerInfo info);
			void Toggle(PlayerInfo info, std::string command, bool toggle);
			void PersonalMessage(PlayerInfo info, std::string message);
			void Help(PlayerInfo info);

			//Movement
			void Fly(PlayerInfo info);
			void Walk(PlayerInfo info);
			void Speed(PlayerInfo info, char level);
			void Teleport(PlayerInfo info);
			void Ghost(PlayerInfo info);

			//Enviroment
			void Night(PlayerInfo info);
			void Day(PlayerInfo info);
			void Rain(PlayerInfo info);
			void Sun(PlayerInfo info);

			//Weapons
			void BombGun(PlayerInfo info);

			//Misc
			void Debug(PlayerInfo info); //Use this to test varius functions. Can be called by imgui.

			//Toggles for wether or not a command is enabled or disabled

			inline bool isPM = true;

			inline bool isFly = true;
			inline bool isWalk = true;
			inline bool isSpeed = true;
			inline bool isTeleport = true;
			inline bool isGhost = true;

			inline bool isNight = true;
			inline bool isDay = true;
			inline bool isRain = true;
			inline bool isSun = true;

			inline bool isBombGun = true;
		}
		void interpretCommand(std::string command, std::vector<std::string> args, PlayerInfo info);

		/*
		* Send a specified user a message. messages send from user "Command Interpreter" with default message context
		* info - Recipient info
		* message - message context
		*/
		void sendUserSpecificMessage(PlayerInfo info, std::string message);

		/*
		* Send a specified user a message with context and sender options.
		* info - Recipient info
		* message - message content
		* context - Brick Rigs's chat context
		* sender - custom sender name.
		*/
		void sendUserSpecificMessageWithContext(PlayerInfo info, std::string message, SDK::EChatContext context, const wchar_t* sender);


		void sendMessageToAdmin(std::string message);
	}
}
