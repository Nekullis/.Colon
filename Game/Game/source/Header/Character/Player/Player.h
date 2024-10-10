//----------------------------------------------------------------------
// @filename Player.cpp
// @author: Fukuma Kyohei
// @explanation
// �v���C���[�N���X
// �v���C���[�̏����S�ʃN���X
//----------------------------------------------------------------------
#pragma once
#include "../CharacterBase.h"
class Player : public CharacterBase
{
public:
	Player(class ModeBase* game);
	virtual ~Player();
	void Process()	override;
	void Render()	override;
	void Debug()	override;
protected:
};