//----------------------------------------------------------------------
// @filename mydraw.h
// @author: Saito Ko 
// @explanation
// �s���p������]�ړ��g�傪�ł���`��֐����܂Ƃ߂��w�b�_�t�@�C��
//----------------------------------------------------------------------
#pragma once
#include "DxLib.h"		// VECTOR��MATRIX���`�Ƃ��Ďg�����߁A.h�ɓ���Ă���
#include "../Function/Easing.h"
#include "../../Header/Collision/MyStructure.h"

// �摜�̒��S�ŉ�]���ĕ`�悷��
void MyDrawModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle);

// �摜�̒��S�ŉ�]���ĕ`�悷��(���E���]��)
void MyDrawTurnModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle);

// 4�_���w�肵�Ďl�p��`��
void MyDraw4PointBox(MATRIX mView, VECTOR pos[4], unsigned int Color, int FillFlag);

// ��`��`��
void MyDrawBox(MATRIX mView, float x1, float y1, float x2, float y2, unsigned int Color, int FillFlag);

void MyDrawExtendGraph(MATRIX mView, float x1, float y1, float x2, float y2, unsigned int handle, int FillFlag);

void MyDrawDeformationGraph(MATRIX mView, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float direction, int handle, int FillFlag);

void MyDrawRect(MATRIX mView, MYRECT_PLUS rc, unsigned int Color, int FillFlag);

void MyDrawLine(MATRIX mView, float x1, float y1, float x2, float y2, int Color);

void MyDrawCircle(MATRIX mView, float x, float y, float r);

// �ʒu�𑵂��ĕ������`��
// posBaseX = -1:������, 0:����, 1:�E����
void DrawPosString(int x, int y, int posBaseX, unsigned int color, const char* str);

//�L����������h��Ԃ�
void PortalIn(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int GrHandle, int Color, int turn, float param);