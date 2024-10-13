//----------------------------------------------------------------------
// @filename CharacterBase.h
// @author: Fukuma Kyohei
// @explanation
// �Q�[�����̃I�u�W�F�N�g����Ǘ��N���X
// �����蔻��̐���S�ʂ������N���X
//----------------------------------------------------------------------
#include "../Game/Game/source/Header/System/GameCollision.h"
#include "appframe.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
GameCollision::GameCollision(){
	//�R���e�i������
	m_CollisionList.clear();
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
GameCollision::~GameCollision(){
	m_CollisionList.clear();
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @param col �Փ˔���p�R���|�[�l���g
// @return �Ȃ�
//----------------------------------------------------------------------
void GameCollision::AddCollision(CollisionComponent* col){
	m_CollisionList.push_back(col);
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void GameCollision::Process(){
	//�R���e�i�T�C�Y��0�łȂ��̂Ȃ�
	if (m_CollisionList.size() > 0) {
		//2�dif���őS����
		for (auto itr = m_CollisionList.begin(); itr != m_CollisionList.end(); itr++) {
			for (auto jtr = itr + 1; jtr != m_CollisionList.end(); jtr++) {
				//�������̂Ȃ�Č���
				if (itr == jtr)continue; 
				//	�����蔻��^�C�v��OBB�Ƌ��̏ꍇ
				if ((*itr)->GetType() == CollisionComponent::COLLISIONTYPE::OBB&& 
					(*jtr)->GetType() == CollisionComponent::COLLISIONTYPE::SPHERE) {
					OBB* Obb = static_cast<OBB*>((*itr)->GetCollision());
					Sphere* Sph = static_cast<Sphere*>((*jtr)->GetCollision());
					if (Collision3D::OBBSphereCol(*Obb, *Sph)) {
						int i = 0;
					}
				}
			}
		}
	}
}