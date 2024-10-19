//----------------------------------------------------------------------
// @filename CharacterBase.h
// @author: Fukuma Kyohei
// @explanation
// �I�u�W�F�N�g�̔h���N���X
// �v���C���[��G�N���X�͂�������h������
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
//�萔
constexpr auto GRAVITY_VALUE = 10.0f;

class CharacterBase : public ObjectBase
{
public:
	CharacterBase(class ModeBase* game);
	virtual ~CharacterBase() override;
	virtual void Process()	 override;
	virtual void Render()	 override;
	virtual void Debug()	 override;
	//�Q�b�^�[
	float GetLineSeg()				  const { return m_LineSeg; }
	int	GetHandle()					  const { return m_Handle; }
	int GetHp()						  const { return m_Hp; }
	bool GetUseGravity()			  const { return m_UseGravity; }
	//�Z�b�^�[
	void SetLineSeg		(float line)		{ m_LineSeg = line; }
	void SetHandle		(int handle)		{ m_Handle = handle; }
	void SetHp			(int hp)			{ m_Hp = hp; }
	void SetUseGravity	(bool useGravity)	{ m_UseGravity = useGravity; }
protected:
	//���f���n���h��
	int m_Handle;
	//�̗�
	int m_Hp;
	//��������
	float m_LineSeg;
	//�d�͂Ɋ����邩
	bool m_UseGravity;
};

