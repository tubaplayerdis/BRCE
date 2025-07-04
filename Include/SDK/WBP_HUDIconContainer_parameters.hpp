﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: WBP_HUDIconContainer

#include "Basic.hpp"


namespace SDK::Params
{

// Function WBP_HUDIconContainer.WBP_HUDIconContainer_C.AddInteractionWidget
// 0x0008 (0x0008 - 0x0000)
struct WBP_HUDIconContainer_C_AddInteractionWidget final
{
public:
	class UInteractionWidget*                     Widget;                                            // 0x0000(0x0008)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};
static_assert(alignof(WBP_HUDIconContainer_C_AddInteractionWidget) == 0x000008, "Wrong alignment on WBP_HUDIconContainer_C_AddInteractionWidget");
static_assert(sizeof(WBP_HUDIconContainer_C_AddInteractionWidget) == 0x000008, "Wrong size on WBP_HUDIconContainer_C_AddInteractionWidget");
static_assert(offsetof(WBP_HUDIconContainer_C_AddInteractionWidget, Widget) == 0x000000, "Member 'WBP_HUDIconContainer_C_AddInteractionWidget::Widget' has a wrong offset!");

// Function WBP_HUDIconContainer.WBP_HUDIconContainer_C.AddCrosshairWidgets
// 0x0010 (0x0010 - 0x0000)
struct WBP_HUDIconContainer_C_AddCrosshairWidgets final
{
public:
	TArray<class UMapCrosshairWidget*>            Widgets;                                           // 0x0000(0x0010)(ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, ContainsInstancedReference)
};
static_assert(alignof(WBP_HUDIconContainer_C_AddCrosshairWidgets) == 0x000008, "Wrong alignment on WBP_HUDIconContainer_C_AddCrosshairWidgets");
static_assert(sizeof(WBP_HUDIconContainer_C_AddCrosshairWidgets) == 0x000010, "Wrong size on WBP_HUDIconContainer_C_AddCrosshairWidgets");
static_assert(offsetof(WBP_HUDIconContainer_C_AddCrosshairWidgets, Widgets) == 0x000000, "Member 'WBP_HUDIconContainer_C_AddCrosshairWidgets::Widgets' has a wrong offset!");

// Function WBP_HUDIconContainer.WBP_HUDIconContainer_C.ExecuteUbergraph_WBP_HUDIconContainer
// 0x0050 (0x0050 - 0x0000)
struct WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer final
{
public:
	int32                                         EntryPoint;                                        // 0x0000(0x0004)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         CallFunc_MakeLiteralByte_ReturnValue;              // 0x0004(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_5[0x3];                                        // 0x0005(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	class UInteractionWidget*                     K2Node_Event_Widget;                               // 0x0008(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	TArray<class UMapCrosshairWidget*>            K2Node_Event_Widgets;                              // 0x0010(0x0010)(ConstParm, ReferenceParm, ContainsInstancedReference)
	class UGridSlot*                              CallFunc_AddChildToGrid_ReturnValue;               // 0x0020(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UMapCrosshairWidget*                    CallFunc_Array_Get_Item;                           // 0x0028(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UGridSlot*                              CallFunc_AddChildToGrid_ReturnValue_1;             // 0x0030(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UMapCrosshairWidget*                    CallFunc_Array_Get_Item_1;                         // 0x0038(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         CallFunc_MakeLiteralByte_ReturnValue_1;            // 0x0040(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                         Pad_41[0x7];                                       // 0x0041(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class UGridSlot*                              CallFunc_AddChildToGrid_ReturnValue_2;             // 0x0048(0x0008)(ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};
static_assert(alignof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer) == 0x000008, "Wrong alignment on WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer");
static_assert(sizeof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer) == 0x000050, "Wrong size on WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer");
static_assert(offsetof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer, EntryPoint) == 0x000000, "Member 'WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer::EntryPoint' has a wrong offset!");
static_assert(offsetof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer, CallFunc_MakeLiteralByte_ReturnValue) == 0x000004, "Member 'WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer::CallFunc_MakeLiteralByte_ReturnValue' has a wrong offset!");
static_assert(offsetof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer, K2Node_Event_Widget) == 0x000008, "Member 'WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer::K2Node_Event_Widget' has a wrong offset!");
static_assert(offsetof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer, K2Node_Event_Widgets) == 0x000010, "Member 'WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer::K2Node_Event_Widgets' has a wrong offset!");
static_assert(offsetof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer, CallFunc_AddChildToGrid_ReturnValue) == 0x000020, "Member 'WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer::CallFunc_AddChildToGrid_ReturnValue' has a wrong offset!");
static_assert(offsetof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer, CallFunc_Array_Get_Item) == 0x000028, "Member 'WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer::CallFunc_Array_Get_Item' has a wrong offset!");
static_assert(offsetof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer, CallFunc_AddChildToGrid_ReturnValue_1) == 0x000030, "Member 'WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer::CallFunc_AddChildToGrid_ReturnValue_1' has a wrong offset!");
static_assert(offsetof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer, CallFunc_Array_Get_Item_1) == 0x000038, "Member 'WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer::CallFunc_Array_Get_Item_1' has a wrong offset!");
static_assert(offsetof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer, CallFunc_MakeLiteralByte_ReturnValue_1) == 0x000040, "Member 'WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer::CallFunc_MakeLiteralByte_ReturnValue_1' has a wrong offset!");
static_assert(offsetof(WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer, CallFunc_AddChildToGrid_ReturnValue_2) == 0x000048, "Member 'WBP_HUDIconContainer_C_ExecuteUbergraph_WBP_HUDIconContainer::CallFunc_AddChildToGrid_ReturnValue_2' has a wrong offset!");

}

