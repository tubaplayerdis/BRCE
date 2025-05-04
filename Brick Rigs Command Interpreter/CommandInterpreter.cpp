#include "CommandInterpreter.h"
#include <thread>
#include <functional>
#include <SDK.hpp>
#include "global.h"

void modules::CommandInterpreter::Commands::Night()
{
    using namespace global;
    auto cur = GetBrickGameState()->GetMatchSettings();
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.TimeOfDay = 0.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

void modules::CommandInterpreter::Commands::Day()
{
    using namespace global;
    auto cur = GetBrickGameState()->MatchSettings;
    std::cout << cur.WorldSetupParams.TimeOfDay << std::endl;
    cur.WorldSetupParams.TimeOfDay = 12.00f;
    GetBrickGameState()->SetMatchSettings(cur);
}

size_t hash_string(const std::string& str) {
    std::hash<std::string> hasher;
    return hasher(str);
}

constexpr size_t hs(const char* str) {
    std::size_t hash = 14695981039346656037ull;
    while (*str) {
        hash ^= static_cast<unsigned char>(*str++);
        hash *= 1099511628211ull;
    }
    return hash;
}

void modules::CommandInterpreter::interpretCommand(std::string command)
{
	size_t hash_val = hash_string(command);

	switch (hash_val) {
		case hs("/night"):
            Commands::Night();
            break;
        case hs("/day"):
            Commands::Day();
            break;
        default:
            break;
	}
}

