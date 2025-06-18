/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Aaron Wilk 2025, All rights reserved.                     */
/*                                                                            */
/*    Module:     HelpLists.h                                                 */
/*    Author:     Aaron Wilk                                                  */
/*    Created:    20 May 2025                                                 */
/*                                                                            */
/*    Revisions:  V0.1                                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma once
#include <string>

inline std::string MasterHelpMessage = R"(
/help main
/help moderation
/help movement
/help enviroment
/help weapons
/info)";

inline std::string MainHelpMessage = R"(
Do not use the [] in the actual command call!
Main Commands:
/pm [who] [content] - Personal Message Someone
/pma - allow incoming personal messages
/pmd - disallow incoming personal messages
/block [who] - Block a user from personal messaging you
/unblock [who] - Un-Block a user from personal messaging you)";

inline std::string ModerationHelpMessage = R"(
Do not use the [] in the actual command call!
(*) = Admin Only
Moderation Commands:
/off [command] - Disables command (*)
/on [command] - Enables command (*)
/mute [who] - Disable a users ability to message (*)
/unmute - [who] - Re-Enable a users ability to message (*)
/save - Save the current moderation config to the disk (*)
/load - Load the moderation config on the disk (*))";

inline std::string MovementHelpMessage = R"(
Do not use the [] in the actual command call!
Movement Commands:
/fly - Fly around (slow)
/walk - Walk around
/speed [1-3] - Change max sprint speed
/tp - Telport to where you are looking
/tp [who] - Teleport to other people
/ghost - Fly around and disable collisions)";

inline std::string EnviromentHelpMessage = R"(
Do not use the [] in the actual command call!
Enviroment Commands:
/night - Make it night
/day - Make it day
/rain - Make it rain
/clear - Clears the weather)";

inline std::string WeaponsHelpMessage = R"(
Do not use the [] in the actual command call!
Weapon Commands:
/bombgun - Get a bombgun!)";

inline std::string InfoMessage = R"(Brick Rigs Command Interpreter(BRCI), is a chat command mod made for Bricks Rigs that adds chat message functionality to your server. It is dll based and server-side only.
Star the GitHub: https://github.com/tubaplayerdis/BRCI
Follow the Creator: https://github.com/tubaplayerdis
)";


#ifdef _DEBUG
inline std::string WelcomeServerMessage = R"((DEV)Thank you for using the Brick Rigs Command Interpreter(BRCI). Use /help to get started!)";
#else
inline std::string WelcomeServerMessage = R"(Thank you for using the Brick Rigs Command Interpreter(BRCI). Use /help to get started!)";
#endif

inline std::string WelcomeClientMessage = R"(This server uses the Brick Rigs Command Interpreter(BRCI). Use /help to get started!)";