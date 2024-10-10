//----------------------------------------------------------------------
// @filename Afterglow.h
// @author: Osaki Nagomi
// @explanation
// 選択項目の処理をする関数のプロトタイプ宣言をするヘッダファイル
//----------------------------------------------------------------------
#include "DxLib.h"
#include "../../Header/EventSystem/EventSystem.h"

//----------------------------------------------------------------------
// @brief 選択処理
// @param input	入力
// @param axis	軸
// @param size	選択肢の数
// @param select	現在の選択肢
// @return 選択中の要素
//----------------------------------------------------------------------
int SelectFocus(int input,const std::string& axis, int size, int select)
{
	// 入力に応じて選択肢を変更
	if (axis == "x") 
	{
		if(input & PAD_INPUT_LEFT)	return (select + size - 1) % size;
		if(input & PAD_INPUT_RIGHT) return (select + 1) % size;
	}
	if (axis == "y") 
	{
		if(input & PAD_INPUT_UP)	return (select + size - 1) % size;
		if(input & PAD_INPUT_DOWN) return (select + 1) % size;
	}

	// 入力がない場合はそのままの値を返す
	return select;
}
