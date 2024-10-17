//----------------------------------------------------------------------
// @filename ModeGame.cpp
// @author: saito ko
// @explanation
// �Q�[���{�҂��Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Character/CharacterManager.h"
#include "../../Header/Character/GameStage/GameStage.h"
#include "../../Header/Character/Player/Player.h"
#include "../../Header/System/GameCollision.h"
//----------------------------------------------------------------------
// @brief ����������
// @return ����
//----------------------------------------------------------------------
bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	m_GameCol = NEW GameCollision();
	// �}�l�[�W���[�̎擾
	m_CharaManager = NEW CharacterManager();
	m_CharaManager->AddChara(NEW GameStage(this),m_GameCol);
	m_CharaManager->AddChara(NEW Player(this),m_GameCol);
	return true;
}
//----------------------------------------------------------------------
// @brief �I������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeGame::Terminate() {
	base::Terminate();
	delete m_CharaManager;
	m_CharaManager = nullptr;
	delete m_GameCol;
	m_GameCol = nullptr;
	return true;
}
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ModeGame::Process() {
	base::Process();
	m_CharaManager->UpDate();
	m_GameCol->Process();
	return true;
}
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ModeGame::Render() {
	base::Render();
	m_CharaManager->Render();
	return true;
}
