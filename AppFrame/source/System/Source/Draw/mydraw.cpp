//----------------------------------------------------------------------
// @filename mydraw.cpp
// @author: Saito Ko 
// @explanation
// �s���p������]�ړ��g�傪�ł���`��֐����܂Ƃ߂��w�b�_�t�@�C��
//----------------------------------------------------------------------
#include "../../Header/Draw/mydraw.h"

//----------------------------------------------------------------------
// @brief �摜�̒��S�ŉ�]���ĕ`�悷��
// @param mView �r���[�s��
// @param position �ʒu
// @param zoom �g�嗦
// @param angle ��]�p�x
// @param width �摜�̕�
// @param height �摜�̍���
// @param cgHandle �摜�n���h��
// @return �Ȃ�
//----------------------------------------------------------------------
void _MyDrawModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle, int turn) {
	// ��]�~�g�k�~���s�ړ�
	MATRIX mRot = MGetRotZ(angle);						// 2D��x,y����]������ɂ́A3D�Ȃ�Z����]�ɂȂ�
	MATRIX mScale = MGetScale(VGet(zoom, zoom, 1));		// Z�����̔{����1�̂܂�
	MATRIX mTrans = MGetTranslate(position);
	MATRIX m;
	m = MMult(mRot, mScale);
	m = MMult(m, mTrans);

	m = MMult(m, mView);

	// �`�悷��摜��4�̒��_���W
	VECTOR pos[4] = {
		// �ʏ�p�i���ォ��E���j
		VGet(-width / 2.0f, -height / 2.0f, 0),	// ����
		VGet(width / 2.0f, -height / 2.0f,0),	// �E��
		VGet(width / 2.0f,  height / 2.0f ,0),	// �E��
		VGet(-width / 2.0f,  height / 2.0f ,0),	// ����
	};
	if(turn != 0) {
		// ���]�p
		VECTOR posTurn[4] = {
			// ���]�p�i�E�ォ�獶���j
			VGet(width / 2.0f, -height / 2.0f,0),	// �E��
			VGet(-width / 2.0f, -height / 2.0f, 0),	// ����
			VGet(-width / 2.0f,  height / 2.0f,0),	// ����
			VGet(width / 2.0f,  height / 2.0f,0),	// �E��
		};
		for(int i = 0; i < 4; i++) {
			pos[i] = posTurn[i];
		}
	}

	// 4�̒��_���W�S�Ăɍs����|���ĕϊ�����
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	// �ϊ��������W�ŕ`�悷��
	DrawModiGraphF(
		pos[0].x, pos[0].y,
		pos[1].x, pos[1].y,
		pos[2].x, pos[2].y,
		pos[3].x, pos[3].y,
		cgHandle, true);
}

//----------------------------------------------------------------------
// @brief �摜�̒��S�ŉ�]���ĕ`�悷��
// @param mView �r���[�s��
// @param position �ʒu
// @param zoom �g�嗦
// @param angle ��]�p�x
// @param width �摜�̕�
// @param height �摜�̍���
// @param cgHandle �摜�n���h��
// @return �Ȃ�
//----------------------------------------------------------------------
void MyDrawModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle) {
	// ���E���]���Ȃ�
	_MyDrawModiGraph(mView, position, zoom, angle, width, height, cgHandle, 0);
}

//----------------------------------------------------------------------
// @brief �摜�𔽓]���Ē��S�ŉ�]���`�悷��
// @param mView �r���[�s��
// @param position �ʒu
// @param zoom �g�嗦
// @param angle ��]�p�x
// @param width �摜�̕�
// @param height �摜�̍���
// @param cgHandle �摜�n���h��
// @return �Ȃ�
//----------------------------------------------------------------------
void MyDrawTurnModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle) {
	// ���E���]����
	_MyDrawModiGraph(mView, position, zoom, angle, width, height, cgHandle, 1);
}

