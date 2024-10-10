//----------------------------------------------------------------------
// @filename DrawPolygonComponent.h
// @author: Fukuma Kyohei
// @explanation
// �|���S���`��p�R���|�[�l���g
//----------------------------------------------------------------------
#pragma once
#include "../Math/Vector3D.h"
#include "DrawComponent.h"
#include <vector>
class DrawPolygonComponent : public DrawComponent
{
public:
	DrawPolygonComponent(class ObjectBase* owner, int updateowder = 250);
	virtual ~DrawPolygonComponent();
	void Update()override;
	//�Q�b�^�[
	bool GetUseFlag() const { return mUseFlag; }
	std::vector<VERTEX3D> GetVertex() const { return mVertex; }
	std::vector<unsigned short> GetIndex() const { return mIndex; }
	float GetTotalTime() const { return mPlayTotalTime; }
	float GetPlayTime() const { return mNowPlayTime; }
	COLOR_U8 GetColor() const { return mColor; }
	int GetAlpha() const { return mColorAlpha; }
	//�Z�b�^�[
	void SetUseFlag(bool flag) { mUseFlag = flag; }
	void SetVertex(const std::vector<VERTEX3D>& vertex);
	void SetIndex(const std::vector<unsigned short>& index);
	void SetAlpha(int alpha){ mColorAlpha = alpha; }
	void SetTotalTime(float time) { mPlayTotalTime = time; }
	void SetPlayTime(float time) { mNowPlayTime = time; }
protected:
	//�g�p�\�t���O
	bool mUseFlag;
	//�|���S���`��̍ۂɎg���\����
	std::vector<VERTEX3D> mVertex;
	int mVertexCnt;
	//���_�C���f�b�N�X�z��
	std::vector<unsigned short> mIndex;
	int mIndexCnt;
	//���Đ�����
	float mPlayTotalTime;
	//���Đ�����
	float mNowPlayTime;
	//�J���[
	COLOR_U8 mColor;
	//���l
	int mColorAlpha;
};

