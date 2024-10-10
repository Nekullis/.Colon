//----------------------------------------------------------------------
// @filename Afterglow.h
// @author: Osaki Nagomi
// @explanation
// �I�����ڂ̏���������֐��̃v���g�^�C�v�錾������w�b�_�t�@�C��
//----------------------------------------------------------------------
#include "DxLib.h"
#include "../../Header/EventSystem/EventSystem.h"

//----------------------------------------------------------------------
// @brief �I������
// @param input	����
// @param axis	��
// @param size	�I�����̐�
// @param select	���݂̑I����
// @return �I�𒆂̗v�f
//----------------------------------------------------------------------
int SelectFocus(int input,const std::string& axis, int size, int select)
{
	// ���͂ɉ����đI������ύX
	if (axis == "x") 
	{
		if(input & PAD_INPUT_LEFT)	return (select + size - 1) % size;
		if(input & PAD_INPUT_RIGHT) return (select + 1) % size;
	}
	if (axis == "y") 
	{
		if(input & PAD_INPUT_UP)	return (select + size - 1) % size;
		if(input & PAD_INPUT_DOWN) return (select + 1) % size;
	}

	// ���͂��Ȃ��ꍇ�͂��̂܂܂̒l��Ԃ�
	return select;
}
