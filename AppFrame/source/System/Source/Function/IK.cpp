//----------------------------------------------------------------------
// @filename IK.cpp
// @author: Kawai Daisuke
// @explanation
// �t�^���w��p����IK�̌v�Z���s���N���X
//----------------------------------------------------------------------
#include "../../Header/Function/IK.h"
#include "../../Header/Math/Vector3D.h"
#include "../../Header/Collision/3DCollision.h"

//----------------------------------------------------------------------
// @brief 1�{�[��IK
// @param targetPos �ڕW�ʒu
// @param bonePos �{�[���̈ʒu
// @param boneDir �{�[���̌���
// ----------------------------------------------------------------------
void IK::OneBoneIK(Vector3D targetPos, Vector3D& bonePos, Vector3D& boneDir) {

    // �@IK�̖ڕW�ʒu�����[�J���ɕϊ�
    Vector3D localTargetPos = targetPos - bonePos;
    // ���K�����ĕ����x�N�g���ɂ���
    Vector3D localTargetDir = localTargetPos.Normalize();

    // sq = squared�̗��ŁA2���\��
    float sqX = localTargetPos.x * localTargetPos.x;
    float sqY = localTargetPos.y * localTargetPos.y;
    float sqZ = localTargetPos.z * localTargetPos.z;

    // �O�����̒藝�Ńx�N�g���̒��������߂�
    float length = sqrtf(sqX + sqY + sqZ);


    // �A���[�J�����W����O�p���p����sin��z, cos��z, sin��y, cos��y���v�Z
    // 2.1 ���[�p���v�Z����
    // DxLib��Y-up�Ȃ̂�sin��y, cos��y���v�Z����(Z-up����sin��z, cos��z�ɂȂ�)
    float cosTY = localTargetPos.x / sqrtf(sqX + sqZ);
    float sinTY = localTargetPos.z / sqrtf(sqX + sqZ);

    // 2.2 �s�b�`�p���v�Z����
    // sin��x, cos��x���v�Z����
    float cosTZ = sqrtf(sqX + sqZ) / length;
    float sinTZ = localTargetPos.y / length;


    // �B�{�[���̌��������߂�
    // 3.1 ���[���̉�]�s������
    // �O���[�o����Y���i������j
    Vector3D yawAxis = VGet(0.0f, 1.0f, 0.0f);
    if (localTargetDir.x == 0.0f && localTargetDir.z == 0.0f) {
        yawAxis = VGet(1.0f, 0.0f, 0.0f); // ����P�[�X: �ڕW��Y���ɉ����Ă���ꍇ�AX������]���ɂ���
    }
    MATRIX rotationYaw = MGetRotAxis(yawAxis.toVECTOR(), atan2f(sinTY, cosTY));

    // 3.2 �s�b�`���̉�]�s������
    // �O���[�o����X���i�E�����j
    Vector3D pitchAxis = VGet(1.0f, 0.0f, 0.0f);
    MATRIX rotationPitch = MGetRotAxis(pitchAxis.toVECTOR(), atan2f(sinTZ, cosTZ));

    // �{�[���̕������X�V
    // �����K�����[���s�b�`�̏��ԂŊ|����
    boneDir = VTransform(boneDir.toVECTOR(), rotationYaw);
    boneDir = VTransform(boneDir.toVECTOR(), rotationPitch);
}

