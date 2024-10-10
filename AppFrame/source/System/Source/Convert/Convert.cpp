//----------------------------------------------------------------------
// @filename Convert.cpp
// @author: Osaki Nagomi
// @explanation
// �ϊ����s���֐����`����\�[�X�t�@�C��
//----------------------------------------------------------------------
#include "DxLib.h"
#include "../../Header/Convert/Convert.h"

//----------------------------------------------------------------------
// @brief ��ʍ��W���t��HD���W�ɕϊ�����
// @param pos	��ʍ��W
// @param dispW	��ʂ̉���
// @param dispH	��ʂ̏c��
// @return �t��HD���W�ɕϊ��������W
//----------------------------------------------------------------------
Vector3D ConvertPosToFullHD(const Vector3D& pos, float dispW, float dispH)
{
	float x = dispW * pos.x / 1920;
	float y = dispH * pos.y / 1080;
	float z = 0;
	return VGet(x, y, z);
}
