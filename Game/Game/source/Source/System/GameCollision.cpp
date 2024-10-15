//----------------------------------------------------------------------
// @filename CharacterBase.h
// @author: Fukuma Kyohei
// @explanation
// �Q�[�����̃I�u�W�F�N�g����Ǘ��N���X
// �����蔻��̐���S�ʂ������N���X
//----------------------------------------------------------------------
#include "../Game/Game/source/Header/System/GameCollision.h"
#include"../Game/Game/source/Header/Character/CharacterBase.h"
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
// @brief �����蔻��R���|�[�l���g�ǉ�
// @param chara �I�u�W�F�N�g
// @return �Ȃ�
//----------------------------------------------------------------------
void GameCollision::AddCollision(CharacterBase* chara){
	//�R���|�[�l���g�S����
	for (auto&& component : chara->GetComponent()) {
		//�����蔻��p�̃R���|�[�l���g������ʃR���e�i��
		if (component->GetUpdateOwder() == COL_OWDER) {
			CollisionComponent* col = static_cast<CollisionComponent*>(component);
			m_CollisionList.push_back(col);
		}
	}
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
					//�e�I�u�W�F�N�g�̓����蔻����擾
					OBB* Obb = static_cast<OBB*>((*itr)->GetCollision());
					Sphere* Sph = static_cast<Sphere*>((*jtr)->GetCollision());
					//�ŋߓ_�p�̕ϐ�������
					Vector3D* Dist = NEW Vector3D(0.0f, 0.0f, 0.0f);
					//�I�u�W�F�N�g���m���������Ă����ꍇ
					if (Collision3D::OBBSphereCol(*Obb, *Sph, Dist)) {
						//�I�u�W�F�N�g�Ԃ̋��������߂�
						Vector3D Sub = (*jtr)->GetPos() - (*itr)->GetPos();
						//���K�����ċt�x�N�g����
						Sub = Sub.Normalize() * -1;
						//�I�u�W�F�N�g�̈ʒu�ɔ��f
						(*jtr)->SetPos(Sub);
					}
				}
			}
		}
	}
}