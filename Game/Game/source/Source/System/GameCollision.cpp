//----------------------------------------------------------------------
// @filename GameCollision.cpp
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
		for (auto itr_i = m_CollisionList.begin(); itr_i != m_CollisionList.end(); itr_i++) {
			for (auto itr_j = itr_i + 1; itr_j != m_CollisionList.end(); itr_j++) {
				//�������̂Ȃ�Č���
				if (itr_i == itr_j)continue; 

				//	�����蔻��^�C�v��OBB�Ƌ��̏ꍇ
				if ((*itr_i)->GetType() == CollisionComponent::COLLISIONTYPE::OBB&& 
					(*itr_j)->GetType() == CollisionComponent::COLLISIONTYPE::SPHERE) {
					//�e�I�u�W�F�N�g�̓����蔻����擾
					OBB* Obb = dynamic_cast<OBB*>((*itr_i)->GetCollision());
					Sphere* Sph = dynamic_cast<Sphere*>((*itr_j)->GetCollision());

					//�ŋߓ_�p�̕ϐ�������
					Vector3D HitPos =  Vector3D(0.0f, 0.0f, 0.0f);

					//�I�u�W�F�N�g���m���������Ă����ꍇ
					if (Collision3D::OBBSphereCol(*Obb, *Sph, &HitPos)) {
						(*itr_j)->GetCollision()->isHit = true;

						//OBB�̖ʂɉ����������x�N�g�����擾
						Vector3D Vec = Obb->dir_vec[0] + Obb->dir_vec[2];
						//���K��
						Vec = Vec.Normalize();
						//OBB�̖ʂɉ����������x�N�g���̊O�ς����߂�
						Vector3D VecCloss = Vec.Cross(Obb->dir_vec[2]);
						//�@���x�N�g�������߂�
						Vector3D NormalVec = VecCloss.Normalize();

						//�d�̓x�N�g����ݒ�
						Vector3D GravityVec = Vector3D(0.0f, -9.8f, 0.0f);
						//�@���x�N�g���ɏd�̓x�N�g���̓��ς��������킹��
						Vector3D MultiVec = NormalVec * (GravityVec.Normalize().Dot(NormalVec));
						//�d�̓x�N�g���Ƃ������킹���d�̓x�N�g���̍������߂�
						Vector3D SubVec = GravityVec - MultiVec;

						//���̖��ߍ��񂾕��̉����o������
						//�Őڋߓ_�Ƌ��̈ʒu�̍��̃x�N�g���̒��������߂�
						float PushLen = (HitPos - (*itr_j)->GetOwner()->GetPos()).Len();
						//���̔��a�ƃx�N�g���̒����̍������߂�
						float SubLen = Sph->r - PushLen;

						//�ŏI�I�ȉ����o���x�N�g�������߂�
						//OBB��y���̃x�N�g����SubLen���|�����킹�ASubVec�����Z����
						Vector3D Velocity = Obb->dir_vec[1] * SubLen + SubVec;

						//�I�u�W�F�N�g�̈ʒu�ɔ��f
						(*itr_j)->GetOwner()->SetPos((*itr_j)->GetOwner()->GetPos() + Velocity);
						
					}
					//�������Ă��Ȃ�
					else {
						(*itr_j)->GetCollision()->isHit = false;
					}
				}
			}
		}
	}
}