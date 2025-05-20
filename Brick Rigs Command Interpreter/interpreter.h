#pragma once
#include <string>

struct PlayerInfo
{
	std::string name;
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
		}
		void interpretCommand(std::string command, PlayerInfo info);
		void sendUserSpecificMessage(PlayerInfo info, std::string message);
	}
}
