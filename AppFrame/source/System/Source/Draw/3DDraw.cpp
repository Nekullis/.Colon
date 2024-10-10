//----------------------------------------------------------------------
// @filename Draw3D.cpp
// @author: Saito Ko 
// @explanation
// 3D��Ԃł̃R���W������`��`�悷�邽�߂̃N���X
//----------------------------------------------------------------------
#include "../../Header/Draw/3DDraw.h"
#include"../../Header/Collision/2DCollision.h"

//----------------------------------------------------------------------
// @brief: 3D��Ԃō��W�̒��S�ɐ���`�悷��
// @param: pos:���W
// @return: ����������true
//----------------------------------------------------------------------
bool Draw3D::PositionDraw3D(const Vector3D& pos) {
	Vector3D line_w[2] = {
		Vector3D(-25,0,0),
		Vector3D(25,0,0)
	};
	Vector3D line_h[2] = {
		Vector3D(0,-25,0),
		Vector3D(0,25,0)
	};
	Vector3D line_d[2] = {
		Vector3D(0,0,-25),
		Vector3D(0,0,25)
	};

	for (int i = 0; i < 2; i++) {
		line_w[i] = line_w[i] + pos;
		line_h[i] = line_h[i] + pos;
		line_d[i] = line_d[i] + pos;
	}

	DrawLine3D(line_w[0].toVECTOR(), line_w[1].toVECTOR(), GetColor(255, 0, 0));
	DrawLine3D(line_h[0].toVECTOR(), line_h[1].toVECTOR(), GetColor(0, 255, 0));
	DrawLine3D(line_d[0].toVECTOR(), line_d[1].toVECTOR(), GetColor(0, 0, 255));

	return true;
}

//----------------------------------------------------------------------
// @brief: 3D��Ԃő����ɋ�`��`�悷��
// @param: pos:���W
// @param: w:��
// @param: d:���s��
// @return: ����������true
//----------------------------------------------------------------------
bool Draw3D::RectangleFootDraw3D(const Vector3D& pos, float w,float d) {
	Vector3D line[5] = {
		// �ʏ�p�i���ォ��E���j
		Vector3D(-w / 2.0f,0,-d / 2.0f),	// ����
		Vector3D(w / 2.0f,0,-d / 2.0f),	// �E��
		Vector3D(w / 2.0f,0, d / 2.0f),	// �E��
		Vector3D(-w / 2.0f,0, d / 2.0f),	// ����
		Vector3D(-w / 2.0f,0,-d / 2.0f),	// ����
	};

	for (int i = 0; i < 5; i++) {
		line[i] = line[i] + pos;
	}
	for (int i = 0; i < 4; i++) {
		DrawLine3D(line[i].toVECTOR(), line[i + 1].toVECTOR(), GetColor(255, 0, 0));
		DrawLine3D(line[0].toVECTOR(), line[0 + 1].toVECTOR(), GetColor(255, 255, 0));
		DrawLine3D(line[1].toVECTOR(), line[1 + 1].toVECTOR(), GetColor(255, 0, 255));
		DrawLine3D(line[3].toVECTOR(), line[3 + 1].toVECTOR(), GetColor(255, 255, 255));
	}
	return true;
}

//----------------------------------------------------------------------
// @brief: 3D��Ԃŋ�`�̓����蔻���`�悷��
// @param: pos:���W
// @param: w:��
// @param: h:����
// @param: d:���s��
// @param: direction:��]�l
// @return: ����������true
bool Draw3D::BoxCollisionDraw3D(const Vector3D& pos,float w, float h, float d, float direction) {
	MATRIX matrix = MGetRotY(direction);
	Vector3D line_down[5] = {
		// �ʏ�p�i���ォ��E���j
		Vector3D(-w / 2.0f,0,-d / 2.0f),	// ����
		Vector3D(w / 2.0f,0,-d / 2.0f),	// �E��
		Vector3D(w / 2.0f,0, d / 2.0f),	// �E��
		Vector3D(-w / 2.0f,0, d / 2.0f),	// ����
		Vector3D(-w / 2.0f,0,-d / 2.0f),	// ����
	};
	Vector3D line_up[5] = {
		// �ʏ�p�i���ォ��E���j
		Vector3D(-w / 2.0f,h,-d / 2.0f),	// ����
		Vector3D(w / 2.0f,h,-d / 2.0f),	// �E��
		Vector3D(w / 2.0f,h, d / 2.0f),	// �E��
		Vector3D(-w / 2.0f,h, d / 2.0f),	// ����
		Vector3D(-w / 2.0f,h,-d / 2.0f),	// ����
	};

	for (int i = 0; i < 5; i++) {
		line_down[i] = VTransform(line_down[i].toVECTOR(), matrix);
		line_up[i] = VTransform(line_up[i].toVECTOR(), matrix);
	}

	for (int i = 0; i < 4; i++) {
		DrawLine3D(line_down[i].toVECTOR(), line_down[i + 1].toVECTOR(), GetColor(255, 0, 0));
		DrawLine3D(line_up[i].toVECTOR(), line_up[i + 1].toVECTOR(), GetColor(255, 0, 0));
		DrawLine3D(line_down[i].toVECTOR(), line_up[i].toVECTOR(), GetColor(255, 0, 0));
	}
	return true;
}

