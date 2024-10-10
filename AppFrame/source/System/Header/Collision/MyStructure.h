//----------------------------------------------------------------------
// @filename MyStructure.h
// @author: Saito Ko 
// @explanation
// �R���W��������Ŏg�p����N���X��\���̂��`����t�@�C��
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include "../Math/Vector3D.h"
#include "../Function/Easing.h"
#include <vector>
#include <string>

// RECT�p�\����
struct MYRECT {
	float		x, y, w, h;
};

// RECT�p�\����+�A���t�@
struct MYRECT_PLUS : public MYRECT{
	float cx, cy;
	float direction;
};

struct MYCIRCLE {
	float x, y;
	float r;
};

struct HITSLIDE {
	int	 hit;				// �������Ă����1�A�������Ă��Ȃ������0
	int slide_x, slide_y;	// �������Ă���ꍇ�A���炷�ׂ��l
	int index;
};

struct POINT_LINE_SHORT {
	Vector3D hit_point;
	float length = 0.0f;
	float coefficient = 0.0f;//�x�N�g���W��
};

struct TWOLINE_SHORT {
	Vector3D lineOnePoint;
	Vector3D lineTwoPoint;
	float lineOneCoefficient = 0.0f;
	float lineTwoCoefficient = 0.0f;
	float length = 0.0f;
};

class CollisionBase
{
public:
	CollisionBase() { name = ""; isHit = false; isHitOld = false; };
	CollisionBase(std::string name) { this->name = name; isHit = false; isHitOld = false;};
	virtual ~CollisionBase() {};
	void SetName(std::string name) { this->name = name; }
	virtual void Update(){ isHitOld = isHit; isHit = false; };
	virtual void Update(Vector3D pos) { isHitOld = isHit; isHit = false; this->pos = pos;}
	virtual void Render(unsigned int color) = 0;
	std::string GetName() { return name; }
public:
	Vector3D pos;
	bool isHit;
	bool isHitOld;
protected:
	std::string name;
};

class Sphere : public CollisionBase
{
public:
	Sphere() : CollisionBase(){
		pos = VGet(0.0f, 0.0f, 0.0f);
		r = 0.0f;
	}
	Sphere(Vector3D pos, float r) : CollisionBase() {
		this->pos = pos;
		this->r = r;
	}
	Sphere(std::string name, Vector3D pos, float r) : CollisionBase(name) {
		this->pos = pos;
		this->r = r;
	}

	// �`�揈��
	void Render(unsigned int color)override;

	float r;
};

class OBB : public CollisionBase
{
public:
	OBB() : CollisionBase() {
		// ������Ԃł̓��[���h�̎��ƕ��s�ȏ�Ԃɂ���iAABB�j
		dir_vec[0] = Vector3D(1.0f, 0.0f, 0.0f);
		dir_vec[1] = Vector3D(0.0f, 1.0f, 0.0f);
		dir_vec[2] = Vector3D(0.0f, 0.0f, 1.0f);

		for (int i = 0; i < 3; ++i) {			
			length[i] = 0.0f;
		}
	}
	OBB(std::string name, Vector3D pos) : CollisionBase(name) {
		this->pos = pos;
		// ������Ԃł̓��[���h�̎��ƕ��s�ȏ�Ԃɂ���iAABB�j
		dir_vec[0] = Vector3D(1.0f, 0.0f, 0.0f);
		dir_vec[1] = Vector3D(0.0f, 1.0f, 0.0f);
		dir_vec[2] = Vector3D(0.0f, 0.0f, 1.0f);

		for (int i = 0; i < 3; ++i) {
			length[i] = 0.0f;
		}
	}
	OBB(std::string name,Vector3D pos, Vector3D length) : CollisionBase(name) {
		this->pos = pos;
		dir_vec[0] = Vector3D(1.0f, 0.0f, 0.0f);
		dir_vec[1] = Vector3D(0.0f, 1.0f, 0.0f);
		dir_vec[2] = Vector3D(0.0f, 0.0f, 1.0f);
		SetLength(length);
	}

	void SetLength(Vector3D value) {
		length[0] = value.x;
		length[1] = value.y;
		length[2] = value.z;
	}

	// ��]����
	// x��->y��->z���̏��Ԃ�, �e������]������
	void Rotate(Vector3D vRot);

	// ���_���W�̎擾
	void GetVertexPos(std::vector<Vector3D>& vertexPosList);

	// �`�揈��
	void Render(unsigned int color)override;

	Vector3D dir_vec[3];//xv,yv,zv
	float length[3]; //0:w 1:h 3:d
};

class Capsule : public CollisionBase {
public:
	Capsule() : CollisionBase() {
		up = 0.0f;
		r = 0.0f;
		for (int i = 0; i < 3; i++) {
			direction[i] = 0;
		}
	};
	Capsule(std::string name, Vector3D pos, float up, float r) : CollisionBase(name) {
		this->pos = pos;
		this->up = up;
		this->r = r;
		for (int i = 0; i < 3; i++) {
			direction[i] = 0;
		}
	};
	void Update()override {
		up_pos = pos + Vector3D(0,up,0);
	};

	// �`�揈��
	void Render(unsigned int color)override;

	Vector3D up_pos;
	float up = 0.0f;
	float r = 0.0f;
	float direction[3] = { 0.0f,0.0f,0.0f };
};