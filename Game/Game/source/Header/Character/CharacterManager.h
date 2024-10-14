//----------------------------------------------------------------------
// @filename CharacterManager.h
// @author: Fukuma Kyohei
// @explanation
// キャラクターオブジェクトのマネージャークラス
// プレイヤーや敵などのオブジェクトはここで追加する
//----------------------------------------------------------------------
#pragma once
#include <vector>
#include "appframe.h"
//定数
auto constexpr DRAW_OWDER = 200;
class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager();
	void UpDate();
	void Render();
	//キャラクター追加
	void AddChara(class CharacterBase* chara, class GameCollision* col = nullptr);
	//キャラクター削除
	void DeleteChara(class CharacterBase* chara);
	//ゲッター
	std::vector<class CharacterBase*>	GetCharaList()	const { return m_CharaList; }
protected:
	//キャラクターオブジェクトコンテナ
	std::vector<class CharacterBase*> m_CharaList;
	//描画コンポーネントコンテナ
	std::vector<Component*> m_Draw;
};

