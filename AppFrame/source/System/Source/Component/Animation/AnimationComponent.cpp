//----------------------------------------------------------------------
// @filename AnimationManager.cpp
// @author: Morozumi Hiroya Saito Ko
// @explanation
// キャラクターのアニメーションを管理するクラス
// AnimationItemを追加・削除し、アニメーションの管理を行う
//----------------------------------------------------------------------
#include "../../../Header/Component/Animation/AnimationComponent.h"
#include "../../../Header/Component/Object/ObjectBase.h"
#include "../../../../File/CFile/CFile.h"
#include "../../../../Application/UtilMacro.h"
#include "dxlib.h"

std::map<CHARA_NAME, ANIM_MAP> AnimationComponent::_allCharaAnimMap;

//----------------------------------------------------------------------
// @brief コンストラクタ
// @return なし
//----------------------------------------------------------------------
AnimationComponent::AnimationComponent(const std::string& charaName, int modelHandle, int* stateNum ,const std::string& filePath, ObjectBase* owner, int updateowder) 
: Component(owner, updateowder),
_stateNum(stateNum),
_modelHandle(modelHandle),
_playingAnimStateNum(-1),
_playTime(0.0f),
_targetAnimMap(nullptr),
_latestAnimItem(nullptr)
{
	InitMap(charaName, modelHandle, filePath);
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
AnimationComponent::~AnimationComponent()
{
	for (auto itr = _animContainer.begin(); itr != _animContainer.end(); ++itr)
	{
		delete (*itr);
		(*itr) = nullptr;
	}
	_animContainer.clear();
	_targetAnimMap = nullptr;
}
//----------------------------------------------------------------------
// @brief アニメーション情報用マップコンテナの初期設定を行う
//             既に同じキャラクター名が登録されている場合は、同一のマップを使用する
// @param charaName キャラクター名
// @param modelHandle モデルハンドル
// @param fileName モーションリストファイル名
// @return なし
//----------------------------------------------------------------------
void AnimationComponent::InitMap(const std::string& charaName, int modelHandle,const std::string& fileName)
{
	auto itr = _allCharaAnimMap.find(charaName);
	if (itr == _allCharaAnimMap.end()) {
		std::string filePath = "Data/MotionList/" + fileName;

		// csvファイルを読み込む
		CFile file(filePath);
		// ファイルが開けた場合
		if (file.Success()) {
			const char* data = (const char*)file.Data();
			int c = 0;
			int size = file.Size();
			int stateNo = 0;
			while (c < size) {
				std::string motionName;
				int loopTimes = 0;
				// モーション名を取得
				c += GetString(&data[c], &motionName);
				// カンマの位置を見つける
				c += FindString(&data[c], ',', &data[size]); c++;
				// ループ回数を取得
				c += GetDecNum(&data[c], &loopTimes);
				// 改行などスキップ
				c += SkipSpace(&data[c], &data[size]);

				ANIMATION_INFO info{};
				info.animIndex = MV1LoadModel(motionName.c_str());
				info.loopTimes = loopTimes;
				_allCharaAnimMap[charaName][stateNo] = info;
				stateNo++;
#ifdef _DEBUG
				if (info.animIndex == -1) {
					std::string message = "[" + motionName + "] アニメーションが見つかりませんでした";
					MessageBox(NULL, message.c_str(), "エラー", MB_OK);
				}
#endif // _DEBUG
			}
		}
#ifdef _DEBUG
		else {
			// ファイルが開けなかった場合
			MessageBox(NULL, "ファイルが開けませんでした", "エラー", MB_OK);
		}
#endif // _DEBUG
	}
	_targetAnimMap = &_allCharaAnimMap[charaName];
	_modelHandle = modelHandle;
}
//----------------------------------------------------------------------
// @brief アニメーション情報用マップコンテナの初期設定を行う
//             既に同じキャラクター名が登録されている場合は、同一のマップを使用する
// @param charaName キャラクター名
// @param modelHandle モデルハンドル
// @param motionList モーション名の配列
// @return なし
//----------------------------------------------------------------------
void AnimationComponent::InitMap(CHARA_NAME charaName, int modelHandle, const std::vector<MotionNamePair>& motionList)
{
	auto itr = _allCharaAnimMap.find(charaName);
	// 既に同じキャラクター名が登録されている場合は、同一のマップを使用する
	if (itr == _allCharaAnimMap.end()) {
		for (auto it = motionList.begin(); it != motionList.end(); ++it) {
			ANIMATION_INFO info{};
			info.animIndex = MV1GetAnimIndex(modelHandle, it->first.c_str());
			info.loopTimes = it->second;
			_allCharaAnimMap[charaName][static_cast<int>(it - motionList.begin())] = info;
#ifdef _DEBUG
			if (info.animIndex == -1) {
				std::string message = "[" + it->first + "] アニメーションが見つかりませんでした";

				MessageBox(NULL, message.c_str(), "エラー", MB_OK);
			}
#endif // _DEBUG
		}
	}
	_targetAnimMap = &_allCharaAnimMap[charaName];
	_modelHandle = modelHandle;
}
//----------------------------------------------------------------------
// @brief アニメーションアイテムを追加する
// @param statusNo モーションの状態
// @return なし
//----------------------------------------------------------------------
void AnimationComponent::AddAnimationItem()
{
	// 引数statusNoに対応するアニメーション情報が存在するか調べる
	auto itr = (*_targetAnimMap).find((*_stateNum));
	// アニメーション情報が存在する場合
	if (itr != (*_targetAnimMap).end())
	{
		AnimationItem* anim = new AnimationItem();

		ANIMATION_INFO info = itr->second;
		int attachIndex = MV1AttachAnim(_modelHandle, 0, info.animIndex, FALSE);
		float totalTime = MV1GetAttachAnimTotalTime(_modelHandle, attachIndex);
		int loopTimes = info.loopTimes;

		anim->Setup((*_stateNum), attachIndex, totalTime, loopTimes);
		_animContainer.push_back(anim);
		_latestAnimItem = anim;
	}
}
//----------------------------------------------------------------------
// @brief アニメーションの再生処理
// @param statusNo モーションの状態
// @return なし
//----------------------------------------------------------------------
void AnimationComponent::Process()
{
	// 再生するアニメーションが変わった場合
	if (_playingAnimStateNum != (*_stateNum)) {
		// アタッチされているアニメーションに閉じ時間を設定する（モーションブレンド用）
		for (auto itrItem = _animContainer.begin(); itrItem != _animContainer.end();)
		{
			// モーションを3つ以上ブレンドしないために、古いアニメーションを削除する
			if ((*itrItem)->_stateNo != _playingAnimStateNum) {
				// アニメーションをデタッチする
				MV1DetachAnim(_modelHandle, (*itrItem)->_attachIndex);
				// このアニメーションアイテムを削除
				delete (*itrItem);
				itrItem = _animContainer.erase(itrItem);
				continue;
			}

			if ((*itrItem)->_closeTime == 0.0f) {
				// 閉じ時間を設定する
				(*itrItem)->_closeTotalTime = 6.0f;
				(*itrItem)->_closeTime = (*itrItem)->_closeTotalTime;
			}
			++itrItem;
		}

		// アニメーション番号を更新する
		_playingAnimStateNum = (*_stateNum);
		// アニメーションアイテムを追加する
		AddAnimationItem();
	}

	// 最後に追加された（最新の）アニメーションアイテムの再生時間を取得する
	_playTime = _latestAnimItem->_playTime;

	// アニメーションの再生時間を進める
	for (auto itrItem = _animContainer.begin(); itrItem != _animContainer.end(); )
	{
		// 再生時間をセットする
		MV1SetAttachAnimTime(_modelHandle, (*itrItem)->_attachIndex, (*itrItem)->_playTime);

		/* 再生時間の更新処理 */
		// 閉じ時間が設定されていない場合
		if ((*itrItem)->_closeTime == 0.0f) {
			// 再生時間を進める
			(*itrItem)->_playTime += 1.0f;

			// アニメーション再生開始時のモーションブレンド
			if((*itrItem)->_openTime < (*itrItem)->_openTotalTime){
				(*itrItem)->_openTime += 1.0f;
				// ブレンド率を変更する
				MV1SetAttachAnimBlendRate(_modelHandle, (*itrItem)->_attachIndex, (*itrItem)->_openTime / (*itrItem)->_openTotalTime);
			}
			
			// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
			if ((*itrItem)->_playTime > (*itrItem)->_totalTime) {
				// ループ再生をする場合
				if ((*itrItem)->_loopCnt > 1 || (*itrItem)->_loopCnt == 0) {
					if ((*itrItem)->_loopCnt > 1) {
						(*itrItem)->_loopCnt--;
					}
					// 再生時間を0に戻す
					(*itrItem)->_playTime = 0.0f;
				}
				// ループ再生をしない場合
				else {
					(*itrItem)->_playTime = (*itrItem)->_totalTime;
				}
			}
		}
		else {
			// アニメーション終了時のモーションブレンド

			// 閉じ時間を減らす
			(*itrItem)->_closeTime -= 1.f;

			// 閉じ時間が終わったか？
			if ((*itrItem)->_closeTime <= 0.f) {
				// アニメーションをデタッチする
				MV1DetachAnim(_modelHandle, (*itrItem)->_attachIndex);
				// このアニメーションアイテムを削除
				delete (*itrItem);
				itrItem = _animContainer.erase(itrItem);
				continue;
			}
			// ブレンド率を変更する
			MV1SetAttachAnimBlendRate(_modelHandle, (*itrItem)->_attachIndex, (*itrItem)->_closeTime / (*itrItem)->_closeTotalTime);
		}
		// 次のアニメーションアイテムへ
		++itrItem;
	}
}
//----------------------------------------------------------------------
// @brief デバッグ情報の描画
// @return なし
//----------------------------------------------------------------------
void AnimationComponent::DrawDebugInfo()
{
	int y = 100;
	int line = 0;

	DrawBox(0, y, 300, y + 16 * 3, GetColor(128, 128, 128), TRUE);
	DrawFormatString(0, y + line * 16, COLOR_BLUE, "PlayTime : %3.2f", _playTime); line++;

	for (auto itr = _animContainer.begin(); itr != _animContainer.end(); ++itr)
	{
		DrawFormatString(0, y + line * 16, COLOR_BLUE, "アニメーション番号 : %d", (*itr)->_stateNo);
		line++;
	}
}