//----------------------------------------------------------------------
// @brief 4�_���w�肵�Ďl�p��`��
// @param mView �r���[�s��
// @param pos 4�̒��_���W
// @param Color �F
// @param FillFlag �h��Ԃ��t���O
// @return �Ȃ�
//----------------------------------------------------------------------
void MyDraw4PointBox(MATRIX mView, VECTOR pos[4], unsigned int Color, int FillFlag) {
	MATRIX m = mView;

	// 4�̒��_���W�S�Ăɍs����|���ĕϊ�����
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}

	// �h��Ԃ����H
	if(FillFlag == 0) {
		// �ϊ��������W�ŁA���Ŏl�p��`�悷��
		DrawLineAA(
			pos[0].x, pos[0].y,	// ����
			pos[1].x, pos[1].y,	// �E��
			Color);
		DrawLineAA(
			pos[1].x, pos[1].y,	// �E��
			pos[3].x, pos[3].y,	// �E��
			Color);
		DrawLineAA(
			pos[3].x, pos[3].y,	// �E��
			pos[2].x, pos[2].y,	// ����
			Color);
		DrawLineAA(
			pos[2].x, pos[2].y,	// ����
			pos[0].x, pos[0].y,	// ����
			Color);
	}
	else {
		// �ϊ��������W�ŁA�O�p�`�Q��`�悷��
		DrawTriangleAA(
			pos[0].x, pos[0].y,	// ����
			pos[1].x, pos[1].y,	// �E��
			pos[2].x, pos[2].y,	// ����
			Color, FillFlag);
		DrawTriangleAA(
			pos[1].x, pos[1].y,	// �E��
			pos[2].x, pos[2].y,	// ����
			pos[3].x, pos[3].y,	// �E��
			Color, FillFlag);
	}
}

//----------------------------------------------------------------------
// @brief ��`��`��
// @param mView �r���[�s��
// @param x1 �����x���W
// @param y1 �����y���W
// @param x2 �E����x���W
// @param y2 �E����y���W
// @param Color �F
// @param FillFlag �h��Ԃ��t���O
// @return �Ȃ�
//----------------------------------------------------------------------
void MyDrawBox(MATRIX mView, float x1, float y1, float x2, float y2, unsigned int Color, int FillFlag) {
	VECTOR pos[4] = {
		VGet(x1,		y1,		0),	// ����
		VGet(x2 - 1,	y1,		0),	// �E��
		VGet(x1,		y2 - 1,	0),	// ����
		VGet(x2 - 1,	y2 - 1,	0),	// �E��
	};
	MyDraw4PointBox(mView, pos, Color, FillFlag);
}

//----------------------------------------------------------------------
// @brief �摜��ό`���ĕ`�悷��
// @param mView �r���[�s��
// @param x1 �����x���W
// @param y1 �����y���W
// @param x2 �E���x���W
// @param y2 �E���y���W
// @param x3 �E����x���W
// @param y3 �E����y���W
// @param x4 ������x���W
// @param y4 ������y���W
// @param direction ��]�p�x
// @param handle �摜�n���h��
// @param FillFlag �h��Ԃ��t���O
// @return �Ȃ�
//----------------------------------------------------------------------
void MyDrawDeformationGraph(MATRIX mView, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float direction, int handle, int FillFlag) {
	VECTOR pos[4] = {
		VGet(x1,		y1,		0),	// ����
		VGet(x2 - 1,	y2,		0),	// �E��
		VGet(x3,		y3 - 1,	0),	// ����
		VGet(x4 - 1,	y4 - 1,	0),	// �E��
	};
	MATRIX mRot = MGetRotZ(direction);
	MATRIX m = mView;
	//m = MMult(m, mRot);

	// 4�̒��_���W�S�Ăɍs����|���ĕϊ�����
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	DrawModiGraphF(pos[0].x, pos[0].y, pos[1].x, pos[1].y, pos[2].x, pos[2].y, pos[3].x, pos[3].y, handle, FillFlag);
}

//----------------------------------------------------------------------
// @brief �摜��ό`���ĕ`�悷��
// @param mView �r���[�s��
// @param x1 �����x���W
// @param y1 �����y���W
// @param x2 �E����x���W
// @param y2 �E����y���W
// @param handle �摜�n���h��
// @param FillFlag �h��Ԃ��t���O
// @return �Ȃ�
//----------------------------------------------------------------------
void MyDrawExtendGraph(MATRIX mView, float x1, float y1, float x2, float y2, unsigned int handle, int FillFlag) {
	VECTOR pos[4] = {
		VGet(x1,		y1,		0),	// ����
		VGet(x2 - 1,	y1,		0),	// �E��
		VGet(x1,		y2 - 1,	0),	// ����
		VGet(x2 - 1,	y2 - 1,	0),	// �E��
	};
	MATRIX m = mView;
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	DrawExtendGraphF(pos[0].x, pos[0].y, pos[3].x, pos[3].y, handle, FillFlag);
}

//----------------------------------------------------------------------
// @brief �����蔻��̕`��
// @param mView �r���[�s��
// @param rc �����蔻��̋�`
// @param Color �F
// @param FillFlag �h��Ԃ��t���O
// @return �Ȃ�
//----------------------------------------------------------------------
void MyDrawRect(MATRIX mView, MYRECT_PLUS rc, unsigned int Color, int FillFlag){
	MyDrawBox(mView, rc.x, rc.y, rc.x+rc.w, rc.y+rc.h, Color, FillFlag);
}

