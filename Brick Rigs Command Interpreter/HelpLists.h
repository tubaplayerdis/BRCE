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
/help controls (Host Only)
/help main
/help moderation
/help movement
/help enviroment
/help weapons
/info
/uninject)";

#ifdef _DEBUG

inline std::string ControlsHelpMessage = R"(These only work on the host!
Divide - Uninject
Multiply - Toggle Chat Commands
Return - (Fix Freezes))";

#else

inline std::string ControlsHelpMessage = R"(These only work on the host!
CTRL-U - Uninject
CTRL-T - Toggle Chat Commands
Return - (Fix Freezes))";

#endif // _DEBUG

inline std::string MainHelpMessage = R"(You can use PlayerID's for pm/block. use /pid
Main Commands:
/pm [who] [content] - Personal Message Someone
/pma - allow incoming personal messages
/pmd - disallow incoming personal messages
/block [who] - Block a user from personal messaging you
/unblock [who] - Un-Block a user from personal messaging you
/pid - List every players PlayerID)";

inline std::string ModerationHelpMessage = R"(You can use PlayerID's for mute/unmute. use /pid
(*) = Admin Only
Moderation Commands:
/off [command] - Disables command (*)
/on [command] - Enables command (*)
/mute [who] - Disable a users ability to message (*)
/unmute - [who] - Re-Enable a users ability to message (*)
/save - Save the current moderation config to the disk (*)
/load - Load the moderation config on the disk (*))";

inline std::string MovementHelpMessage = R"(Movement Commands:
/fly - Fly around (slow)
/walk - Walk around
/tp [who] - Teleport to other people
/ghost - Fly around and disable collisions)";

inline std::string EnviromentHelpMessage = R"(Enviroment Commands:
/night - Make it night
/day - Make it day
/rain - Make it rain
/sun - Make it sunny)";

inline std::string WeaponsHelpMessage = R"(Weapon Commands:
/ammotype [type] - Change all your guns to the selected ammo type. Ammotypes:
0 - Default
1 - Incendiary
2 - HighExplosive
3 - TargetSeeking
4 - Guided
5 - Flare
*ammotype will NOT change the ammotype on weaons you hold inside a vehicle or a vehicles weapons)";
//List the ammo types later

inline std::string InfoMessage = R"(Brick Rigs Command Interpreter(BRCI), is a chat command mod made for Bricks Rigs that adds chat message functionality to your server. It is dll based and server-side only.
Star the GitHub: https://github.com/tubaplayerdis/BRCI
Follow the Creator: https://github.com/tubaplayerdis
)";

inline std::string BypassPassword = "uno";


#ifdef _DEBUG
inline std::string WelcomeServerMessage = R"((DEV)Thank you for using the Brick Rigs Command Interpreter(BRCI). Use /help to get started!)";
#else
inline std::string WelcomeServerMessage = R"(Thank you for using the Brick Rigs Command Interpreter(BRCI). Use /help to get started!)";
#endif

inline std::string WelcomeClientMessage = R"(This server uses the Brick Rigs Command Interpreter(BRCI). Use /help to get started!)";