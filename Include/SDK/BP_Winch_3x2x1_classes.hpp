﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BP_Winch_3x2x1

#include "Basic.hpp"

#include "BrickRigs_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass BP_Winch_3x2x1.BP_Winch_3x2x1_C
// 0x0000 (0x01C0 - 0x01C0)
class UBP_Winch_3x2x1_C final : public UWinchBrickStaticInfo
{
public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"BP_Winch_3x2x1_C">();
	}
	static class UBP_Winch_3x2x1_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UBP_Winch_3x2x1_C>();
	}
};
static_assert(alignof(UBP_Winch_3x2x1_C) == 0x000010, "Wrong alignment on UBP_Winch_3x2x1_C");
static_assert(sizeof(UBP_Winch_3x2x1_C) == 0x0001C0, "Wrong size on UBP_Winch_3x2x1_C");

}

