//----------------------------------------------------------------------
// @filename ModeGame.h
// @date: 2023/12/14
// @author: Fukuma Kyohei
// @explanation
// �{�X�o�g���ȊO�̃X�e�[�W���Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
#include "dxlib.h"

class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize()override;
	virtual bool Terminate()override;
	virtual bool Process()override;
	virtual bool Render()override;
	//�Q�b�^�[
	class CharacterManager* GetCharaManager() const { return m_CharaManager; }
protected:
	class CharacterManager* m_CharaManager;
	class GameCollision* m_GameCol;
};