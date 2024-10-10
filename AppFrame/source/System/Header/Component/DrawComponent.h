//----------------------------------------------------------------------
// @filename DrawComponent.h
// @author: Fukuma Kyohei
// @explanation
// �`��p�R���|�[�l���g�̊��N���X
//----------------------------------------------------------------------
#pragma once
#include "../Math/Vector3D.h"
#include "../../AppFrame/source/System/Header/Component/Component.h"
class DrawComponent:public Component
{
public:
	DrawComponent(class ObjectBase* owner, int updateowder = 250);
	virtual ~DrawComponent();
	//�X�V
	virtual void Update()override;
	virtual void LoadPass(const char* pass);
	//�Q�b�^�[
	int GetHandle()		const { return m_Handle; }
	Vector3D GetPos()	const { return m_Pos; }
	//�Z�b�^�[
	void SetPos(Vector3D pos) { m_Pos = pos; }
	void SetScale(Vector3D scale) { m_Scale = scale; }
protected:
	int m_Handle;
	Vector3D m_Scale;
	const char* m_Pass;
	Vector3D m_Pos;
};

