//----------------------------------------------------------------------
// @filename Convert.h
// @author: Osaki Nagomi
// @explanation
// �ϊ����s���֐����`����w�b�_�t�@�C��
//----------------------------------------------------------------------
#pragma once

#include "DxLib.h"
#include "../Math/Vector3D.h"
#include <type_traits>

Vector3D ConvertPosToFullHD(const Vector3D& pos, float dispW, float dispH);

//----------------------------------------------------------------------
// @brief Enum�^��int�^�ɕϊ�����
// @param e Enum�^�ϐ�
// @return int�^�ɕϊ����ꂽ�l
//----------------------------------------------------------------------
template<typename T>
int ConvertEnumToInt(T e)
{
	static_assert(std::is_enum<T>::value, "T must be an enum type");
	return static_cast<int>(e);
}

//----------------------------------------------------------------------
// @brief int�^��Enum�^�ɕϊ�����
// @param i int�^�ϐ�
// @return Enum�^�ɕϊ����ꂽ�l
//----------------------------------------------------------------------
template<typename T>
T ConvertIntToEnum(int i)
{
	static_assert(std::is_enum<T>::value, "T must be an enum type");
	return static_cast<T>(i);
}