#pragma once
#include <string>

namespace modules
{
	namespace CommandInterpreter
	{
		namespace Commands
		{
			void Night();
			void Day();
		}
		void interpretCommand(std::string command);
	}
}
