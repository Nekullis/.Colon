//----------------------------------------------------------------------
// @filename Convert.h
// @author: Osaki Nagomi
// @explanation
// •ÏŠ·‚ğs‚¤ŠÖ”‚ğ’è‹`‚·‚éƒwƒbƒ_ƒtƒ@ƒCƒ‹
//----------------------------------------------------------------------
#pragma once

#include "DxLib.h"
#include "../Math/Vector3D.h"
#include <type_traits>

Vector3D ConvertPosToFullHD(const Vector3D& pos, float dispW, float dispH);

//----------------------------------------------------------------------
// @brief EnumŒ^‚ğintŒ^‚É•ÏŠ·‚·‚é
// @param e EnumŒ^•Ï”
// @return intŒ^‚É•ÏŠ·‚³‚ê‚½’l
//----------------------------------------------------------------------
template<typename T>
int ConvertEnumToInt(T e)
{
	static_assert(std::is_enum<T>::value, "T must be an enum type");
	return static_cast<int>(e);
}

//----------------------------------------------------------------------
// @brief intŒ^‚ğEnumŒ^‚É•ÏŠ·‚·‚é
// @param i intŒ^•Ï”
// @return EnumŒ^‚É•ÏŠ·‚³‚ê‚½’l
//----------------------------------------------------------------------
template<typename T>
T ConvertIntToEnum(int i)
{
	static_assert(std::is_enum<T>::value, "T must be an enum type");
	return static_cast<T>(i);
}