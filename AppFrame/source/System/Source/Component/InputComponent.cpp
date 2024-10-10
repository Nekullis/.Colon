//----------------------------------------------------------------------
// @filename InputComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// ���͏����l�����L�����N�^�[�̉�]�E���W�𐧌䂷��R���|�[�l���g
//----------------------------------------------------------------------
#include "../../Header/Component/InputComponent.h"
#include "../../Header/Component/CameraComponent.h"
#include "../../Header/Math/Matrix3D.h"
#include "../../Header/Math/MyMath.h"
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
InputComponent::InputComponent(ObjectBase* owner, int updateowder) :MoveComponent(owner, updateowder)
{
	//�R���g���[���[������
	m_Pad = new XInput();
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
InputComponent::~InputComponent()
{
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void InputComponent::Update()
{
	m_Pad->Input();
	
}
