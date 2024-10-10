//----------------------------------------------------------------------
// @filename AICompornent.h
// @author: Fukuma Kyohei
// @explanation
// AI�̏�Ԃ��Ǘ�����R���|�[�l���g
//----------------------------------------------------------------------
#pragma once
#include "LogicComponent.h"
#include <unordered_map>
class AIComponent : public LogicComponent
{
public:
	AIComponent(class ObjectBase* owner, int updateowder = 10);
	virtual ~AIComponent();
	//�X�V
	void Update() override;
	//��ԕύX
	void ChangeState(const std::string& name);
	//��Ԃ̓o�^
	void RegisterState(class AIState* state);
private:
	//�C���X�^���X�̕R�t��
	std::unordered_map <std::string, class AIState*> mStateMap;
	//���݂̏��
	class AIState* mState;
};

