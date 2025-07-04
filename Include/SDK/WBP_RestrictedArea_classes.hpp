﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: WBP_RestrictedArea

#include "Basic.hpp"

#include "Engine_structs.hpp"
#include "BrickRigs_classes.hpp"


namespace SDK
{

// WidgetBlueprintGeneratedClass WBP_RestrictedArea.WBP_RestrictedArea_C
// 0x0030 (0x02A8 - 0x0278)
class UWBP_RestrictedArea_C final : public URestrictedAreaWidget
{
public:
	struct FPointerToUberGraphFrame               UberGraphFrame;                                    // 0x0278(0x0008)(ZeroConstructor, Transient, DuplicateTransient)
	class UWidgetAnimation*                       FadeAnimation;                                     // 0x0280(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, IsPlainOldData, RepSkip, NoDestructor, HasGetValueTypeHash)
	class UBrickImage*                            BrickImage_258;                                    // 0x0288(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UBrickImage*                            BrickImage_425;                                    // 0x0290(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UBrickBorder*                           RestrictedAreaBorder;                              // 0x0298(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UBrickTextBlock*                        RestrictedAreaTextBlock;                           // 0x02A0(0x0008)(BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)

public:
	void PlayFadeInAnim();
	void PlayFadeOutAnim();
	void UpdateTimerRemaining(float TimeRemaining);
	void ExecuteUbergraph_WBP_RestrictedArea(int32 EntryPoint);

public:
	static class UClass* StaticClass()
	{
		return StaticBPGeneratedClassImpl<"WBP_RestrictedArea_C">();
	}
	static class UWBP_RestrictedArea_C* GetDefaultObj()
	{
		return GetDefaultObjImpl<UWBP_RestrictedArea_C>();
	}
};
static_assert(alignof(UWBP_RestrictedArea_C) == 0x000008, "Wrong alignment on UWBP_RestrictedArea_C");
static_assert(sizeof(UWBP_RestrictedArea_C) == 0x0002A8, "Wrong size on UWBP_RestrictedArea_C");
static_assert(offsetof(UWBP_RestrictedArea_C, UberGraphFrame) == 0x000278, "Member 'UWBP_RestrictedArea_C::UberGraphFrame' has a wrong offset!");
static_assert(offsetof(UWBP_RestrictedArea_C, FadeAnimation) == 0x000280, "Member 'UWBP_RestrictedArea_C::FadeAnimation' has a wrong offset!");
static_assert(offsetof(UWBP_RestrictedArea_C, BrickImage_258) == 0x000288, "Member 'UWBP_RestrictedArea_C::BrickImage_258' has a wrong offset!");
static_assert(offsetof(UWBP_RestrictedArea_C, BrickImage_425) == 0x000290, "Member 'UWBP_RestrictedArea_C::BrickImage_425' has a wrong offset!");
static_assert(offsetof(UWBP_RestrictedArea_C, RestrictedAreaBorder) == 0x000298, "Member 'UWBP_RestrictedArea_C::RestrictedAreaBorder' has a wrong offset!");
static_assert(offsetof(UWBP_RestrictedArea_C, RestrictedAreaTextBlock) == 0x0002A0, "Member 'UWBP_RestrictedArea_C::RestrictedAreaTextBlock' has a wrong offset!");

}

