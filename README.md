# Brick Rigs Command Interpreter

## Overview

The Brick Rigs Command Interpreter (BRCI) adds chat message command functionality to your brick rigs server.

## Development

This project is still under development. The expected release window is later june of 2025

Follow development: https://youtube.com/@johndenver-co9rr

### Todo:

 - Fix weather commands to look more realistic
 - Remove traces of speed command and remove it from helplist and readme
 - Bug test with a closed and open beta.

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

/off [command] - Disables command *  
/on [command] - Enables command *  
/mute [who] - Disable a users ability to message *  
/unmute - [who] - Re-Enable a users ability to message *  
/save - Save the current moderation config to the disk *  
/load - Load the moderation config on the disk *  

### Movement

/fly - Fly around (slow)  
/walk - Walk around  
/speed [1-3] - Change max sprint speed  
/tp [who] - Teleport to other people  
/ghost - Fly around and disable collisions  

#### Enviroment

/night - Make it night  
/day - Make it day  
/rain - Make it rain (!)  
/clear - Clears the weather (!)  

#### Weapons

/ammotype [type] - Changes all weapons in players inventory to the selected ammotype. Does not affect vehicles or weapons held by the player in a vehicle
