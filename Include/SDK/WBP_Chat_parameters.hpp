﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: WBP_Chat

#include "Basic.hpp"

#include "UMG_structs.hpp"


namespace SDK::Params
{

// Function WBP_Chat.WBP_Chat_C.UpdateIsFocused
// 0x0001 (0x0001 - 0x0000)
struct WBP_Chat_C_UpdateIsFocused final
{
public:
	bool                                          bNewFocused;                                       // 0x0000(0x0001)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor)
};
static_assert(alignof(WBP_Chat_C_UpdateIsFocused) == 0x000001, "Wrong alignment on WBP_Chat_C_UpdateIsFocused");
static_assert(sizeof(WBP_Chat_C_UpdateIsFocused) == 0x000001, "Wrong size on WBP_Chat_C_UpdateIsFocused");
static_assert(offsetof(WBP_Chat_C_UpdateIsFocused, bNewFocused) == 0x000000, "Member 'WBP_Chat_C_UpdateIsFocused::bNewFocused' has a wrong offset!");

// Function WBP_Chat.WBP_Chat_C.UpdateIsTyping
// 0x0001 (0x0001 - 0x0000)
struct WBP_Chat_C_UpdateIsTyping final
{
public:
	bool                                          bNewTyping;                                        // 0x0000(0x0001)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor)
};
static_assert(alignof(WBP_Chat_C_UpdateIsTyping) == 0x000001, "Wrong alignment on WBP_Chat_C_UpdateIsTyping");
static_assert(sizeof(WBP_Chat_C_UpdateIsTyping) == 0x000001, "Wrong size on WBP_Chat_C_UpdateIsTyping");
static_assert(offsetof(WBP_Chat_C_UpdateIsTyping, bNewTyping) == 0x000000, "Member 'WBP_Chat_C_UpdateIsTyping::bNewTyping' has a wrong offset!");

// Function WBP_Chat.WBP_Chat_C.ExecuteUbergraph_WBP_Chat
// 0x000C (0x000C - 0x0000)
struct WBP_Chat_C_ExecuteUbergraph_WBP_Chat final
{
public:
	int32                                         EntryPoint;                                        // 0x0000(0x0004)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_Event_bNewTyping;                           // 0x0004(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	bool                                          Temp_bool_Variable;                                // 0x0005(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
	ESlateVisibility                              Temp_byte_Variable;                                // 0x0006(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	ESlateVisibility                              Temp_byte_Variable_1;                              // 0x0007(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	ESlateVisibility                              K2Node_Select_Default;                             // 0x0008(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                          K2Node_Event_bNewFocused;                          // 0x0009(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor)
};
static_assert(alignof(WBP_Chat_C_ExecuteUbergraph_WBP_Chat) == 0x000004, "Wrong alignment on WBP_Chat_C_ExecuteUbergraph_WBP_Chat");
static_assert(sizeof(WBP_Chat_C_ExecuteUbergraph_WBP_Chat) == 0x00000C, "Wrong size on WBP_Chat_C_ExecuteUbergraph_WBP_Chat");
static_assert(offsetof(WBP_Chat_C_ExecuteUbergraph_WBP_Chat, EntryPoint) == 0x000000, "Member 'WBP_Chat_C_ExecuteUbergraph_WBP_Chat::EntryPoint' has a wrong offset!");
static_assert(offsetof(WBP_Chat_C_ExecuteUbergraph_WBP_Chat, K2Node_Event_bNewTyping) == 0x000004, "Member 'WBP_Chat_C_ExecuteUbergraph_WBP_Chat::K2Node_Event_bNewTyping' has a wrong offset!");
static_assert(offsetof(WBP_Chat_C_ExecuteUbergraph_WBP_Chat, Temp_bool_Variable) == 0x000005, "Member 'WBP_Chat_C_ExecuteUbergraph_WBP_Chat::Temp_bool_Variable' has a wrong offset!");
static_assert(offsetof(WBP_Chat_C_ExecuteUbergraph_WBP_Chat, Temp_byte_Variable) == 0x000006, "Member 'WBP_Chat_C_ExecuteUbergraph_WBP_Chat::Temp_byte_Variable' has a wrong offset!");
static_assert(offsetof(WBP_Chat_C_ExecuteUbergraph_WBP_Chat, Temp_byte_Variable_1) == 0x000007, "Member 'WBP_Chat_C_ExecuteUbergraph_WBP_Chat::Temp_byte_Variable_1' has a wrong offset!");
static_assert(offsetof(WBP_Chat_C_ExecuteUbergraph_WBP_Chat, K2Node_Select_Default) == 0x000008, "Member 'WBP_Chat_C_ExecuteUbergraph_WBP_Chat::K2Node_Select_Default' has a wrong offset!");
static_assert(offsetof(WBP_Chat_C_ExecuteUbergraph_WBP_Chat, K2Node_Event_bNewFocused) == 0x000009, "Member 'WBP_Chat_C_ExecuteUbergraph_WBP_Chat::K2Node_Event_bNewFocused' has a wrong offset!");

}

