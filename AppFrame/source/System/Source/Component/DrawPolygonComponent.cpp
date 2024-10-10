//----------------------------------------------------------------------
// @filename DrawPolygonComponent.h
// @author: Fukuma Kyohei
// @explanation
// �|���S���`��p�R���|�[�l���g
//----------------------------------------------------------------------
#include "../../Header/Component/DrawPolygonComponent.h"
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param owner �I�[�i�[
// @param updateowder �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
DrawPolygonComponent::DrawPolygonComponent(ObjectBase* owner, int updateowder) :DrawComponent(owner, updateowder)
{
	mUseFlag = false;
	mPlayTotalTime = 0.0;
	mColorAlpha = 255;
	mVertexCnt = 0;
	mIndexCnt = 0;
	mColor = GetColorU8(255, 255, 255,255);
	mNowPlayTime = 0.0f;
	mVertex.clear();
	mIndex.clear();
}

//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return �Ȃ�
//----------------------------------------------------------------------
DrawPolygonComponent::~DrawPolygonComponent()
{
	mVertex.clear();
	mIndex.clear();
}

//----------------------------------------------------------------------
// @brief �X�V����
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawPolygonComponent::Update()
{
	SetUseLighting(false);
	if (!mUseFlag) { return; }
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mColorAlpha);
	DrawPolygonIndexed3D(mVertex.data(), mVertexCnt, mIndex.data(), mIndexCnt, DX_NONE_GRAPH, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetUseLighting(true);

}

//----------------------------------------------------------------------
// @brief ���_�̐ݒ�
// @param vertex ���_���X�g
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawPolygonComponent::SetVertex(const std::vector<VERTEX3D>& vertex)
{
	this->mVertex = vertex;
	this->mVertexCnt = static_cast<int>(vertex.size());
}

//----------------------------------------------------------------------
// @brief ���_�C���f�b�N�X�̐ݒ�
// @param vertex ���_�̃C���f�b�N�X���X�g
// @return �Ȃ�
//----------------------------------------------------------------------
void DrawPolygonComponent::SetIndex(const std::vector<unsigned short>& index)
{
	this->mIndex = index;
	this->mIndexCnt = static_cast<int>(index.size()) / 3;
}
