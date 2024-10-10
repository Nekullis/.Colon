//----------------------------------------------------------------------
// @filename AnimationManager.h
// @author: Morozumi Hiroya Saito Ko
// @explanation
// キャラクターのアニメーションを管理するクラス
// AnimationItemを追加・削除し、アニメーションの管理を行う
//----------------------------------------------------------------------
#pragma once
#include "AnimationItem.h"
#include "MotionList.h"
#include "../Component.h"
#include <map>
#include <vector>

// アニメーション情報
// int : 各キャラクターのアニメーションステータス番号（enum型からint型にキャストしたもの）
// ANIMATION_INFO : アニメーション情報（AnimationItem.hで定義）
typedef std::map<int, ANIMATION_INFO> ANIM_MAP;

typedef std::string CHARA_NAME;

class AnimationComponent : public Component
{
public:	

	AnimationComponent(const std::string& charaName, int modelHandle, int* stateNum ,const std::string& filePath, class ObjectBase* owner , int updateOwder);
	~AnimationComponent();

	// --------------------------------------------------------------------------------------------
	// アニメーション情報用マップコンテナの初期設定を行う
	// 既に同じキャラクター名が登録されている場合は、同一のマップを使用する

	// @param charaName キャラクター名
	// @param modelHandle モデルハンドル
	// @param fileName モーションリストファイル名
	void InitMap(const std::string& charaName , int modelHandle, const std::string& fileName);

	// @param charaName キャラクター名
	// @param modelHandle モデルハンドル
	// @param motionList モーション名の配列
	void InitMap(CHARA_NAME charaName, int modelHandle, const std::vector<MotionNamePair>& motionList);
	// --------------------------------------------------------------------------------------------

	// アニメーションの更新処理
	void Process();

	// 最後に追加された（最新の）アニメーションの再生時間を取得する
	float GetPlayTime() const { return _playTime; }

	// デバッグ情報の描画
	void DrawDebugInfo();

private:
	// アニメーションアイテムを追加する
	void AddAnimationItem();

	// 全キャラクターのアニメーション情報用マップコンテナ
	// 同種のキャラクターのアニメーション情報を共有するため、キャラクター名をキーにしてマップを保持する
	static std::map<CHARA_NAME, ANIM_MAP> _allCharaAnimMap;

	// アニメーション情報用マップコンテナ
	// _allCharaAnimMapから指定したキャラクターのアニメーション情報を取得するためのマップ
	// キー : int型 キャラクターのステータス番号
	// バリュー : ANIMATION_INFO型 アニメーション情報
	ANIM_MAP* _targetAnimMap;

	// モデルハンドル
	int _modelHandle;

	// アニメーションの番号
	int* _stateNum;
	// 再生中アニメーションのステータス番号
	int _playingAnimStateNum;

	// アニメーションアイテム
	std::vector<AnimationItem*> _animContainer;

	// 最後に追加された（最新の）アニメーションアイテム
	AnimationItem* _latestAnimItem;
	// 最後に追加された（最新の）アニメーションの再生時間
	float _playTime;
};