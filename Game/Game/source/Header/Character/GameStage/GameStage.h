//----------------------------------------------------------------------
// @filename GameStage.cpp
// @author: Fukuma Kyohei
// @explanation
// �Q�[���X�e�[�W�N���X
// �X�e�[�W�̏����S�ʃN���X
//----------------------------------------------------------------------
#pragma once
#include "../CharacterBase.h"
class GameStage :public CharacterBase
{
public:
	GameStage(class ModeBase* game);
	virtual ~GameStage();
	void Process()	override;
protected:
	//���͏����R���|�[�l���g
	class InputComponent* m_Input;
	class OBB* m_Collision;
	class DrawOBBComponent* m_OBB;
	class CameraComponent* m_Camera;
};

