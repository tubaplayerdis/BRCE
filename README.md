# Brick Rigs Command Interpreter

## Overview

The Brick Rigs Command Interpreter (BRCI) adds chat message command functionality to your brick rigs server.

## Development

This project is still under development. The expected release window is later june of 2025

### Todo:

 - Change README command list groups
 - Implement unimplemented commands
 - Fix freezing/hook/memory issues

### Commands

(!) = Still being worked on or not implemented
(*) = Admin Only

### Master

/help main - main command list
/help moderation - moderation command list
/help movement - movement command list
/help enviroment - enviroment command list
/help weapons - weapons command list
/info - Info about BRCI

#### Main

/pm [who] [content] - Personal Message Someone
/pma - allow incoming personal messages
/pmd - disallow incoming personal messages
/block [who] - Block a user from personal messaging you
/unblock [who] - Un-Block a user from personal messaging you
/pid - List every players PlayerID

#### Moderation

/off [command] - Disables command (*)
/on [command] - Enables command (*)
/mute [who] - Disable a users ability to message (*)
/unmute - [who] - Re-Enable a users ability to message (*)
/save - Save the current moderation config to the disk (*)
/load - Load the moderation config on the disk (*)

### Movement

/fly - Fly around (slow)
/walk - Walk around
/speed [1-3] - Change max sprint speed
/tp - Telport to where you are looking (!)
/tp [who] - Teleport to other people (1)
/ghost - Fly around and disable collisions

#### Enviroment

/night - Make it night
/day - Make it day
/rain - Make it rain (!)
/clear - Clears the weather (!)

#### Weapons

/bombgun - gives the player a gun that shoots bombs (!)
