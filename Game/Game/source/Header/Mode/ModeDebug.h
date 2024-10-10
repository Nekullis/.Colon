//----------------------------------------------------------------------
// @filename ModeGame.h
// @date: 2024/9/11
// @author: saito ko
// @explanation
// ボスバトル以外のステージを管理するクラス
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
class ModeDebug : public ModeBase
{
	typedef ModeBase base;
public:
	bool Initialize()override;
	bool Terminate()override;
	bool Process()override;
	bool Render()override;
};
