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
	////�A�i���O�p�b�h�̒l��atan2�֐��Ŋp�x�𓾂�
	//float dir = atan2f(static_cast<float>(mPad->GetLy() * -1),static_cast<float>(mPad->GetLx() * -1));
	//float com_dir_y = CameraComponent::GetInstance()->GetDir().y;
	////�A�i���O�p�b�h�������Ă���̂Ȃ�
	//if(mPad->IsInputStickLeft())
	//{
	//	//�Q�ƃI�u�W�F�N�g�̈ʒu���擾
	//	Vector3D pos = m_Owner->GetPos();
	//	//�Z�b�^�[�œ������x����
	//	float speed = mForwardSpeed;
	//	//y���̉�]�s��𓾂�
	//	Matrix3D matrix = Matrix3D::MGetRotY(com_dir_y);
	//	//�ړ��ʂ𓾂�
	//	Vector3D move{ speed * cosf(dir) ,0,speed * sinf(dir) };
	//	//�ړ��ʂƃJ�����̉�]�l�̐ς����߁A�J�����̌����ƑO���x�N�g������v������
	//	move = move * matrix;
	//	//�ʒu�ɔ��f
	//	pos += move;
	//	//�Z�b�^�[�Ńv���C���[�̈ʒu���ɑ��
	//	m_Owner->SetPos(pos);
	//	//�ړ���̉�]�l�����߂�
	//	Vector3D rot = Vector3D(0, -(dir + Math::DegToRad(90.0f))+ com_dir_y, 0);
	//	//�v���C���[�̉�]�l�ɔ��f
	//	m_Owner->SetRotation(rot);
	//}
	//
}
