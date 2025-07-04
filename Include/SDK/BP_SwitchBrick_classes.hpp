﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BP_SwitchBrick

#include "Basic.hpp"

#include "BrickRigs_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass BP_SwitchBrick.BP_SwitchBrick_C
// 0x0000 (0x01A0 - 0x01A0)
class UBP_SwitchBrick_C final : public USwitchBrickStaticInfo
{
public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"BP_SwitchBrick_C">();
	}
	static class UBP_SwitchBrick_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UBP_SwitchBrick_C>();
	}
};
static_assert(alignof(UBP_SwitchBrick_C) == 0x000008, "Wrong alignment on UBP_SwitchBrick_C");
static_assert(sizeof(UBP_SwitchBrick_C) == 0x0001A0, "Wrong size on UBP_SwitchBrick_C");

}

