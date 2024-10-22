//----------------------------------------------------------------------
// @filename CameraComponent.cpp
// @author: Fukuma Kyohei
// @explanation
// �Q�[�����̃J���������S�ʐ��䂷��R���|�[�l���g
//----------------------------------------------------------------------
#include "../../Header/Component/CameraComponent.h"
#include "../../Header/Component/Object/ObjectBase.h"
#include "../../Header/Collision/3DCollision.h"

CameraComponent* CameraComponent::m_CameraInstance = nullptr;

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
CameraComponent::CameraComponent(ObjectBase* owner, int updateowder) : LogicComponent(owner, updateowder)
{
	m_CameraInstance = this;
	//�����_������
	m_Target = { 0 };
	//�ʒu������
	m_Pos = { 0 };
	m_Dir = Vector3D(0, m_Owner->GetRotation().y, 0);
	//�ŒZ�`�拗��������
	m_Near = 20.0f;
	//�Œ��`�拗��������
	m_Far = 50000.0f;
	//�����l������
	m_Distance = -700.0f;
	//�΂˒萔
	m_Spring = 0.1f;
	//�����萔
	m_DampFactor = 0.8f;
	m_CurrentPos = m_Pos;
	m_CurrentVelocity;
	//�Q�[���p�b�h�̎擾
	m_Pad = XInput::GetInstance();
	m_Owner->AddComponent(this);
}
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
CameraComponent::~CameraComponent()
{
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void CameraComponent::Update()
{
	Component::Update();
	//�ʒu�ݒ�
	Vector3D pos;
	//�p�b�h���͂Ŋp�x����
	if (m_Pad->GetRx() < 0) { m_Dir.y -= 0.05f; }
	if (m_Pad->GetRx() > 0) { m_Dir.y += 0.05f; }
	//�����_�ݒ�
	Vector3D target;
	//�J�����ʒu���v���[���[�ʒu�ɋ��^���W�n����ω��������W�n�𑫂������W�ɂ���
	pos = m_Owner->GetPos() + Collision3D::ConvertToCartesian(m_Dir, m_Distance);
	//�㓪����菭�����߂̈ʒu�ɂ���
	pos.y += 100.0f;
	target = Vector3D(m_Owner->GetPos()); 
	m_Pos = pos;
	//�΂˗͌v�Z
	Vector3D springforce = -m_Spring * (m_CurrentPos - pos);
	//�����͌v�Z
	Vector3D dampforce = -m_DampFactor * m_CurrentVelocity;
	//�����͂��v�Z���Ă���
	Vector3D force = springforce + dampforce;
	Vector3D accseler = force;
	//���x�X�V
	m_CurrentVelocity += accseler;
	//�ʒu�X�V
	m_CurrentPos += m_CurrentVelocity;
	m_Pos = m_CurrentPos;
	//�J�����`�ʂ̍ŒZ�����A�Œ�������ݒ肷��
	SetCameraNearFar(m_Near, m_Far);
	//�J�����̈ʒu�ƒ����_�𔽉f����
	SetCameraPositionAndTarget_UpVecY(m_CurrentPos.toVECTOR(), target.toVECTOR());
}




