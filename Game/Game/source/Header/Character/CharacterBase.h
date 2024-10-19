//----------------------------------------------------------------------
// @filename CharacterBase.h
// @author: Fukuma Kyohei
// @explanation
// オブジェクトの派生クラス
// プレイヤーや敵クラスはここから派生する
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
//定数
constexpr auto GRAVITY_VALUE = 10.0f;

class CharacterBase : public ObjectBase
{
public:
	CharacterBase(class ModeBase* game);
	virtual ~CharacterBase() override;
	virtual void Process()	 override;
	virtual void Render()	 override;
	virtual void Debug()	 override;
	//ゲッター
	float GetLineSeg()				  const { return m_LineSeg; }
	int	GetHandle()					  const { return m_Handle; }
	int GetHp()						  const { return m_Hp; }
	bool GetUseGravity()			  const { return m_UseGravity; }
	//セッター
	void SetLineSeg		(float line)		{ m_LineSeg = line; }
	void SetHandle		(int handle)		{ m_Handle = handle; }
	void SetHp			(int hp)			{ m_Hp = hp; }
	void SetUseGravity	(bool useGravity)	{ m_UseGravity = useGravity; }
protected:
	//モデルハンドル
	int m_Handle;
	//体力
	int m_Hp;
	//線分長さ
	float m_LineSeg;
	//重力に干渉するか
	bool m_UseGravity;
};