//----------------------------------------------------------------------
// @brief 2�{�[��IK
// @param targetPos �ڕW�ʒu
// @param joint1Pos ���֐߂̈ʒu
// @param joint1Dir ���֐߂̌���
// @param joint2Pos ���֐߂̈ʒu
// @param joint2Dir ���֐߂̌���
// @param bone1Length ���{�[���̒���
// @param bone2Length ���{�[���̒���
// ----------------------------------------------------------------------
void IK::TwoBoneIK(Vector3D targetPos, Vector3D& joint1Pos, Vector3D& joint1Dir,
    Vector3D& joint2Pos, Vector3D& joint2Dir, float bone1Length, float bone2Length) {

    Vector3D Line = targetPos - joint1Pos;
    float LineLength = Line.Len();

    // �@1�{�[��IK���g���đ��֐߂�ڕW�ʒu�Ɍ�����
    OneBoneIK(targetPos, joint1Pos, joint1Dir);

    // �A���֐߂̐i�s��������Ƃ��đ��֐߂̉�]����@���Ƃ��镽�ʂ����
    Vector3D planeNormal = joint1Dir.Cross(targetPos - joint1Pos);
    planeNormal = planeNormal.Normalize(); // �@���̐��K��

    // ��������͑��֐߂����֐߂���̖@�������Ƃ����P����]�����邽�߁A�Q�����̖��Ƃ��Ĉ���
    // �B���֐߂̐�[���ڕW�ʒu�Ɍ����悤�ɓ�{�̊֐߂���]�����āA�O�p�`�����  
    // 3.1�O�p�`�̊e�ӂ́A���ꂼ��bone1Length, bone2Length, Line�̒��������̂�
    // ��a��bone1Length�A��b��bone2Length�A��c��Line�Ƃ��ė]���藝���g����cosB,C�����߂�
    float sqA = bone1Length * bone1Length;
    float sqB = bone2Length * bone2Length;
    float sqC = LineLength * LineLength;

    float cosB = (sqA + sqC - sqB) / (2 * bone1Length * LineLength);
    Collision3D::clamp1m1(cosB); // -1�`1�͈̔͂ɃN�����v
    float sinB = sqrtf(1 - cosB * cosB);

    float cosC = (sqA + sqB - sqC) / (2 * bone1Length * bone2Length);
    Collision3D::clamp1m1(cosC); // -1�`1�͈̔͂ɃN�����v
    float sinC = sqrtf(1 - cosC * cosC);

    // 3.3��]�����ɂ��čl����O�ɁA��2�֐߂̉�]�p���]���藝�ŋ��߂��O�p�`abc�̓��pC�ł͂Ȃ��A
    // ���ۂɂ͊O�p�̃�-C�ƂȂ��Ă���_�ɂ��čl�����Ȃ���΂Ȃ�܂���B
    // �Ƃ����Ă��A�����͈ȉ��̌����ɂ���������cosC�̕����𔽓]���邾���ō\���܂���BsinC�̒l�͂��̂܂܂ł��B
    cosC = -cosC; // �O�p�␳

    // �C��]��������sin�ɂ����������߂�
    // ��]�����������v���̏ꍇ�͐������̉�]�ŁA���v���̏ꍇ�͕������̉�]�ƂȂ�B
    // ��]�����̐�����sin�Ƃ̐��������ŕ\���ł���̂ŁAcos�̕����͕ω����Ȃ��B
    // �����ŁAsin�Ƃ̐����͊O�ς��g���ċ��߂邱�Ƃ��ł���B
    // �����ŁA�O�ς̌��ʂ����̏ꍇ��sin�Ƃ����A���̏ꍇ��sin�Ƃ����ƂȂ�B
    if (joint1Dir.Cross(targetPos - joint1Pos).Len() < 0) {
        sinB = -sinB;
    }

    // �D����ꂽcos, sin�̑g�ݍ��킹�ŁA�e�֐߂���]������
    // joint1�̐V���������x�N�g�����v�Z
    MATRIX rotationB = MGetRotAxis(planeNormal.toVECTOR(), atan2f(sinB, cosB));
    joint1Dir = VTransform(joint1Dir.toVECTOR(), rotationB);
    joint1Dir = joint1Dir.Normalize(); // ���K��

    // joint2�̈ʒu���v�Z
    joint2Pos = joint1Pos + joint1Dir * bone1Length;
    // joint2�̐V���������x�N�g�����v�Z
    MATRIX rotationC = MGetRotAxis(planeNormal.toVECTOR(), atan2f(sinC, cosC));
    joint2Dir = VTransform(joint1Dir.toVECTOR(), rotationC);
    joint2Dir = joint2Dir.Normalize(); // ���K��
}