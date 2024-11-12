//----------------------------------------------------------------------
// @filename ModeDebug.h
// @date: 2024/9/11
// @author: Fukuma Kyohei
// @explanation
// �{�X�o�g���ȊO�̃X�e�[�W���Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
class ModeDebug : public ModeBase
{
	typedef ModeBase base;
public:
	bool Initialize()override;
	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};
