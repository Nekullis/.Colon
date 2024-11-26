//----------------------------------------------------------------------
// @filename MyStructure.cpp
// @author: Saito Ko 
// @explanation
// �R���W��������Ŏg�p����N���X��\���̂��`����t�@�C��
//----------------------------------------------------------------------
#include "../../Header/Collision/MyStructure.h"

// �`�揈��
//----------------------------------------------------------------------
// @brief Sphere�̕`�揈��
// @param �`��F
// @return �Ȃ�
//----------------------------------------------------------------------
void Sphere::Render(unsigned int color)
{
	DrawSphere3D(pos.toVECTOR(), r, 64, color, color, false);
}

//----------------------------------------------------------------------
// @brief ��]����
//             x��->y��->z���̏��Ԃ�, �e������]������
// @param vRot ��]�p�x
// @return �Ȃ�
//----------------------------------------------------------------------
void OBB::Rotate(Vector3D vRot)
{
	MATRIX m = MGetRotX(vRot.x);
	m = MMult(m, MGetRotY(vRot.y));
	m = MMult(m, MGetRotZ(vRot.z));

	Vector3D d[3] = {
	 Vector3D(1.0f, 0.0f, 0.0f),
	 Vector3D(0.0f, 1.0f, 0.0f),
	 Vector3D(0.0f, 0.0f, 1.0f)
	};

	for (int i = 0; i < 3; i++) {
		dir_vec[i] = VTransform(d[i].toVECTOR(), m);
	}
}

//----------------------------------------------------------------------
// @brief ���_���W�̎擾
// @param vertexPosList ���_���W���X�g
// @return �Ȃ�
//----------------------------------------------------------------------
void OBB::GetVertexPos(std::vector<Vector3D>& vertexPosList)
{
	Vector3D vDiff[3];
	for (int i = 0; i < 3; i++) {
		vDiff[i] = dir_vec[i] * (length[i] / 2.0f);
	}

	Vector3D vPos[8];
	vPos[0] = pos + vDiff[0] + vDiff[1] + vDiff[2];
	vPos[1] = pos + vDiff[0] + vDiff[1] + (vDiff[2] * -1.0f);
	vPos[2] = pos + vDiff[0] + (vDiff[1] * -1.0f) + vDiff[2];
	vPos[3] = pos + vDiff[0] + (vDiff[1] * -1.0f) + (vDiff[2] * -1.0f);

	vPos[4] = pos + (vDiff[0] * -1.0f) + vDiff[1] + vDiff[2];
	vPos[5] = pos + (vDiff[0] * -1.0f) + vDiff[1] + vDiff[2] * -1.0f;
	vPos[6] = pos + (vDiff[0] * -1.0f) + (vDiff[1] * -1.0f) + vDiff[2];
	vPos[7] = pos + (vDiff[0] * -1.0f) + (vDiff[1] * -1.0f) + (vDiff[2] * -1.0f);

	for (int i = 0; i < 8; i++) {
		vertexPosList.push_back(vPos[i]);
	}
}

//----------------------------------------------------------------------
// @brief OBB�̕`�揈��
// @param color �`��F
// @return �Ȃ�
//----------------------------------------------------------------------
void OBB::Render(unsigned int color)
{
	for (int i = 0; i < 3; i++) {
		Vector3D vDiff = dir_vec[i]* (length[i] / 2.0f);

		Vector3D pos1 = pos+ (vDiff* -1.0f);
		Vector3D pos2 = pos+ vDiff;

		int vecIndex1 = (i + 1) % 3;
		int vecIndex2 = (i + 2) % 3;

		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				int vecSign1 = j == 0 ? -1 : 1;
				int vecSign2 = k == 0 ? -1 : 1;
				MATRIX m = MGetTranslate((dir_vec[vecIndex1]* (length[vecIndex1] / 2.0f * vecSign1)).toVECTOR());
				m = MMult(m, MGetTranslate((dir_vec[vecIndex2]* (length[vecIndex2] / 2.0f * vecSign2)).toVECTOR()));

				VECTOR linePos1 = VTransform(pos1.toVECTOR(), m);
				VECTOR linePos2 = VTransform(pos2.toVECTOR(), m);

				DrawLine3D(linePos1, linePos2, color);
			}
		}
	}
}

//----------------------------------------------------------------------
// @brief �J�v�Z���̕`�揈��
// @param color �`��F
// @return �Ȃ�
//----------------------------------------------------------------------
void Capsule::Render(unsigned int color)
{
	DrawCapsule3D(pos.toVECTOR(), up_pos.toVECTOR(), r, 16, color, color, false);
}