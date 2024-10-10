//----------------------------------------------------------------------
// @filename CameraComponent.h
// @author: Fukuma Kyohei
// @explanation
// カプセル型の衝突判定用コンポーネント
//----------------------------------------------------------------------
#pragma once
#include "CollisionComponent.h"
#include "../Math/Vector3D.h"

class CapsuleColComponent :public CollisionComponent
{
public:
	static CapsuleColComponent* capInstance;
	CapsuleColComponent(class ObjectBase* owner, int updateowder = 200);
	virtual ~CapsuleColComponent();
	virtual void Update()override;
	//ゲッター
	static CapsuleColComponent* GetInstance() { return capInstance; }
	Vector3D GetTopPos() const { return mTopPos; }
	//セッター
	void SetTopPos(Vector3D pos) { mTopPos = pos; }
protected:
	Vector3D mTopPos;
};

