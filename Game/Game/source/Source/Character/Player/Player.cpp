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
	m_Pos = { 0.0f,400.0f,0.0f };
	m_UseGravity = true;

	//���̂̏�񏉊���
	m_Sphere = NEW Sphere();
	m_Sphere->r = 100.0f;
	m_Sphere->pos = m_Pos;

	//�`��p�R���|�[�l���g������
	m_Draw = NEW DrawSphereComponent(this);

	//���̗p�����蔻��R���|�[�l���g�ǉ�
	m_Col = NEW SphereColComponent(this);

	//�J����������
	m_Camera = NEW CameraComponent(this);
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
Player::~Player(){
	delete m_Sphere;
	m_Sphere = nullptr;
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
	m_Draw->SetSphere(m_Sphere);
	m_Col->SetCollision(m_Sphere);
}

//----------------------------------------------------------------------
// @brief �`�揈��
// @return �Ȃ�
//----------------------------------------------------------------------
void Player::Render(){
	CharacterBase::Render();
	if (m_Sphere->isHit) {
		m_UseGravity = false;
	}
	else {
		m_UseGravity = true;
	}
}

//----------------------------------------------------------------------
// @brief �f�o�b�O�\��
// @return �Ȃ�
//----------------------------------------------------------------------
void Player::Debug(){
}
