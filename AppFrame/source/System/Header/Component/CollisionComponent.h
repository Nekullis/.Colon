//----------------------------------------------------------------------
// @filename CollisionComponent.h
// @author: Fukuma Kyohei
// @explanation
// 衝突判定用コンポーネント
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
	//ゲッター
	Vector3D GetPos() const { return mPos; }
	float GetRadius() const { return mRadius; }
	float GetSeg() const { return mLineSeg; }
	COLLISIONTYPE GetType() const { return mType; }
	COLLISIONGROUP GetGroup() const { return mGroup; }
	//セッター
	void SetPos(Vector3D pos) { mPos = pos; }
	void SetRadius(float radius) { mRadius = radius; }
	void SetType(COLLISIONTYPE col) { mType = col; }
	void SetSeg(float seg) { mLineSeg = seg; }
	void SetGroup(COLLISIONGROUP group) { mGroup = group; }
protected:
	//位置
	Vector3D mPos;
	//マネージャー
	class CollisionManager* mManager;
	//タイプ
	COLLISIONTYPE mType;
	//グループ
	COLLISIONGROUP mGroup;
	//半径
	float mRadius;
	//線分の長さ
	float mLineSeg;
};

