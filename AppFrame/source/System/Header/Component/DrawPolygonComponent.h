//----------------------------------------------------------------------
// @filename DrawPolygonComponent.h
// @author: Fukuma Kyohei
// @explanation
// ポリゴン描画用コンポーネント
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
	//ゲッター
	bool GetUseFlag() const { return mUseFlag; }
	std::vector<VERTEX3D> GetVertex() const { return mVertex; }
	std::vector<unsigned short> GetIndex() const { return mIndex; }
	float GetTotalTime() const { return mPlayTotalTime; }
	float GetPlayTime() const { return mNowPlayTime; }
	COLOR_U8 GetColor() const { return mColor; }
	int GetAlpha() const { return mColorAlpha; }
	//セッター
	void SetUseFlag(bool flag) { mUseFlag = flag; }
	void SetVertex(const std::vector<VERTEX3D>& vertex);
	void SetIndex(const std::vector<unsigned short>& index);
	void SetAlpha(int alpha){ mColorAlpha = alpha; }
	void SetTotalTime(float time) { mPlayTotalTime = time; }
	void SetPlayTime(float time) { mNowPlayTime = time; }
protected:
	//使用可能フラグ
	bool mUseFlag;
	//ポリゴン描画の際に使う構造体
	std::vector<VERTEX3D> mVertex;
	int mVertexCnt;
	//頂点インデックス配列
	std::vector<unsigned short> mIndex;
	int mIndexCnt;
	//総再生時間
	float mPlayTotalTime;
	//現再生時間
	float mNowPlayTime;
	//カラー
	COLOR_U8 mColor;
	//α値
	int mColorAlpha;
};

