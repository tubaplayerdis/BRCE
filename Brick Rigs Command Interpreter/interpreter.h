#pragma once
#include <string>

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
			void Enable(PlayerInfo info, std::string command);
			void Disable(PlayerInfo info, std::string command);
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
		void interpretCommand(std::string command, PlayerInfo info);
		void sendUserSpecificMessage(PlayerInfo info, std::string message);
		void sendMessageToAdmin(std::string message);
	}
}
