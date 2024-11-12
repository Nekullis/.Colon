//----------------------------------------------------------------------
// @filename ModeGame.h
// @date: 2023/12/14
// @author: Fukuma Kyohei
// @explanation
// ボスバトル以外のステージを管理するクラス
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
#include "dxlib.h"

class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize()override;
	virtual bool Terminate()override;
	virtual bool Process()override;
	virtual bool Render()override;
	//ゲッター
	class CharacterManager* GetCharaManager() const { return m_CharaManager; }
protected:
	class CharacterManager* m_CharaManager;
	class GameCollision* m_GameCol;
};