﻿#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: WBP_TeamScore

#include "Basic.hpp"

#include "WBP_TeamScore_classes.hpp"
#include "WBP_TeamScore_parameters.hpp"


namespace SDK
{

// Function WBP_TeamScore.WBP_TeamScore_C.UpdateScore
// (Event, Protected, BlueprintEvent)
// Parameters:
// int32                                   NewScore                                               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// int32                                   NewMaxScore                                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UWBP_TeamScore_C::UpdateScore(int32 NewScore, int32 NewMaxScore)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("WBP_TeamScore_C", "UpdateScore");

	Params::WBP_TeamScore_C_UpdateScore Parms{};

	Parms.NewScore = NewScore;
	Parms.NewMaxScore = NewMaxScore;

	UObject::ProcessEvent(Func, &Parms);
}


// Function WBP_TeamScore.WBP_TeamScore_C.UpdateTeamAttitude
// (Event, Protected, BlueprintEvent)
// Parameters:
// ETeamAttitude                           NewTeamAttitude                                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UWBP_TeamScore_C::UpdateTeamAttitude(ETeamAttitude NewTeamAttitude)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("WBP_TeamScore_C", "UpdateTeamAttitude");

	Params::WBP_TeamScore_C_UpdateTeamAttitude Parms{};

	Parms.NewTeamAttitude = NewTeamAttitude;

	UObject::ProcessEvent(Func, &Parms);
}


// Function WBP_TeamScore.WBP_TeamScore_C.UpdateTeamIcon
// (Event, Protected, BlueprintEvent)
// Parameters:
// class UTexture2D*                       NewIcon                                                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UWBP_TeamScore_C::UpdateTeamIcon(class UTexture2D* NewIcon)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("WBP_TeamScore_C", "UpdateTeamIcon");

	Params::WBP_TeamScore_C_UpdateTeamIcon Parms{};

	Parms.NewIcon = NewIcon;

	UObject::ProcessEvent(Func, &Parms);
}


// Function WBP_TeamScore.WBP_TeamScore_C.ExecuteUbergraph_WBP_TeamScore
// (Final, UbergraphFunction, HasDefaults)
// Parameters:
// int32                                   EntryPoint                                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UWBP_TeamScore_C::ExecuteUbergraph_WBP_TeamScore(int32 EntryPoint)
{
	static class UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = Class->GetFunction("WBP_TeamScore_C", "ExecuteUbergraph_WBP_TeamScore");

	Params::WBP_TeamScore_C_ExecuteUbergraph_WBP_TeamScore Parms{};

	Parms.EntryPoint = EntryPoint;

	UObject::ProcessEvent(Func, &Parms);
}

}