//----------------------------------------------------------------------
// @brief: 3D��ԂŃr���{�[�h�̓����蔻���`�悷��
// @param: pos:���W
// @param: w:��
// @param: h:����
// @param: d:���s��
// @param: direction:��]�l
// @return: ����������true
//----------------------------------------------------------------------
bool Draw3D::CollisionToBillBoradDraw(const Vector3D& pos, float w, float h, float d, float direction_z = 0) {
	Vector3D line_down[5] = {
		// �ʏ�p�i���ォ��E���j
		Vector3D(-w / 2.0f,-h/2,-d / 2.0f),	// ����
		Vector3D( w / 2.0f,-h/2,-d / 2.0f),	// �E��
		Vector3D( w / 2.0f,-h/2, d / 2.0f),	// �E��
		Vector3D(-w / 2.0f,-h/2, d / 2.0f),	// ����
		Vector3D(-w / 2.0f,-h/2,-d / 2.0f),	// ����
	};
	Vector3D line_up[5] = {
		// �ʏ�p�i���ォ��E���j
		Vector3D(-w / 2.0f,h/2,-d / 2.0f),	// ����
		Vector3D( w / 2.0f,h/2,-d / 2.0f),	// �E��
		Vector3D( w / 2.0f,h/2, d / 2.0f),	// �E��
		Vector3D(-w / 2.0f,h/2, d / 2.0f),	// ����
		Vector3D(-w / 2.0f,h/2,-d / 2.0f),	// ����
	};

	MATRIX matrix = MGetRotZ(direction_z);
	matrix = MMult(matrix, GetCameraBillboardMatrix());

	for (int i = 0; i < 5; i++) {
		line_down[i] = VTransform(line_down[i].toVECTOR(), matrix);
		line_up[i] = VTransform(line_up[i].toVECTOR(), matrix);
	}

	for (int i = 0; i < 5; i++) {
		line_down[i] = line_down[i] + pos;
		line_up[i] = line_up[i] + pos;
	}

	for (int i = 0; i < 4; i++) {
		DrawLine3D(line_down[i].toVECTOR(), line_down[i + 1].toVECTOR(), GetColor(255, 0, 0));
		DrawLine3D(line_up[i].toVECTOR(), line_up[i + 1].toVECTOR(), GetColor(255, 0, 0));
		DrawLine3D(line_down[i].toVECTOR(), line_up[i].toVECTOR(), GetColor(255, 0, 0));
	}

	return true;
};

//----------------------------------------------------------------------
// @brief: 3D��Ԃő����ɉ~��`�悷��
// @param: pos:���W
// @param: r:���a
// @return: ����������true
//----------------------------------------------------------------------
bool Draw3D::CircleFootDraw3D(const Vector3D& pos, float r) {
	for (float i = 0; i < 360.0f; i+=1.0f) {
		DrawPixel3D(Vector3D(pos.x + r * cosf(Math::DegToRad(i)), pos.y, pos.z + r * sinf(Math::DegToRad(i))).toVECTOR(), GetColor(255, 0, 0));
	}
	return true;
}

//----------------------------------------------------------------------
// @brief: 3D��Ԃŉ~�̓����蔻���`�悷��
// @param: pos:���W
// @param: r:���a
// @param: h:����
// @param: flag:����`�悷�邩�ǂ���
// @return: ����������true
//----------------------------------------------------------------------
bool Draw3D::CircleCollisionDraw(const Vector3D& pos, float r, float h,bool flag) {
	for (float i = 0; i < 360.0f; i+=1.0f) {
		DrawPixel3D(Vector3D(pos.x + r * cosf(Math::DegToRad(i)), pos.y, pos.z + r * sinf(Math::DegToRad(i))).toVECTOR(), GetColor(255, 0, 0));
		DrawPixel3D(Vector3D(pos.x + r * cosf(Math::DegToRad(i)), pos.y + (h / 2), pos.z + r * sinf(Math::DegToRad(i))).toVECTOR(), GetColor(255, 0, 0));
		DrawPixel3D(Vector3D(pos.x + r * cosf(Math::DegToRad(i)), pos.y + h, pos.z + r * sinf(Math::DegToRad(i))).toVECTOR(), GetColor(255, 0, 0));
		if (flag) {
			if ((static_cast<int>(i) % 90) == 0) {
				DrawLine3D(VGet(pos.x + r * cosf(Math::DegToRad(i)), pos.y, pos.z + r * sinf(Math::DegToRad(i))), VGet(pos.x + r * cosf(Math::DegToRad(i)), pos.y + h, pos.z + r * sinf(Math::DegToRad(i))), GetColor(255, 0, 0));
			}
		}
	}
	return true;
}