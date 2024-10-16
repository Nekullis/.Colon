//----------------------------------------------------------------------
// @filename CharacterBase.h
// @author: Fukuma Kyohei
// @explanation
// キャラクターオブジェクトのマネージャークラス
// プレイヤーや敵などのオブジェクトはここで追加する
//----------------------------------------------------------------------
#include "../../Header/Character/CharacterManager.h"
#include "../../Header/Character/CharacterBase.h"
#include "../../Header/System/GameCollision.h"

//----------------------------------------------------------------------
// @brief コンストラクタ
// @return なし
//----------------------------------------------------------------------
CharacterManager::CharacterManager(){
}

//----------------------------------------------------------------------
// @brief デストラクタ
// @return なし
//----------------------------------------------------------------------
CharacterManager::~CharacterManager(){
}

//----------------------------------------------------------------------
// @brief キャラクターオブジェクトをコンテナに追加
// @param chara キャラクターオブジェクト
// @return なし
//----------------------------------------------------------------------
void CharacterManager::AddChara(CharacterBase* chara, GameCollision* col){
	//描画コンポーネントをマネージャー内のコンテナに移動
	for (auto&& component : chara->GetComponent()){
		if (component->GetUpdateOwder() > DRAW_OWDER) {
			m_Draw.push_back(std::move(component));
		}
	}
	if (col) {
		col->AddCollision(chara);
	}
	//コンテナに格納
	m_CharaList.emplace_back(chara);
}

//----------------------------------------------------------------------
// @brief 指定キャラクターオブジェクトの削除
// @param chara キャラクターオブジェクト
// @return なし
//----------------------------------------------------------------------
void CharacterManager::DeleteChara(CharacterBase* chara){
	//条件の合うオブジェクトをコンテナ内から検索
	auto itr = std::find(m_CharaList.begin(), m_CharaList.end(), chara);
	//見つけたオブジェクトの削除
	if (itr != m_CharaList.end()) { m_CharaList.erase(itr); }
}

//----------------------------------------------------------------------
// @brief 更新処理
// @return なし
//----------------------------------------------------------------------
void CharacterManager::UpDate(){
	//コンテナに入っているのオブジェクトの更新処理
	for (auto&& Chara : m_CharaList){
		Chara->Process();
	}
}

//----------------------------------------------------------------------
// @brief 描画処理
// @return なし
//----------------------------------------------------------------------
void CharacterManager::Render(){
	//コンテナに入っているのオブジェクトの更新処理
	for (auto&& Draw : m_Draw) {
		Draw->Update();
	}
}
