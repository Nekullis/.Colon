//----------------------------------------------------------------------
// @filename GameStage.cpp
// @author: Fukuma Kyohei
// @explanation
// ゲームステージクラス
// ステージの処理全般クラス
//----------------------------------------------------------------------
#pragma once
#include "../CharacterBase.h"
class GameStage :public CharacterBase
{
public:
	GameStage(class ModeBase* game);
	virtual ~GameStage();
	void Process()	override;
protected:
	//入力処理コンポーネント
	class InputComponent* m_Input;
	class OBB* m_Obb;
	class OBBColComponent* m_Col;
	class DrawOBBComponent* m_Draw;
};

