//----------------------------------------------------------------------
// @filename ModeSpline.h
// @author: Saito Ko
// @explanation
// �X�v���C���ł̋O���𐶐����t�@�C�����쐬���邽�߂̃N���X
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
#include "stdio.h"
#include "SplineBox.h"

enum class MoveType : int
{
	None = 0,
	Spline,
	Camera
};

enum class ModeType : int
{
	Modyfy = 0,
	AddPoint,
	Remove,
	Save,
	Time,
	Speed
};

enum class SplineType : int
{
	BSpline = 6,
	CatmullRom
};

class ModeSpline : public ModeBase
{
	typedef ModeBase base;
public:
	ModeSpline(XInput* input, Vector3D pos);
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	void Save();
	void SetCameraMove();
	void MoveSplineBox();
	void CollisionCheck();
protected:
	std::vector<SplineBox*> _pointList;
	std::vector<SplineBox*> _deleteList;

	Vector3D _cameraPos;
	Vector3D _cameraOriginPos;
	float _cameraDistance;
	Mouse* _mouse;
	SplineBox* _splineBox;
	float distance = 0.f;
	Vector3D _cameraAngle;

	int _timePickPosX;
	int _speedPickPosX;

	MoveType _moveType;
	ModeType _modeType;
	SplineType _splineType;

	XInput* input;

	float _time = 0.0f;
	float _timeSpeed = 0.01f;

	bool _isPlay;
};