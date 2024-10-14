//----------------------------------------------------------------------
// @filename CharacterManager.h
// @author: Fukuma Kyohei
// @explanation
// �L�����N�^�[�I�u�W�F�N�g�̃}�l�[�W���[�N���X
// �v���C���[��G�Ȃǂ̃I�u�W�F�N�g�͂����Œǉ�����
//----------------------------------------------------------------------
#pragma once
#include <vector>
#include "appframe.h"
//�萔
auto constexpr DRAW_OWDER = 200;
class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager();
	void UpDate();
	void Render();
	//�L�����N�^�[�ǉ�
	void AddChara(class CharacterBase* chara, class GameCollision* col = nullptr);
	//�L�����N�^�[�폜
	void DeleteChara(class CharacterBase* chara);
	//�Q�b�^�[
	std::vector<class CharacterBase*>	GetCharaList()	const { return m_CharaList; }
protected:
	//�L�����N�^�[�I�u�W�F�N�g�R���e�i
	std::vector<class CharacterBase*> m_CharaList;
	//�`��R���|�[�l���g�R���e�i
	std::vector<Component*> m_Draw;
};

