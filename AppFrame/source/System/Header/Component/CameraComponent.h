//----------------------------------------------------------------------
// @filename CameraComponent.h
// @author: Fukuma Kyohei
// @explanation
// �Q�[�����̃J���������S�ʐ��䂷��R���|�[�l���g
//----------------------------------------------------------------------
#pragma once
#include <utility>
#include "LogicComponent.h"
#include "../Math/Vector3D.h"
#include "../Input/XInput.h"
class CameraComponent : public LogicComponent
{
public:
	CameraComponent(ObjectBase* owner,int updateowder = 100);
	virtual ~CameraComponent();
	static CameraComponent* m_CameraInstance;
	void Update()override;
	//�Q�b�^�[
	static CameraComponent* GetInstance() { return m_CameraInstance; }
	Vector3D GetTarget() const{ return m_Target; }
	Vector3D GetDir() const{ return m_Dir; }
	Vector3D GetPos() const{ return m_Pos; }
	//�Z�b�^�[
	void SetTarget(Vector3D vec) { m_Target = vec; }
protected:
	XInput* m_Pad;
	//�J�����ʒu
	Vector3D m_Pos;
	Vector3D m_Dir;
	//�J���������_
	Vector3D m_Target;
	//�ŒZ�`�拗��
	float m_Near;
	//�Œ��`�拗��
	float m_Far;
	//�I�u�W�F�N�g����J�����܂ł̋���
	float m_Distance;
	//�΂˒萔
	float m_Spring;
	//�����萔
	float m_DampFactor;
	//�ʒu�Ƒ��x
	Vector3D m_CurrentPos;
	Vector3D m_CurrentVelocity;
};

