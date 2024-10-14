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
//----------------------------------------------------------------------
// @brief ����������
// @return ����
//----------------------------------------------------------------------
bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	// �}�l�[�W���[�̎擾
	m_CharaManager = NEW CharacterManager();
	m_CharaManager->AddChara(NEW GameStage(this));
	m_CharaManager->AddChara(NEW Player(this));
	return true;
}
//----------------------------------------------------------------------
// @brief �I������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ModeGame::Process() {
	base::Process();
	m_CharaManager->UpDate();
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
