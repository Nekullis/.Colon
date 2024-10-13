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
				//�����蔻��̎��
				enum class HITTYPE_3D :int{
					//�������l
					NONE = 0,
					//���Ƌ�
					SPHERE_TO_SPHERE,
					//����OBB
					SPHERE_TO_OBB,
					//OBB��OBB
					OBB_TO_OBB,
					//�J�v�Z���ƃJ�v�Z��
					CAPSULE_TO_CAPSULE
				}
				//�q�b�g�t���O������
				Hit = HITTYPE_3D::NONE;
				//2�̃I�u�W�F�N�g�̍ŒZ����������
				float dis = 0.0f;
				//	�����蔻��^�C�v��OBB�Ƌ��̏ꍇ
				if ((*itr)->GetType() == CollisionComponent::COLLISIONTYPE::OBB&& 
					(*jtr)->GetType() == CollisionComponent::COLLISIONTYPE::SPHERE) {
					Hit = HITTYPE_3D::SPHERE_TO_OBB;
				}
				switch (Hit)
				{
				case HITTYPE_3D::NONE:
					break;
				case HITTYPE_3D::SPHERE_TO_SPHERE:
					break;
				case HITTYPE_3D::SPHERE_TO_OBB:
					break;
				case HITTYPE_3D::OBB_TO_OBB:
					break;
				case HITTYPE_3D::CAPSULE_TO_CAPSULE:
					break;
				default:
					break;
				}
			}
		}
	}
}