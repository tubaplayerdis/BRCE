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

#### Management

/help - Provides help with commands and displays command list

/off [command] - Disables command (Admin Only)

/on [command] - Enables command(Admin Only)

/pm [who] [content] - Personal Message Someone

/mute [who] - Disable a users ability to speak in chat and personal message other users (Admin Only)

/unmute - [who] - Re-Enable a users ability to speak in chat and personal message other users (Admin Only)

/pma - allow incoming personal messages

/pmd - disallow incoming personal messages

/block [who] - Block a user from personal messaging you

/unblock [who] - Un-Block a user from personal messaging you


#### Movement

/fly - Turns the players movement mode to flying

/walk - Turns the players movement mode to walking

/speed [1-3] - changes the players speed based off input (!)

/tp - teleports player to the place they are looking (!)

/ghost - disables collision with the world and player can fly (!)


#### Enviroment

/night - Turns world to night

/day - Turns world to day

/rain - starts rain (!)

/clear - sets weather to clear (!)

#### Weapons

/bombgun - gives the player a gun that shoots bombs (!)
