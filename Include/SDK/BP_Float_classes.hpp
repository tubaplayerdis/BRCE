﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: BP_Float

#include "Basic.hpp"

#include "BrickRigs_classes.hpp"


namespace SDK
{

// BlueprintGeneratedClass BP_Float.BP_Float_C
// 0x0000 (0x01A0 - 0x01A0)
class UBP_Float_C final : public UFloatBrickStaticInfo
{
public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"BP_Float_C">();
	}
	static class UBP_Float_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UBP_Float_C>();
	}
};
static_assert(alignof(UBP_Float_C) == 0x000008, "Wrong alignment on UBP_Float_C");
static_assert(sizeof(UBP_Float_C) == 0x0001A0, "Wrong size on UBP_Float_C");

}

