//----------------------------------------------------------------------
// @filename MotionList.cpp
// @author: Morozumi Hiroya Saito Ko
// @explanation
// 各キャラクターのモーションリストを管理するクラス
// AnimationManagerクラス及びFrameDataクラスの初期化処理で必要な情報を管理する
// "Data/MotionList/MotionList_〇〇.csv" から、各キャラクターのモーション一覧を読み込む（○○の部分にはキャラクター名が入る）
//----------------------------------------------------------------------
#include "../../../Header/Component/Animation/MotionList.h"
#include "../../../../File/CFile/CFile.h"

std::map<CHARA_NAME, std::vector<MotionNamePair>> MotionList::_allCharaMotionList;

//--------------------------------------------------------
// @breif モーションリストの読み込み
// @param charaName: キャラクター名
// @param fileName: モーションリストのファイル名
// @return  無し
//--------------------------------------------------------
void MotionList::Load(CHARA_NAME charaName, std::string fileName)
{
	 //すでに該当するキャラクターのモーションリストが存在する場合は読み込まない
	auto itr = _allCharaMotionList.find(charaName);
	if (itr == _allCharaMotionList.end()) {
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

				MotionNamePair m = { motionName, loopTimes };
				_allCharaMotionList[charaName].push_back(m);
			}
		}
	}
}

//--------------------------------------------------------
// @breif モーションリストをすべて削除する
// @return  無し
//--------------------------------------------------------
void MotionList::DeleteAll()
{
	_allCharaMotionList.clear();
}

//--------------------------------------------------------
// ＠breif指定したキャラクターのモーションリストを取得する
// @param charaName: キャラクター名
// @return  モーションリスト
//--------------------------------------------------------
std::vector<MotionNamePair>* MotionList::GetMotionList(CHARA_NAME charaName)
{
	// 指定したキャラクターのモーションリストが存在する場合
	auto itr = _allCharaMotionList.find(charaName);
	if (itr != _allCharaMotionList.end()) {
		return &itr->second;
	}
	// 存在しない場合
	return nullptr;
}
