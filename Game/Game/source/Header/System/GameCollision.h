//----------------------------------------------------------------------
// @filename CharacterBase.h
// @author: Fukuma Kyohei
// @explanation
// �Q�[�����̃I�u�W�F�N�g����Ǘ��N���X
// �����蔻��̐���S�ʂ������N���X
//----------------------------------------------------------------------
#pragma once
#include <vector>
class GameCollision
{
public:
	GameCollision();
	~GameCollision();
	void Process();
	//�R���W�����ǉ�
	void AddCollision(class CollisionComponent* col);
	//�Q�b�^�[
	std::vector<class CollisionComponent*> GetCollisionList() { return m_CollisionList; }
protected:
	//�Փ˔���p�R���|�[�l���g�R���e�i
	std::vector<class CollisionComponent*> m_CollisionList;
};

