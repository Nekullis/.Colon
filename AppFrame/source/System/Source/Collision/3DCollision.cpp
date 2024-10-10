//----------------------------------------------------------------------
// @filename 3DCollision.cpp
// @author: Saito Ko Fukuma Kyohei Kawai Daisuke
// @explanation
// 3D�Ŏg�p���铖���蔻����s���N���X
//----------------------------------------------------------------------
#include "../../Header/Collision/3DCollision.h"

//----------------------------------------------------------------------
// @brief XZ���ʂł̓����蔻��
// @param pos1 �ʒu1
// @param w1 ��1
// @param d1 ���s1
// @param pos2 �ʒu2
// @param w2 ��2
// @param d2 ���s2
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::PlaneCollision(Vector3D pos1, float w1,float d1, Vector3D pos2, float w2, float d2)
{
	Vector3D receiv = pos1 - Vector3D(w1 / 2, 0, d1 / 2);
	Vector3D give = pos2 - Vector3D(w2 / 2, 0, d2 / 2);

	return Collision2D::IsHitBox(receiv.x, receiv.z, w1, d1, give.x, give.z, w2, d2);
}

//----------------------------------------------------------------------
// @brief AABB�ł̓����蔻��
// @param pos1 �ʒu1
// @param w1 ��1
// @param h1 ����1
// @param d1 ���s1
// @param pos2 �ʒu2
// @param w2 ��2
// @param h2 ����2
// @param d2 ���s2
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::AABBCollision(Vector3D pos1, float w1, float h1, float d1, Vector3D pos2, float w2, float h2, float d2)
{
	Vector3D receiv = pos1 - Vector3D(w1 / 2, h1 / 2, d1 / 2);
	Vector3D give = pos2 - Vector3D(w2 / 2, h2 / 2, d2 / 2);

	if(Collision2D::IsHitBox(receiv.x, receiv.z, w1, d1, give.x, give.z, w2, d2)) {
		if(Collision2D::IsHitBox(receiv.x, receiv.y, w1, h1, give.x, give.y, w2, h2)) {
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------
// @brief XZ���ʂł̉~�̓����蔻��
// @param pos1 �ʒu1
// @param r1 ���a1
// @param pos2 �ʒu2
// @param r2 ���a2
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::CircleCollision(Vector3D pos1, float r1, Vector3D pos2, float r2){
	Vector3D col = pos1 - pos2; col.y = 0;
	float r = r1 + r2;
	if (r * r > col.x * col.x + col.z * col.z) {
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
// @brief �~���̓����蔻��
// @param pos1 �ʒu1
// @param r1 ���a1
// @param h1 ����1
// @param pos2 �ʒu2
// @param r2 ���a2
// @param h2 ����2
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::CylindCollision(Vector3D pos1, float r1, float h1, Vector3D pos2, float r2, float h2) {
	Vector3D col = pos1 - pos2;
	float r = r1 + r2;
	if (r * r > col.x * col.x + col.z * col.z) {
		if (pos1.y < pos2.y && pos1.y + h1 > pos2.y ||
			pos1.y < pos2.y + h2 && pos1.y + h1 > pos2.y + h2) {
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------
// @brief AABB�̍ŒZ����
// @param Box �{�b�N�X�̈ʒu
// @param wide ��
// @param height ����
// @param depth ���s
// @param Point �_�̈ʒu
// @return �ŒZ����
//----------------------------------------------------------------------
float Collision3D::AABBShortLength(Vector3D Box, float wide, float height ,float depth , Vector3D Point) {
	float SqLen = 0;   // �����ׂ̂���̒l���i�[
	float point[3] = { Point.x,Point.y,Point.z};
	float box[3] = { Box.x,Box.y,Box.z };
	float length[3] = { wide/2,height/2,depth/2 };

	for (int i = 0; i < 3; i++)
	{
		// �e���œ_���ŏ��l�ȉ��������͍ő�l�ȏ�Ȃ�΁A�����l��
		if (point[i] < box[i] - length[i])  // i=0��X�A1��Y�A2��Z�̈Ӗ��ł�
			SqLen += ((point[i] - (box[i] - length[i])) * (point[i] - (box[i] - length[i])));
		if (point[i] > box[i] + length[i])
			SqLen += ((point[i] - (box[i] + length[i])) * (point[i] - (box[i] + length[i])));
	}
	return sqrtf(SqLen);
}

//----------------------------------------------------------------------
// @brief OBB���m�̓����蔻��
// @param obb_1 OBB�̏��
// @param obb_2 OBB�̏��
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::OBBCollision(OBB obb_1, OBB obb_2) {
	// length�͑S�̂̒����Ȃ̂Ŏg���Ƃ��͔����ɂ���
	//NAe �� �����x�N�g�� Ae �� �����x�N�g���ɂ��̒��������������́@�����x�N�g���̓}�g���N�X���玝���Ă������̂Ő��K������Ă���

	Vector3D NAe1 = obb_1.dir_vec[0], Ae1 = NAe1 * (obb_1.length[0] / 2);
	Vector3D NAe2 = obb_1.dir_vec[1], Ae2 = NAe2 * (obb_1.length[1] / 2);
	Vector3D NAe3 = obb_1.dir_vec[2], Ae3 = NAe3 * (obb_1.length[2] / 2);
	Vector3D NBe1 = obb_2.dir_vec[0], Be1 = NBe1 * (obb_2.length[0] / 2);
	Vector3D NBe2 = obb_2.dir_vec[1], Be2 = NBe2 * (obb_2.length[1] / 2);
	Vector3D NBe3 = obb_2.dir_vec[2], Be3 = NBe3 * (obb_2.length[2] / 2);
	//Misalignment�ł��Ȃ��̒��S�Ƀ��f�������炵�Ă��� ��̂��������ōςނƎv�����t���C�g�n�Ȃǂ�3����]������Ƃ���
	//VTransform�̒��̉�]�s���y�������łȂ����Ƃ����܂߂�3���ŉ�]���Ă�������
	Vector3D Interval = obb_1.pos - obb_2.pos;

	//  �e���̕����x�N�g���ƕ������Ƃ̐�Βl�̓��ς̘a���܂Ƃ߂����̂� ���S�_�Ԃ̋������r�����S�_�ԋ������Z��������Փ˂��Ă���

	// ������ : Ae1
	float rA = Ae1.Len();
	float rB = Math::LenSegOnSeparateAxis(NAe1, Be1, Be2, Be3);
	float L = fabsf(Interval.Dot(NAe1));
	if (L > rA + rB)
		return false; // �Փ˂��Ă��Ȃ�

	// ������ : Ae2
	rA = Ae2.Len();
	rB = Math::LenSegOnSeparateAxis(NAe2, Be1, Be2, Be3);
	L = fabsf(Interval.Dot(NAe2));
	if (L > rA + rB)
		return false;

	// ������ : Ae3
	rA = Ae3.Len();
	rB = Math::LenSegOnSeparateAxis(NAe3, Be1,Be2,Be3);
	L = fabsf(Interval.Dot(NAe3));
	if (L > rA + rB)
		return false;

	// ������ : Be1
	rA = Math::LenSegOnSeparateAxis(NBe1, Ae1, Ae2, Ae3);
	rB = Be1.Len();
	L = fabsf(Interval.Dot(NBe1));
	if (L > rA + rB)
		return false;

	// ������ : Be2
	rA = Math::LenSegOnSeparateAxis(NBe2, Ae1, Ae2, Ae3);
	rB = Be2.Len();
	L = fabsf(Interval.Dot(NBe2));
	if (L > rA + rB)
		return false;

	// ������ : Be3
	rA = Math::LenSegOnSeparateAxis(NBe3, Ae1, Ae2, Ae3);
	rB = Be3.Len();
	L = fabsf(Interval.Dot(NBe3));
	if (L > rA + rB)
		return false;

	// ��9���̌v�Z�͏�̕����x�N�g�������ł��ł���
	//  OBB���ӓ��m�Ђ˂����֌W�ŋ߂Â��ƕ����x�N�g���̕������ł͔���ł��Ȃ��Ȃ邻���ł�

	// ������ : C11   Ae1*Be1�ɐ���
	Vector3D Cross;
	Cross = NAe1.Cross(NBe1);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C12   Ae1*Be2
	Cross = NAe1.Cross(NBe2);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C13   Ae1*Be3
	Cross = NAe1.Cross(NBe3);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae2, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C21   Ae2*Be1
	Cross = NAe2.Cross(NBe1);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C22   Ae2*Be2
	Cross = NAe2.Cross(NBe2);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C23   Ae2*Be3
	Cross = NAe2.Cross(NBe3);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae3);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C31   Ae3*Be1
	Cross = NAe3.Cross(NBe1);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = Math::LenSegOnSeparateAxis(Cross, Be2, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C32   Ae3*Be2
	Cross = NAe3.Cross(NBe2);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be3);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// ������ : C33   Ae3*Be3
	Cross = NAe3.Cross(NBe3);
	rA = Math::LenSegOnSeparateAxis(Cross, Ae1, Ae2);
	rB = Math::LenSegOnSeparateAxis(Cross, Be1, Be2);
	L = fabsf(Interval.Dot(Cross));
	if (L > rA + rB)
		return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}

//----------------------------------------------------------------------
// @brief �_�ƒ����̍ŒZ����
//             �ŒZ�����͑�̓_�Ɠ_�𐂒��ɉ��������ɂȂ�
// @param line_start �����̎n�_
// @param line_end �����̏I�_
// @param point �_�̈ʒu
// @return �ŒZ����
//----------------------------------------------------------------------
POINT_LINE_SHORT Collision3D::PointLineShortLength(Vector3D line_start, Vector3D line_end, Vector3D point) {
	POINT_LINE_SHORT Re;
	Vector3D line = line_end - line_start;
	float length = line.Sqlen();

	Re.coefficient = 0.0f;
	if (length > 0.0f) {
		Re.coefficient = line.Dot(point - line_start) / length;
	}

	Re.hit_point = line_start + (line * Re.coefficient);
	Re.length = (Re.hit_point - point).Len();

	return Re;
};

//----------------------------------------------------------------------
// @brief �_�Ɛ����̍ŒZ����
//             �ŒZ�����͑�̓_�Ɠ_�𐂒��ɉ��������ɂȂ�
// @param line_start �����̎n�_
// @param line_end �����̏I�_
// @param point �_�̈ʒu
// @return �ŒZ����
//----------------------------------------------------------------------
POINT_LINE_SHORT Collision3D::PointLineSegShortLength(Vector3D line_start, Vector3D line_end, Vector3D point) {
	Vector3D end = line_end - line_start;
	POINT_LINE_SHORT Re = Collision3D::PointLineShortLength(line_start, line_end, point);

	if (!Math::CheckAcuteAngle(point, line_start, line_end)) {
		//�n�_��
		Re.hit_point = line_start;
		Re.length = (line_start - point).Len();
	}
	else if (!Math::CheckAcuteAngle(point, line_start + end, line_start)) {
		//�I�_��
		Re.hit_point = line_start + end;
		Re.length = (end - point).Len();
	}

	return Re;
}

//----------------------------------------------------------------------
// @brief 2�����̐����ɂȂ�ꏊ�ƃx�N�g���W��
// @param line_1_start ����1�̎n�_
// @param line_1_end ����1�̏I�_
// @param line_2_start ����2�̎n�_
// @param line_2_end ����2�̏I�_
// @return 2�����̍ŒZ�����E����1�̍ŒZ�����̓_�E����1�̃x�N�g���W���E����2�̍ŒZ�����̓_�E����2�̃x�N�g���W��
//----------------------------------------------------------------------
TWOLINE_SHORT Collision3D::TwoLineShortPoint(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {
	TWOLINE_SHORT Re;
	Vector3D one_way = line_1_end - line_1_start;
	Vector3D two_way = line_2_end - line_2_start;

	//���s�Ȓ��������ׂ�
	if (Math::CheckParallelRelation(line_1_start, line_1_end, line_2_start, line_2_end)) {
		POINT_LINE_SHORT pls = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, line_2_start);
		Re.length = pls.length;
		Re.lineOnePoint = line_1_start;
		Re.lineOneCoefficient = 0.0f;
		Re.lineTwoPoint = pls.hit_point;
		Re.lineTwoCoefficient = pls.coefficient;

		return Re;
	}

	float Dot_OwTw = one_way.Dot(two_way);//����1�ƕ���2�̐����ȋ���
	float Dot_OsOw = one_way.Sqlen();//����1�ƕ���1�̐����ȋ���
	float Dot_TsTw = two_way.Sqlen();//����2�ƕ���2�̐����ȋ���
	Vector3D Sub_OsTs = line_1_start - line_2_start;//�n�_1����n�_2�̕���

	Re.lineOneCoefficient = (Dot_OwTw * two_way.Dot(Sub_OsTs) - Dot_TsTw * one_way.Dot(Sub_OsTs)) / (Dot_OsOw * Dot_TsTw - Dot_OwTw * Dot_OwTw);
	Re.lineOnePoint = line_1_start + one_way * Re.lineOneCoefficient;
	Re.lineTwoCoefficient = two_way.Dot(Re.lineOnePoint - line_2_start) / Dot_TsTw;
	Re.lineTwoPoint = line_2_start + two_way * Re.lineTwoCoefficient;
	Re.length = (Re.lineTwoPoint - Re.lineOnePoint).Len();

	return Re;
}

//----------------------------------------------------------------------
// @brief 2�����̐����ɂȂ�ꏊ�ƃx�N�g���W��
// @param line_1_start ����1�̎n�_
// @param line_1_end ����1�̏I�_
// @param line_2_start ����2�̎n�_
// @param line_2_end ����2�̏I�_
// @return 2�����̍ŒZ�����E����1�̍ŒZ�����̓_�E����1�̃x�N�g���W���E����2�̍ŒZ�����̓_�E����2�̃x�N�g���W��
//----------------------------------------------------------------------
TWOLINE_SHORT Collision3D::TwoSegmentShortPoint(Vector3D line_1_start, Vector3D line_1_end, Vector3D line_2_start, Vector3D line_2_end) {

	TWOLINE_SHORT Re;

	Vector3D one_way = line_1_end - line_1_start;
	Vector3D two_way = line_2_end - line_2_start;

	float effective_range = 0.001f;

	//�k�ށ@���������ē_�ɂȂ��Ă���@�_�ōl����
	//����1���k�ނ��Ă��邩
	if (one_way.Sqlen() < effective_range) {
		//����1���k�ނ��Ă���
		//����2���k�ނ��Ă��邩
		if (two_way.Sqlen() < effective_range) {
			// ����2�͏k�ނ��Ă���
			Re.lineOnePoint = line_1_start;
			Re.lineTwoPoint = line_2_start;
			Re.lineOneCoefficient = 0.0f;
			Re.lineTwoCoefficient = 0.0f;
			Re.length = (line_2_start- line_1_start).Len();
			return Re;
		}
		else {
			// ����2�͏k�ނ��Ă��Ȃ�����
			//����1�̎n�_�ƒ���2�̍ŒZ����
			POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_2_start, line_2_end, line_1_start);
			Re.lineOnePoint = line_1_start;
			Re.lineOneCoefficient = 0.0f;
			Re.lineTwoPoint = value.hit_point;
			Re.lineTwoCoefficient = value.coefficient;
			Re.length = value.length;
			Re.lineTwoCoefficient = Math::Clamp(0, 1.0f, Re.lineTwoCoefficient);
			return Re;
		}
	}
	//����2���k�ނ��Ă��邩
	else if (two_way.Sqlen() < effective_range) {
		// ����2�͏k�ނ��Ă���
		//��Ő���1�͊m�F�����̂ł����͂��Ȃ�
		POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, line_2_start);
		Re.lineOnePoint = value.hit_point;
		Re.lineOneCoefficient = value.coefficient;
		Re.lineTwoPoint = line_2_start;
		Re.lineTwoCoefficient = 0.0f;
		Re.length = value.length;
		Re.lineOneCoefficient = Math::Clamp(0, 1.0f, Re.lineOneCoefficient);
		return Re;
	}

	//�k�ނ��Ȃ������̂Ő������m�ōl����
	//����1�Ɛ���2�����s��
	if (Math::CheckParallelRelation(line_1_start, line_1_end, line_2_start, line_2_end)) {
		//���s�������̂Ő����̒[�̈���o1�Ƃ���
		POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, line_2_start);
		Re.lineOnePoint = line_1_start;
		Re.lineOneCoefficient = 0.0f;
		Re.lineTwoPoint = value.hit_point;
		Re.lineTwoCoefficient = value.coefficient;
		Re.length = value.length;
		if (0.0f <= Re.lineTwoCoefficient && Re.lineTwoCoefficient <= 1.0f) {
			return Re;
		}
	}
	else {
		//���s�łȂ������̂Ő�����̍ŒZ���������߂�
		Re = Collision3D::TwoLineShortPoint(line_1_start, line_1_end, line_2_start, line_2_end);
		if (0.0f <= Re.lineOneCoefficient && Re.lineOneCoefficient <= 1.0f &&
			0.0f <= Re.lineTwoCoefficient && Re.lineTwoCoefficient <= 1.0f) {
			return Re;
		}
	}

	//�����̒[�������̊O���ɂ���̂�
	//����1���̃x�N�g���W����0����1�̊ԂɃN�����v���Đ������~�낷

	Re.lineOneCoefficient = Math::Clamp(0, 1, Re.lineOneCoefficient);
	Re.lineOnePoint = line_1_start + one_way * Re.lineOneCoefficient;
	POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(line_2_start, line_2_end, Re.lineOnePoint);
	Re.lineTwoCoefficient = value.coefficient;
	Re.lineTwoPoint = value.hit_point;
	Re.length = value.length;

	if (0.0f <= Re.lineTwoCoefficient && Re.lineTwoCoefficient <= 1.0f) {
		return Re;
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	Re.lineTwoCoefficient = Math::Clamp(0, 1, Re.lineTwoCoefficient);
	Re.lineTwoPoint = line_2_start + two_way * Re.lineTwoCoefficient;
	value = Collision3D::PointLineSegShortLength(line_1_start, line_1_end, Re.lineTwoPoint);

	Re.lineOneCoefficient = value.coefficient;
	Re.lineOnePoint = value.hit_point;
	Re.length = value.length;

	if (0.0f <= Re.lineOneCoefficient && Re.lineOneCoefficient <= 1.0f) {
		return Re;
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------
	Re.lineOneCoefficient = Math::Clamp(0, 1, Re.lineOneCoefficient);
	Re.lineOnePoint = line_1_start + one_way * Re.lineOneCoefficient;
	Re.length = (Re.lineTwoPoint - Re.lineOnePoint).Len();
	return Re;
}

//----------------------------------------------------------------------
// @brief ���Ƌ��̓����蔻��
// @param pos1 �ʒu1
// @param r1 ���a1
// @param pos2 �ʒu2
// @param r2 ���a2
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::SphereCol(Vector3D pos1, float r1, Vector3D pos2, float r2) {
	return (pos2 - pos1).Sqlen() <= (r1 + r2) * (r1 + r2);
}

//----------------------------------------------------------------------
// @brief ���Ƌ��̓����蔻��
// @param sphere1 ��1
// @param sphere2 ��2
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::SphereCol(const Sphere& sphere1, const Sphere& sphere2)
{
	return Collision3D::SphereCol(sphere1.pos, sphere1.r, sphere2.pos, sphere2.r);
}

//----------------------------------------------------------------------
// @brief �J�v�Z�����m�̓����蔻��
// @param line_1_start �J�v�Z��1�̎n�_
// @param line_1_end �J�v�Z��1�̏I�_
// @param r_1 �J�v�Z��1�̔��a
// @param line_2_start �J�v�Z��2�̎n�_
// @param line_2_end �J�v�Z��2�̏I�_
// @param r_2 �J�v�Z��2�̔��a
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::TwoCapsuleCol(Vector3D line_1_start, Vector3D line_1_end, float r_1, Vector3D line_2_start, Vector3D line_2_end, float r_2) {
	TWOLINE_SHORT value = Collision3D::TwoSegmentShortPoint(line_1_start, line_1_end, line_2_start, line_2_end);
	return value.length <= r_1 + r_2;
}

//----------------------------------------------------------------------
// @brief �J�v�Z�����m�̓����蔻��
// @param capsule1 �J�v�Z��1
// @param capsule2 �J�v�Z��2
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::TwoCapsuleCol(const Capsule& capsule1, const Capsule& capsule2)
{
	return Collision3D::TwoCapsuleCol(capsule1.pos, capsule1.up_pos, capsule1.r, capsule2.pos, capsule2.up_pos, capsule2.r);
}

//----------------------------------------------------------------------
// @brief ���ƃJ�v�Z���̓����蔻��
// @param spherePos ���̈ʒu
// @param sphereR ���̔��a
// @param capsuleStartPos �J�v�Z���̎n�_
// @param capsuleEndPos �J�v�Z���̏I�_
// @param capsuleR �J�v�Z���̔��a
// @param[out] shortestPos �ŒZ�����̈ʒu
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::SphereCapsuleCol(Vector3D spherePos, float sphereR, Vector3D capsuleStartPos, Vector3D capsuleEndPos, float capsuleR, Vector3D* shortestPos)
{
	POINT_LINE_SHORT value = Collision3D::PointLineSegShortLength(capsuleStartPos, capsuleEndPos, spherePos);
	if (shortestPos != nullptr) {
		*shortestPos = value.hit_point;
	}
	return Collision3D::SphereCol(spherePos, sphereR, value.hit_point, capsuleR);
}

//----------------------------------------------------------------------
// @brief ���ƃJ�v�Z���̓����蔻��
// @param sphere ��
// @param capsule �J�v�Z��
// @param[out] shortestPos �ŒZ�����̈ʒu
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::SphereCapsuleCol(const Sphere& sphere, const Capsule& capsule, Vector3D* shortestPos)
{
	return Collision3D::SphereCapsuleCol(sphere.pos, sphere.r, capsule.pos, capsule.up_pos, capsule.r, shortestPos);
}

//----------------------------------------------------------------------
// @brief �_��OBB�̍Őڋߓ_
// @param point �_�̈ʒu
// @param obb OBB�̏��
// @return OBB�Ɠ_����ԋ߂�OBB�̈ʒu
//----------------------------------------------------------------------
Vector3D Collision3D::PointOBB(Vector3D point, OBB obb) {
	Vector3D pos = obb.pos;
	Vector3D cp = point - pos;
	Vector3D Re = pos;
	float length = 0.0f;
	for (int i = 0; i < 3; i++) {
		length = cp.Dot(obb.dir_vec[i]);

		if (length > (obb.length[i] / 2)) {
			length = obb.length[i] / 2;
		}
		else if (length < -obb.length[i] / 2) {
			length = -obb.length[i] / 2;
		}
		Re = Re+obb.dir_vec[i]* length;
	}
	return Re;
}

//----------------------------------------------------------------------
// @brief OBB�Ƌ��̓����蔻��
// @param obb OBB
// @param point ���̈ʒu
// @param r ���̔��a
// @param[out] hitPos �Փ˂����ʒu
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::OBBSphereCol(OBB obb, Vector3D point, float r, Vector3D* hitPos) {
	Vector3D pos = Collision3D::PointOBB(point, obb);

	Vector3D vector = pos - point;

	if (vector.Dot(vector) <= r * r) {
		if (hitPos != nullptr) {
			*hitPos = pos;
		}
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
// @brief OBB�Ƌ������蔻��
// @param obb OBB
// @param sphere ��
// @param[out] hitPos �Փ˂����ʒu
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::OBBSphereCol(const OBB& obb, const Sphere& sphere, Vector3D* hitPos)
{
	return Collision3D::OBBSphereCol(obb, sphere.pos, sphere.r, hitPos);
}

//----------------------------------------------------------------------
// @brief OBB�ƃJ�v�Z���̓����蔻��
// @param obb OBB
// @param capsuleStartPos �J�v�Z���̎n�_
// @param capsuleEndPos �J�v�Z���̏I�_
// @param capsuleR �J�v�Z���̔��a
// @param[out] hitPos �Փ˂����ʒu
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::OBBCapsuleCol(OBB obb, Vector3D line_start, Vector3D line_end, float r, Vector3D* hitPos) {
	POINT_LINE_SHORT  a = Collision3D::PointLineSegShortLength(line_start, line_end, obb.pos);

	Vector3D pos = Collision3D::PointOBB(a.hit_point, obb);

	Vector3D vector = pos - a.hit_point;

	if (vector.Dot(vector) <= r * r) {
		if (hitPos != nullptr) {
			*hitPos = pos;
		}
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
// @brief OBB�ƃJ�v�Z���̓����蔻��
// @param obb OBB
// @param capsule �J�v�Z��
// @param[out] hitPos �Փ˂����ʒu
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::OBBCapsuleCol(OBB obb, Capsule capsule, Vector3D* hitPos) {
	return OBBCapsuleCol(obb, capsule.pos, capsule.up_pos, capsule.r, hitPos);
}

//----------------------------------------------------------------------
// @brief ������OBB�̓����蔻��
// @param line_start �����̎n�_
// @param line_end �����̏I�_
// @param obb OBB
// @return �Փ˂��Ă��邩�ǂ���
//----------------------------------------------------------------------
bool Collision3D::SegmentOBB(Vector3D line_start, Vector3D line_end, OBB obb){
	for(int i = 0; i < 3; i++){
		TWOLINE_SHORT value = Collision3D::TwoSegmentShortPoint(line_start, line_end, obb.pos, obb.pos + obb.dir_vec[i] * obb.length[i]);
		if (value.length > obb.length[i]/2) {
			return false;
		}
	}
	return true;
};

//---------------------------------------------------------------------------------
// �͍�����Y
//---------------------------------------------------------------------------------
 
//--------------------------------------------------------
// @brief 0�`1�̊ԂɃN�����v
// @param[out] v �N�����v����l
// @return �Ȃ�
//--------------------------------------------------------
void Collision3D::clamp01(float& v) {
	if (v < 0.0f)
		v = 0.0f;
	else if (v > 1.0f)
		v = 1.0f;
}

//--------------------------------------------------------
// @brief -1�`1�̊ԂɃN�����v
// @param[out] v �N�����v����l
// @return �Ȃ�
// --------------------------------------------------------
void Collision3D::clamp1m1(float& v) {
	if (v < -1.0f)
		v = -1.0f;
	else if (v > 1.0f)
		v = 1.0f;
}

//--------------------------------------------------------
// @brief min�`max�̊ԂɃN�����v
// @param[out] v �N�����v����l
// @param[in] min �ŏ��l
// @param[in] max �ő�l
// @return �Ȃ�
// --------------------------------------------------------
void Collision3D::clamp(float& v, float min, float max) {
	if (v < min)
		v = min;
	else if (v > max)
		v = max;
}

//--------------------------------------------------------
// @brief ���s�����ׂ�
// @param[in] p1 ���W1
// @param[in] p2 ���W2
// @return ���s�Ȃ�true
bool Collision3D::isParallel(VECTOR p1, VECTOR p2) {

	//�O�ώ��
	VECTOR v = VCross(p1, p2);

	//�T�C�Y����
	float d = VSize(v);

	// �덷�͈͓��Ȃ畽�s�Ɣ���
	if (-0.0001f < d && d < 0.0001f) {

		return true;
	}

	return false;
}

//--------------------------------------------------------
// @brief DXlib��p�����ǎC��x�N�g���̍쐬
// @param HitNorm ���������ʂ̖@��
// @param MoveV �ړ��x�N�g��
// @return �ǎC��x�N�g��
// --------------------------------------------------------
Vector3D Collision3D::MakeWallLap(MV1_COLL_RESULT_POLY HitNorm, Vector3D MoveV) {

	//�@���x�N�g��(V)�����߂邽�߂̌���
	// V = F * aN
	// F(�ړ��x�N�g��),a(-F * N),N(�@���x�N�g���i�P�ʉ�������j)

	// �@���x�N�g��
	Vector3D norm = HitNorm.Normal;
	norm = norm.Normalize();

	// �ړ��x�N�g��
	Vector3D FrontV = MoveV;

	// �ړ��x�N�g����-1��������iReverseMove�j
	Vector3D RMove = FrontV * -1;

	//�ǂɑ΂��ĕ��s�ȃx�N�g��(�ǎC��)���߂�̂Ɏg�����
	//�@���Ƌt�ړ��x�N�g���̓���
	float a = RMove.Dot(norm);

	//�ǂɑ΂��ĕ��s�ȃx�N�g��(�ǎC��)���߂�̂Ɏg������̂Q
	//�ړ��x�N�g���ɑ������߂̃x�N�g��
	norm = norm * a;

	//�ǎC��x�N�g���쐬
	//WR = wall rapping = �ǎC��
	Vector3D WR = FrontV + norm;

	return WR;
}

//--------------------------------------------------------
// @brief �x�N�g���̐�Βl�����߂�
// @param v �x�N�g��
// @return �x�N�g���̐�Βl
// --------------------------------------------------------
float Collision3D::VectorAbs(Vector3D v)
{
	float v_comp[] = { v.x,v.y,v.z };
	int length = sizeof(v_comp) / sizeof(v_comp[0]);
	for (int i = 0; i < length; ++i)
	{
		v_comp[i] = abs(v_comp[i]);
	}
	Vector3D absV = Vector3D(v_comp[0], v_comp[1], v_comp[2]);
	return  sqrtf(absV.Sqlen());
}

//--------------------------------------------------------
// @brief �_�ƎO�p���̓����蔻��
// @param top �O�p���̒��_
// @param bottom �O�p���̒��
// @param r ���a
// @param p �_
// @return �Փ˂��Ă��邩�ǂ���
// --------------------------------------------------------
bool Collision3D::CheckHitPointCorn(Vector3D top, Vector3D bottom, float r, Vector3D p)
{
	float h = VectorAbs(bottom - top);
	Vector3D PnT = p - top;
	Vector3D BnT = bottom - top;
	if (0.0f <= PnT.Dot(BnT) &&
		PnT.Dot(BnT) <= h * h &&
		VectorAbs(PnT.Cross(BnT)) <= VectorAbs(PnT) * r * h / sqrtf(r * r + h * h))
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------
// @brief �����ƕ��ʂ̓����蔻��
// @param p1a ���ʂ̓_1
// @param p1n ���ʂ̖@��
// @param p2a �����̎n�_
// @param p2b �����̏I�_
// @param[out] h ��_
// @return �Փ˂��Ă��邩�ǂ���
// --------------------------------------------------------
bool Collision3D::CheckHitSegmentPlane(Vector3D p1a, Vector3D p1n, Vector3D p2a, Vector3D p2b, Vector3D& h)
{
	// ���ʂ̖@���x�N�g���̐���
	float a = p1n.x, b = p1n.y, c = p1n.z;
	// ���ʏ�̓_�̍��W
	float x0 = p1a.x, y0 = p1a.y, z0 = p1a.z;

	// �����̒[�_�̍��W
	float x1 = p2a.x, y1 = p2a.y, z1 = p2a.z;
	float x2 = p2b.x, y2 = p2b.y, z2 = p2b.z;

	// t�̕��ꕔ���̌v�Z�i���ʂƐ����̕����x�N�g���̓��ρj
	float denominator = a * (x2 - x1) + b * (y2 - y1) + c * (z2 - z1);
	if (denominator == 0) {
		// ���ꂪ0�̏ꍇ�A���ʂƐ����͕��s�ł��邽�ߌ�_�Ȃ�
		return false;
	}

	// t�̕��q�����̌v�Z�i���ʏ�̓_�Ɛ����̎n�_�̃x�N�g���̓��ρj
	float numerator = a * (x0 - x1) + b * (y0 - y1) + c * (z0 - z1);

	// t�̌v�Z�i������̂ǂ̈ʒu�Ɍ�_�����邩�������p�����[�^�j
	float t = numerator / denominator;
	if (t < 0.0f || t > 1.0f) {
		// t��0����1�͈̔͊O�ł���΁A��_�͐�����ɑ��݂��Ȃ�
		return false;
	}

	// ��_�̌v�Z�i������̓_�̃p�����[�^�\����t�����j
	h.x = (1 - t) * x1 + t * x2;
	h.y = (1 - t) * y1 + t * y2;
	h.z = (1 - t) * z1 + t * z2;


	return true;
}

//--------------------------------------------------------
// @brief �����ƎO�p�`�̓����蔻��
// @param p1a �����̎n�_
// @param p1b �����̏I�_
// @param p2a �O�p�`�̓_1
// @param p2b �O�p�`�̓_2
// @param p2c �O�p�`�̓_3
// @param[out] h ��_
// @param[out] t ��_�̃p�����[�^
// @return �Փ˂��Ă��邩�ǂ���
// --------------------------------------------------------
bool Collision3D::CheckHitTriangleSegment(Vector3D p1a, Vector3D p1b, Vector3D p2a, Vector3D p2b, Vector3D p2c, Vector3D& h, float& t) {

	// �@���ʂ̕����������߂�
	// �O�p�`�̖@���x�N�g���̐���
	// �O��n = AB x AC
	// plane normal��pn

	Vector3D pn = (p2b - p2a).Cross(p2c - p2a);

	if (pn.x == 0.0f && pn.y == 0.0f && pn.z == 0.0f) {
		return false;
	}

	// ���ʂ̕�����
	// ax + by + cz + d = 0
	// d = -(pn.x * p2a.x + pn.y * p2a.y + pn.z * p2a.z)
	float d = -(pn.x * p2a.x + pn.y * p2a.y + pn.z * p2a.z);

	// �A���������ʂ����؂邩�ǂ����𔻒肷��
	// �������ʂ̂ǂ���ɂ��邩
	float a = pn.x * p1a.x + pn.y * p1a.y + pn.z * p1a.z + d;
	float b = pn.x * p1b.x + pn.y * p1b.y + pn.z * p1b.z + d;

	// a,b�̕������قȂ�ꍇ�A�����͕��ʂ����؂�
	if (a * b >= 0) {
		return false;
	}

	// �B�����ƕ��ʂ̌�_�����߂�
	// �����̕����x�N�g��
	Vector3D v = p1b - p1a;

	// �������P(t) = p1 + t * v �����ʏ�ɂ��邽�߂̂������߂�
	// pn.x * (p1a.x + t(p1b.x - p1a.x)) + pn.y * (p1a.y + t(p1b.y - p1a.y)) 
	//		+ pn.z * (p1a.z + t(p1b.z - p1a.z)) + d = 0
	// 
	//		-(pn.x * p1a.x + pn.y * p1a.y + pn.z * p1a.z + d) 
	// t = ----------------------------------------------------
	//			 pn.x * v.x + pn.y * v.y + pn.z * v.z

	float denominator = pn.x * v.x + pn.y * v.y + pn.z * v.z;
	if (denominator == 0.0f) {
		return false;
	}

	t = -a / denominator;

	// t��0����1�͈̔͊O�ł���΁A��_�͐�����ɑ��݂��Ȃ�
	if (t < 0.0f || t > 1.0f) {
		return false;
	}

	// ��_�̌v�Z�i������̓_�̃p�����[�^�\����t�����j
	h.x = p1a.x + t * v.x;
	h.y = p1a.y + t * v.y;
	h.z = p1a.z + t * v.z;

	return true;
}

//--------------------------------------------------------
// ���ԌN�Y
//--------------------------------------------------------

//--------------------------------------------------------
// @brief �_�Ɛ�`�̓����蔻��
// @param v1 �����x�N�g��
// @param v2 �����x�N�g��
// @param rad �p�x
// @return �Փ˂��Ă��邩�ǂ���
//--------------------------------------------------------
bool Collision3D::CollisionPointAndFan(Vector3D v1, Vector3D v2, float rad)
{
	//���ς̌v�Z
	v1 = v1.Normalize();
	v2 = v2.Normalize();
	float dot = v1.Dot(v2);
	//���ς̌v�Z���o�O��Ȃ��悤��
	if (dot < 0.0000001 && dot > -0.0000001) { return false; }
	if (dot > Math::DegToRad(rad))
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------
// @brief ���ʍ��W�n���f�J���g���W�n�ɕϊ�
// @param angle �����x�N�g��
// @param radius ���ʂ̒��S�_����̔��a
// @return �ϊ�����
//--------------------------------------------------------
Vector3D Collision3D::ConvertToCartesian(Vector3D angle, float radius)
{
	Vector3D temp;
	//���ʍ��W�n���f�J���g���W�n�ɕϊ����邽�߂ɕK�v�ȗv�f�͔��a(radius),�����p�x(angle��x����),�����p�x(angle��y����)
	temp.x = radius * cosf(angle.x) * sinf(angle.y);
	temp.y = radius * sinf(angle.x);
	temp.z = radius * cosf(angle.x) * cosf(angle.y);
	return temp;
}
