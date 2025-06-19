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

	bool operator==(const PlayerInfo& other) const {
		return other.name == name;
	}
};

struct BlockedPlayer
{
	PlayerInfo Blocker;
	PlayerInfo Blocked;

	BlockedPlayer() {
		Blocker = PlayerInfo();
		Blocked = PlayerInfo();
	}

	BlockedPlayer(std::string blocker, std::string blocked) {
		Blocker = PlayerInfo(blocker);
		Blocked = PlayerInfo(blocked);
	}

	BlockedPlayer(PlayerInfo blocker, PlayerInfo blocked) {
		Blocker = PlayerInfo(blocker);
		Blocked = PlayerInfo(blocked);
	}

	bool operator==(const BlockedPlayer& other) const {
		return (Blocker == other.Blocker && Blocked == other.Blocked);
	}
};

namespace modules
{
	namespace interpreter
	{
		namespace Commands
		{
			//Management
			void Toggle(PlayerInfo info, std::string command, bool toggle);
			void PersonalMessage(PlayerInfo info, std::string originalMessage);
			void Help(PlayerInfo info, std::string arg);

			//Movement
			bool Fly(PlayerInfo info);
			bool Walk(PlayerInfo info);
			bool Speed(PlayerInfo info, char level);
			bool Teleport(PlayerInfo info);
			bool Ghost(PlayerInfo info);

			//Enviroment
			bool Night(PlayerInfo info);
			bool Day(PlayerInfo info);
			bool Rain(PlayerInfo info);
			bool Sun(PlayerInfo info);

			//Weapons
			bool AmmoType(PlayerInfo info, std::string ammotype);

			//Misc
			void Debug(PlayerInfo info); //Use this to test varius functions. Can be called by imgui.

			namespace Moderation
			{
				void ToggleMute(PlayerInfo info, std::string originalMessage, bool on_of);
				void ToggleBlock(PlayerInfo info, std::string originalMessage, bool on_off);
				void ToggleSilence(PlayerInfo info, bool on_off);
				void Save(PlayerInfo info);
				void Load(PlayerInfo info);
				void ListMuted(PlayerInfo info);
				void ListBlocked(PlayerInfo info);
				void IsOnSilence(PlayerInfo info);
				void ListPlayerIDS(PlayerInfo info);
			}

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
		void interpretCommand(std::string command, std::vector<std::string> args, PlayerInfo info, std::string originalMessage);

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

		/*
		* Send a specified user a message with context as the Command Failed! sender.
		* info - Recipient info
		* message - message content
		* context - Brick Rigs's chat context
		*/
		inline void sendUserSpecificMessageCommandFailed(PlayerInfo info, std::string message) { sendUserSpecificMessageWithContext(info, message, SDK::EChatContext::Global, L"Command Failed!"); }

		inline void ToFewArgs(PlayerInfo info, std::string commandstr, std::string cmdgroup) { sendUserSpecificMessageCommandFailed(info, std::string("Too few arguments used in command: ") + commandstr + std::string("\nUse /help ") + cmdgroup + std::string(" for more details!")); };


		void sendMessageToAdmin(std::string message);
	}
}
