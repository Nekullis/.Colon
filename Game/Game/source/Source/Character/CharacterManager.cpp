//----------------------------------------------------------------------
// @filename CharacterBase.h
// @author: Fukuma Kyohei
// @explanation
// �L�����N�^�[�I�u�W�F�N�g�̃}�l�[�W���[�N���X
// �v���C���[��G�Ȃǂ̃I�u�W�F�N�g�͂����Œǉ�����
//----------------------------------------------------------------------
#include "../../Header/Character/CharacterManager.h"
#include "../../Header/Character/CharacterBase.h"
#include "../../Header/System/GameCollision.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
CharacterManager::CharacterManager(){
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
CharacterManager::~CharacterManager(){
}

//----------------------------------------------------------------------
// @brief �L�����N�^�[�I�u�W�F�N�g���R���e�i�ɒǉ�
// @param chara �L�����N�^�[�I�u�W�F�N�g
// @return �Ȃ�
//----------------------------------------------------------------------
void CharacterManager::AddChara(CharacterBase* chara, GameCollision* col){
	//�`��R���|�[�l���g���}�l�[�W���[���̃R���e�i�Ɉړ�
	for (auto&& component : chara->GetComponent()){
		if (component->GetUpdateOwder() > DRAW_OWDER) {
			m_Draw.push_back(std::move(component));
		}
	}
	if (col) {
		col->AddCollision(chara);
	}
	//�R���e�i�Ɋi�[
	m_CharaList.emplace_back(chara);
}

//----------------------------------------------------------------------
// @brief �w��L�����N�^�[�I�u�W�F�N�g�̍폜
// @param chara �L�����N�^�[�I�u�W�F�N�g
// @return �Ȃ�
//----------------------------------------------------------------------
void CharacterManager::DeleteChara(CharacterBase* chara){
	//�����̍����I�u�W�F�N�g���R���e�i�����猟��
	auto itr = std::find(m_CharaList.begin(), m_CharaList.end(), chara);
	//�������I�u�W�F�N�g�̍폜
	if (itr != m_CharaList.end()) { m_CharaList.erase(itr); }
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void CharacterManager::UpDate(){
	//�R���e�i�ɓ����Ă���̃I�u�W�F�N�g�̍X�V����
	for (auto&& Chara : m_CharaList){
		Chara->Process();
	}
}

//----------------------------------------------------------------------
// @brief �`�揈��
// @return �Ȃ�
//----------------------------------------------------------------------
void CharacterManager::Render(){
	//�R���e�i�ɓ����Ă���̃I�u�W�F�N�g�̍X�V����
	for (auto&& Draw : m_Draw) {
		Draw->Update();
	}
}
