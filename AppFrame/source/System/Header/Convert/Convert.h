//----------------------------------------------------------------------
// @filename Convert.h
// @author: Osaki Nagomi
// @explanation
// 変換を行う関数を定義するヘッダファイル
//----------------------------------------------------------------------
#pragma once

#include "DxLib.h"
#include "../Math/Vector3D.h"
#include <type_traits>

Vector3D ConvertPosToFullHD(const Vector3D& pos, float dispW, float dispH);

//----------------------------------------------------------------------
// @brief Enum型をint型に変換する
// @param e Enum型変数
// @return int型に変換された値
//----------------------------------------------------------------------
template<typename T>
int ConvertEnumToInt(T e)
{
	static_assert(std::is_enum<T>::value, "T must be an enum type");
	return static_cast<int>(e);
}

//----------------------------------------------------------------------
// @brief int型をEnum型に変換する
// @param i int型変数
// @return Enum型に変換された値
//----------------------------------------------------------------------
template<typename T>
T ConvertIntToEnum(int i)
{
	static_assert(std::is_enum<T>::value, "T must be an enum type");
	return static_cast<T>(i);
}