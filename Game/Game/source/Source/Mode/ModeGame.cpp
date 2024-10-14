//----------------------------------------------------------------------
// @filename ModeGame.cpp
// @author: saito ko
// @explanation
// ゲーム本編を管理するクラス
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Character/CharacterManager.h"
#include "../../Header/Character/GameStage/GameStage.h"
#include "../../Header/Character/Player/Player.h"
//----------------------------------------------------------------------
// @brief 初期化処理
// @return 無し
//----------------------------------------------------------------------
bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	// マネージャーの取得
	m_CharaManager = NEW CharacterManager();
	m_CharaManager->AddChara(NEW GameStage(this));
	m_CharaManager->AddChara(NEW Player(this));
	return true;
}
//----------------------------------------------------------------------
// @brief 終了処理
// @return 成功しているか
//----------------------------------------------------------------------
bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool ModeGame::Process() {
	base::Process();
	m_CharaManager->UpDate();
	return true;
}
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool ModeGame::Render() {
	base::Render();
	m_CharaManager->Render();
	return true;
}