void MyDrawLine(MATRIX mView, float x1, float y1, float x2, float y2, int Color ) {
	VECTOR pos[] = {
		VGet(x1,		y1,		0),	// 1
		VGet(x2 - 1,	y2,		0),	// 2
	};
	MATRIX m = mView;
	for(int i = 0; i < 2; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	DrawLineAA(pos[0].x, pos[0].y, pos[1].x, pos[1].y, Color);
}

void MyDrawCircle(MATRIX mView, float x, float y, float r) {
	MATRIX m = mView;
	VECTOR pos;
	pos = VGet(x, y, 0);

	pos = VTransform(pos, m);

	DrawCircleAA(pos.x, pos.y, r, GetColor(0,168,0), TRUE);

}

//----------------------------------------------------------------------
// @brief �ʒu�𑵂��ĕ������`��
// @param x x���W
// @param y y���W
// @param posBaseX -1:������, 0:����, 1:�E����
// @param color �F
// @param str ������
// @return �Ȃ�
// ----------------------------------------------------------------------
void DrawPosString(int x, int y, int posBaseX, unsigned int color, const char* str) {
	int w = GetDrawStringWidth(str, static_cast<int>(strlen(str)));	// �`�悷�镶���̉��T�C�Y�𓾂�
	if(posBaseX == 0) {
		// ���������Ȃ̂�x�ʒu�����ɔ������炷
		x -= w / 2;
	}
	else if(posBaseX > 0) {
		// �E�����Ȃ̂�x�ʒu�����ɂ��炷
		x -= w;
	}
	DrawString(x, y, str, color);
}

//----------------------------------------------------------------------
// @brief �摜�̓h��Ԃ��`��
// @param mView �r���[�s��
// @param position �ʒu
// @param zoom �g�嗦
// @param angle ��]�p�x
// @param width �摜�̕�
// @param height �摜�̍���
// @param GrHandle �摜�n���h��
// @param Color �F
// @param turn ���]�t���O
// @param param �����x
// @return �Ȃ�
//----------------------------------------------------------------------
void PortalIn(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int GrHandle, int Color, int turn,float param)
{
	// ��]�~�g�k�~���s�ړ�
	MATRIX mRot = MGetRotZ(angle);						// 2D��x,y����]������ɂ́A3D�Ȃ�Z����]�ɂȂ�
	MATRIX mScale = MGetScale(VGet(zoom, zoom, 1));		// Z�����̔{����1�̂܂�
	MATRIX mTrans = MGetTranslate(position);
	MATRIX m;
	m = MMult(mRot, mScale);
	m = MMult(m, mTrans);
	m = MMult(m, mView);

	// �`�悷��摜��4�̒��_���W
	VECTOR pos[4] = {
		// �ʏ�p�i���ォ��E���j
		VGet(-width / 2.0f, -height / 2.0f, 0),	// ����
		VGet(width / 2.0f, -height / 2.0f,0),	// �E��
		VGet(width / 2.0f,  height / 2.0f,0),	// �E��
		VGet(-width / 2.0f,  height / 2.0f,0),	// ����
	};

	// 4�̒��_���W�S�Ăɍs����|���ĕϊ�����
	for (int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}

	// �y�o�b�t�@��L���ɂ���
	SetUseZBufferFlag(TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(param));


	// �y�o�b�t�@�ɉ摜�Ɠ����傫���̃}�X�N����������
	DrawBoxToZBuffer(static_cast<int>(pos[0].x),
		static_cast<int>(pos[0].y),
		static_cast<int>(pos[2].x),
		static_cast<int>(pos[2].y), TRUE, DX_ZWRITE_MASK);

	// �y�o�b�t�@�ɉ摜�̌`�Ń}�X�N�𙊂�т�
	DrawExtendGraphToZBuffer(static_cast<int>(pos[0].x),
		static_cast<int>(pos[0].y),
		static_cast<int>(pos[2].x),
		static_cast<int>(pos[2].y),
		GrHandle, DX_ZWRITE_CLEAR);

	// �摜�̑傫���̃{�b�N�X��`�悷��(�}�X�N������т���Ă���Ƃ��낵���h��Ԃ���Ȃ�)
	DrawBoxAA(pos[0].x, pos[0].y, pos[2].x, pos[2].y, Color, TRUE);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �y�o�b�t�@�𖳌��ɂ���
	SetUseZBufferFlag(FALSE);
}