//----------------------------------------------------------------------
// @filename Player.cpp
// @author: Fukuma Kyohei
// @explanation
// �v���C���[�N���X
// �v���C���[�̏����S�ʃN���X
//----------------------------------------------------------------------
#include "../../../Header/Character/Player/Player.h"
#include "appframe.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
Player::Player(ModeBase* game) :CharacterBase(game){
	m_Pos = { 0.0f,200.0f,0.0f };
	m_UseGravity = true;

	m_Collision = NEW Sphere();
	m_Collision->r = 100.0f;
	m_Sphere = NEW DrawSphereComponent(this);

	SphereColComponent* Col = NEW SphereColComponent(this);

	//�J����������
	m_Camera = NEW CameraComponent(this);
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
Player::~Player(){
	delete m_Collision;
	m_Collision = nullptr;
	delete m_Camera;
	m_Camera = nullptr;
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void Player::Process(){
	CharacterBase::Process();
////////////////////////////////////////////////////////////////////////
//�ړ�����
////////////////////////////////////////////////////////////////////////
	m_Sphere->SetSphere(m_Collision);
}

//----------------------------------------------------------------------
// @brief �`�揈��
// @return �Ȃ�
//----------------------------------------------------------------------
void Player::Render(){
	CharacterBase::Render();
}

//----------------------------------------------------------------------
// @brief �f�o�b�O�\��
// @return �Ȃ�
//----------------------------------------------------------------------
void Player::Debug(){
}
