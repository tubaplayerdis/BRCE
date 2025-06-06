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
Do not use the [] in the actual command call!
Use the following command lists for the commands.
/help main
/help moderation
/help movement
/help enviroment
/help weapons)";

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
/unmute - [who] - Re-Enable a users ability to message (*))";

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

