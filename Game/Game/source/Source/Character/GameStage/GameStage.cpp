//----------------------------------------------------------------------
// @filename GameStage.cpp
// @author: Fukuma Kyohei
// @explanation
// �Q�[���X�e�[�W�N���X
// �X�e�[�W�̏����S�ʃN���X
//----------------------------------------------------------------------
#include "../Game/Game/source/Header/Character/GameStage/GameStage.h"
#include "appframe.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
GameStage::GameStage(ModeBase* game):CharacterBase(game){
	//�ʒu������
	m_Pos = Vector3D(500.0f, 0.0f, 100.0f);
	//�X�P�[���ݒ�
	m_Scale = Vector3D(1000.0f, 10.0f, 1000.0f);

	//���͗p�R���|�[�l���g������
	m_Input = NEW InputComponent(this);

	////�`��p�R���|�[�l���g������
	//DrawMV1Component* Model = NEW DrawMV1Component(this);
	////�`��p���f���ǂݍ���
	//Model->LoadPass("");

	//�R���W�����pOBB������
	m_Collision = NEW OBB("stage", m_Pos, m_Scale);
	m_OBB = NEW DrawOBBComponent(this);

	//�J����������
	m_Camera = NEW CameraComponent(this);
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
GameStage::~GameStage(){
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void GameStage::Process(){
	CharacterBase::Process();
	//��]�n�̊��l��ݒ�
	float Control_Value = Math::DegToRad(30.0f);
	//�x�N�g���̑����ʂ�ݒ�
	float Vec_Dir = Math::DegToRad(1.0f);

	if (m_Input->GetPad()->IsInputStickLeft()){
		//�p�b�h�̃A�i���O�X�e�B�b�N��x���l�𔽉f
		if (m_Input->GetPad()->GetLx() > 0) { m_Rotation.z -= Vec_Dir; }
		else if (m_Input->GetPad()->GetLx() < 0) { m_Rotation.z += Vec_Dir; }
		//�K��l�𒴂��Ȃ��悤�ɐݒ�
		m_Rotation.z = std::clamp(m_Rotation.z, -Control_Value, Control_Value);

		//�p�b�h�̃A�i���O�X�e�B�b�N��y���l�𔽉f
		if (m_Input->GetPad()->GetLy() > 0) { m_Rotation.x += Vec_Dir; }
		else if (m_Input->GetPad()->GetLy() < 0) { m_Rotation.x -= Vec_Dir; }
		//�K��l�𒴂��Ȃ��悤�ɐݒ�
		m_Rotation.x = std::clamp(m_Rotation.x, -Control_Value, Control_Value);
	}

	//OBB����]������
	m_Collision->Rotate(m_Rotation);
	m_OBB->SetOBB(m_Collision);
}