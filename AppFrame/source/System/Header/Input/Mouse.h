//----------------------------------------------------------------------
// @filename Mouse.h
// @author: Saito Ko
// @explanation
// マウスの座標やクリック情報を管理するクラス
//----------------------------------------------------------------------
#pragma once
#include "../Math/Vector3D.h"
#include "dxlib.h"

#define MOUTH_LEFT  0
#define MOUTH_RIGHT 1
#define MOUTH_CENTER 2
#define MOUTH_MAX 3

class Mouse
{
	public:
	Mouse();
	~Mouse();
	void Update();

	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetOldX() const  { return oldX; }
	int GetOldY() const  { return oldY; }

	bool GetKey(int index) const { return _key[index]; }
	bool GetTrg(int index) const { return _trg[index]; }
	bool GetRel(int index) const { return _rel[index]; }
protected:
	int x,y,oldX,oldY;
	bool _key[MOUTH_MAX];
	bool _trg[MOUTH_MAX];
	bool _rel[MOUTH_MAX];
};

