//----------------------------------------------------------------------
// @filename AnimationItem.cpp
// @date: 2024/02/07
// @author: Morozumi Hiroya Saito Ko
// @explanation
// キャラクターのアニメーション情報を保持するクラス
// AnimationManagerクラスで、このクラスのインスタンスを追加・削除し、アニメーションの管理を行う
//----------------------------------------------------------------------
#include "../../../Header/Component/Animation/AnimationItem.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @return なし
//----------------------------------------------------------------------
AnimationItem::AnimationItem()
{
	_stateNo = -1;

	_attachIndex = -1;
	_totalTime = 0.0f;
	_playTime = 0.0f;

	_openTime = 0.0f;
	_openTotalTime = 0.0f;

	_closeTotalTime = 0.0f;
	_closeTime = 0.0f;

	_loopCnt = 0;
}
//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
AnimationItem::~AnimationItem()
{
}
//----------------------------------------------------------------------
// @brief 初期化処理
// @param animIndex アニメーション番号
// @param attachIndex アタッチ番号
// @param totalTime アニメーションの総時間
// @param loopTimes ループ回数
// @return なし
//----------------------------------------------------------------------
void AnimationItem::Setup(int animIndex, int attachIndex, float totalTime, int loopTimes)
{
	_stateNo = animIndex;

	_attachIndex = attachIndex;
	_totalTime = totalTime;
	_playTime = 0.0f;

	_openTime = 0.0f;
	_openTotalTime = 6.0f;

	_closeTotalTime = 0.0f;
	_closeTime = 0.0f;

	_loopCnt = loopTimes;
}
