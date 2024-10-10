//----------------------------------------------------------------------
// @filename ObjectBase.h
// @author: Fukuma Kyohei
// @explanation
// �I�u�W�F�N�g�̐e�N���X
// �I�u�W�F�N�g�͂��̃N���X�A�܂��͂��̔h���N���X���琶��
//----------------------------------------------------------------------
#pragma once
#include "DxLib.h"
#include "../../../Header/Math/Vector3D.h"
#include <vector>
#include <string>

class ObjectBase
{
public:
	//���
	enum class State
	{
		ACTIVE,
		PAUSE,
		DEAD
	};
	ObjectBase(class ModeBase* game);
	virtual ~ObjectBase();
	virtual void Process();
	virtual void Render();
	virtual void Debug();
	//�R���|�[�l���g�ǉ�
	void AddComponent(class Component* component);
	//�R���|�[�l���g�폜
	void RemoveComponent(class Component* component);
	//�Q�b�^�[
	virtual Vector3D GetPos()		const { return m_Pos; }
	virtual Vector3D GetRotation()	const { return m_Rotation; }
	virtual Vector3D GetScale()		const { return m_Scale; }
	virtual bool GetIsTarget()		const { return m_IsTargetting; }
	virtual State GetState()		const { return m_State; }
	class ModeGame* GetGame()		const { return m_Game; }
	std::vector<class Component*> GetComponent() const{ return m_Components; }
	//�Z�b�^�[
	void SetPos(const Vector3D& pos) { m_Pos = pos; }
	void SetRotation(Vector3D rot) { m_Rotation = rot; }
	void SetScale(Vector3D scale) { m_Scale = scale; }
	void SetState(State state) { m_State = state; }
protected:
	//�ʒu
	Vector3D m_Pos;
	//�p�x
	Vector3D m_Rotation;
	//�X�P�[��
	Vector3D m_Scale;
	//���
	State m_State;
	//�^�[�Q�b�g�\��
	bool m_IsTargetting;
	//�R���|�[�l���g
	std::vector<class Component*> m_Components;
	class ModeGame* m_Game;

};

