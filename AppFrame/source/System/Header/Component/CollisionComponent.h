//----------------------------------------------------------------------
// @filename CollisionComponent.h
// @author: Fukuma Kyohei
// @explanation
// �Փ˔���p�R���|�[�l���g
//----------------------------------------------------------------------
#pragma once
#include "../Component/LogicComponent.h"
#include "../Math/Vector3D.h"
class CollisionComponent : public LogicComponent
{
public:
	enum class COLLISIONTYPE : int
	{
		NONE = 0,
		CIRCLE,
		AABB,
		OBB,
		CAPSULE,
		SPHERE
	};
	enum class COLLISIONGROUP : int
	{
		NONE = 0,
		PLAYER,
		ENEMY,
		Neutral
	};
	CollisionComponent(class ObjectBase* owner, int updateowder = 150);
	virtual ~CollisionComponent();
	virtual void Update()override;
	//�Q�b�^�[
	Vector3D GetPos() const { return mPos; }
	float GetRadius() const { return mRadius; }
	float GetSeg() const { return mLineSeg; }
	COLLISIONTYPE GetType() const { return mType; }
	COLLISIONGROUP GetGroup() const { return mGroup; }
	//�Z�b�^�[
	void SetPos(Vector3D pos) { mPos = pos; }
	void SetRadius(float radius) { mRadius = radius; }
	void SetType(COLLISIONTYPE col) { mType = col; }
	void SetSeg(float seg) { mLineSeg = seg; }
	void SetGroup(COLLISIONGROUP group) { mGroup = group; }
protected:
	//�ʒu
	Vector3D mPos;
	//�}�l�[�W���[
	class CollisionManager* mManager;
	//�^�C�v
	COLLISIONTYPE mType;
	//�O���[�v
	COLLISIONGROUP mGroup;
	//���a
	float mRadius;
	//�����̒���
	float mLineSeg;
};

