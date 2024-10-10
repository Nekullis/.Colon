//----------------------------------------------------------------------
// @filename DrawPolygonComponent.h
// @author: Fukuma Kyohei
// @explanation
// ポリゴン描画用コンポーネント
//----------------------------------------------------------------------
#include "../../Header/Component/DrawPolygonComponent.h"
#include "../../Header/Component/Object/ObjectBase.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @param owner オーナー
// @param updateowder 更新順番
// @return なし
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
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
DrawPolygonComponent::~DrawPolygonComponent()
{
	mVertex.clear();
	mIndex.clear();
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
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
// @brief 頂点の設定
// @param vertex 頂点リスト
// @return なし
//----------------------------------------------------------------------
void DrawPolygonComponent::SetVertex(const std::vector<VERTEX3D>& vertex)
{
	this->mVertex = vertex;
	this->mVertexCnt = static_cast<int>(vertex.size());
}

//----------------------------------------------------------------------
// @brief 頂点インデックスの設定
// @param vertex 頂点のインデックスリスト
// @return なし
//----------------------------------------------------------------------
void DrawPolygonComponent::SetIndex(const std::vector<unsigned short>& index)
{
	this->mIndex = index;
	this->mIndexCnt = static_cast<int>(index.size()) / 3;
}
