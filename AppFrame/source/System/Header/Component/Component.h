//----------------------------------------------------------------------
// @filename Component.h
// @author: Fukuma Kyohei
// @explanation
// �R���|�[�l���g(�\���v�f)�̐e�N���X
//----------------------------------------------------------------------
#pragma once
#include <string>
class Component
{
public:
	Component(class ObjectBase* owner, int updateowder = 100);
	virtual ~Component();
	//�X�V
	virtual void Update();
	//�Q�b�^�[
	int GetUpdateOwder() const { return m_UpdateOwder; }
	class ObjectBase* GetOwner() { return m_Owner; }
protected:
	//���L�I�u�W�F�N�g
	class ObjectBase* m_Owner;
	//�X�V����
	int m_UpdateOwder;
};

