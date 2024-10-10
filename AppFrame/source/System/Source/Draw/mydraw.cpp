//----------------------------------------------------------------------
// @filename mydraw.cpp
// @author: Saito Ko 
// @explanation
// 行列を用いた回転移動拡大ができる描画関数をまとめたヘッダファイル
//----------------------------------------------------------------------
#include "../../Header/Draw/mydraw.h"

//----------------------------------------------------------------------
// @brief 画像の中心で回転して描画する
// @param mView ビュー行列
// @param position 位置
// @param zoom 拡大率
// @param angle 回転角度
// @param width 画像の幅
// @param height 画像の高さ
// @param cgHandle 画像ハンドル
// @return なし
//----------------------------------------------------------------------
void _MyDrawModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle, int turn) {
	// 回転×拡縮×並行移動
	MATRIX mRot = MGetRotZ(angle);						// 2Dでx,yを回転させるには、3DならZ軸回転になる
	MATRIX mScale = MGetScale(VGet(zoom, zoom, 1));		// Z方向の倍率は1のまま
	MATRIX mTrans = MGetTranslate(position);
	MATRIX m;
	m = MMult(mRot, mScale);
	m = MMult(m, mTrans);

	m = MMult(m, mView);

	// 描画する画像の4つの頂点座標
	VECTOR pos[4] = {
		// 通常用（左上から右回り）
		VGet(-width / 2.0f, -height / 2.0f, 0),	// 左上
		VGet(width / 2.0f, -height / 2.0f,0),	// 右上
		VGet(width / 2.0f,  height / 2.0f ,0),	// 右下
		VGet(-width / 2.0f,  height / 2.0f ,0),	// 左下
	};
	if(turn != 0) {
		// 反転用
		VECTOR posTurn[4] = {
			// 反転用（右上から左回り）
			VGet(width / 2.0f, -height / 2.0f,0),	// 右上
			VGet(-width / 2.0f, -height / 2.0f, 0),	// 左上
			VGet(-width / 2.0f,  height / 2.0f,0),	// 左下
			VGet(width / 2.0f,  height / 2.0f,0),	// 右下
		};
		for(int i = 0; i < 4; i++) {
			pos[i] = posTurn[i];
		}
	}

	// 4つの頂点座標全てに行列を掛けて変換する
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	// 変換した座標で描画する
	DrawModiGraphF(
		pos[0].x, pos[0].y,
		pos[1].x, pos[1].y,
		pos[2].x, pos[2].y,
		pos[3].x, pos[3].y,
		cgHandle, true);
}

//----------------------------------------------------------------------
// @brief 画像の中心で回転して描画する
// @param mView ビュー行列
// @param position 位置
// @param zoom 拡大率
// @param angle 回転角度
// @param width 画像の幅
// @param height 画像の高さ
// @param cgHandle 画像ハンドル
// @return なし
//----------------------------------------------------------------------
void MyDrawModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle) {
	// 左右反転しない
	_MyDrawModiGraph(mView, position, zoom, angle, width, height, cgHandle, 0);
}

//----------------------------------------------------------------------
// @brief 画像を反転して中心で回転し描画する
// @param mView ビュー行列
// @param position 位置
// @param zoom 拡大率
// @param angle 回転角度
// @param width 画像の幅
// @param height 画像の高さ
// @param cgHandle 画像ハンドル
// @return なし
//----------------------------------------------------------------------
void MyDrawTurnModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle) {
	// 左右反転する
	_MyDrawModiGraph(mView, position, zoom, angle, width, height, cgHandle, 1);
}

//----------------------------------------------------------------------
// @brief 4点を指定して四角を描く
// @param mView ビュー行列
// @param pos 4つの頂点座標
// @param Color 色
// @param FillFlag 塗りつぶしフラグ
// @return なし
//----------------------------------------------------------------------
void MyDraw4PointBox(MATRIX mView, VECTOR pos[4], unsigned int Color, int FillFlag) {
	MATRIX m = mView;

	// 4つの頂点座標全てに行列を掛けて変換する
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}

	// 塗りつぶしか？
	if(FillFlag == 0) {
		// 変換した座標で、線で四角を描画する
		DrawLineAA(
			pos[0].x, pos[0].y,	// 左上
			pos[1].x, pos[1].y,	// 右上
			Color);
		DrawLineAA(
			pos[1].x, pos[1].y,	// 右上
			pos[3].x, pos[3].y,	// 右下
			Color);
		DrawLineAA(
			pos[3].x, pos[3].y,	// 右下
			pos[2].x, pos[2].y,	// 左下
			Color);
		DrawLineAA(
			pos[2].x, pos[2].y,	// 左下
			pos[0].x, pos[0].y,	// 左上
			Color);
	}
	else {
		// 変換した座標で、三角形２つを描画する
		DrawTriangleAA(
			pos[0].x, pos[0].y,	// 左上
			pos[1].x, pos[1].y,	// 右上
			pos[2].x, pos[2].y,	// 左下
			Color, FillFlag);
		DrawTriangleAA(
			pos[1].x, pos[1].y,	// 右上
			pos[2].x, pos[2].y,	// 左下
			pos[3].x, pos[3].y,	// 右下
			Color, FillFlag);
	}
}

//----------------------------------------------------------------------
// @brief 矩形を描く
// @param mView ビュー行列
// @param x1 左上のx座標
// @param y1 左上のy座標
// @param x2 右下のx座標
// @param y2 右下のy座標
// @param Color 色
// @param FillFlag 塗りつぶしフラグ
// @return なし
//----------------------------------------------------------------------
void MyDrawBox(MATRIX mView, float x1, float y1, float x2, float y2, unsigned int Color, int FillFlag) {
	VECTOR pos[4] = {
		VGet(x1,		y1,		0),	// 左上
		VGet(x2 - 1,	y1,		0),	// 右上
		VGet(x1,		y2 - 1,	0),	// 左下
		VGet(x2 - 1,	y2 - 1,	0),	// 右下
	};
	MyDraw4PointBox(mView, pos, Color, FillFlag);
}

//----------------------------------------------------------------------
// @brief 画像を変形して描画する
// @param mView ビュー行列
// @param x1 左上のx座標
// @param y1 左上のy座標
// @param x2 右上のx座標
// @param y2 右上のy座標
// @param x3 右下のx座標
// @param y3 右下のy座標
// @param x4 左下のx座標
// @param y4 左下のy座標
// @param direction 回転角度
// @param handle 画像ハンドル
// @param FillFlag 塗りつぶしフラグ
// @return なし
//----------------------------------------------------------------------
void MyDrawDeformationGraph(MATRIX mView, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float direction, int handle, int FillFlag) {
	VECTOR pos[4] = {
		VGet(x1,		y1,		0),	// 左上
		VGet(x2 - 1,	y2,		0),	// 右上
		VGet(x3,		y3 - 1,	0),	// 左下
		VGet(x4 - 1,	y4 - 1,	0),	// 右下
	};
	MATRIX mRot = MGetRotZ(direction);
	MATRIX m = mView;
	//m = MMult(m, mRot);

	// 4つの頂点座標全てに行列を掛けて変換する
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	DrawModiGraphF(pos[0].x, pos[0].y, pos[1].x, pos[1].y, pos[2].x, pos[2].y, pos[3].x, pos[3].y, handle, FillFlag);
}

//----------------------------------------------------------------------
// @brief 画像を変形して描画する
// @param mView ビュー行列
// @param x1 左上のx座標
// @param y1 左上のy座標
// @param x2 右下のx座標
// @param y2 右下のy座標
// @param handle 画像ハンドル
// @param FillFlag 塗りつぶしフラグ
// @return なし
//----------------------------------------------------------------------
void MyDrawExtendGraph(MATRIX mView, float x1, float y1, float x2, float y2, unsigned int handle, int FillFlag) {
	VECTOR pos[4] = {
		VGet(x1,		y1,		0),	// 左上
		VGet(x2 - 1,	y1,		0),	// 右上
		VGet(x1,		y2 - 1,	0),	// 左下
		VGet(x2 - 1,	y2 - 1,	0),	// 右下
	};
	MATRIX m = mView;
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	DrawExtendGraphF(pos[0].x, pos[0].y, pos[3].x, pos[3].y, handle, FillFlag);
}

//----------------------------------------------------------------------
// @brief 当たり判定の描画
// @param mView ビュー行列
// @param rc 当たり判定の矩形
// @param Color 色
// @param FillFlag 塗りつぶしフラグ
// @return なし
//----------------------------------------------------------------------
void MyDrawRect(MATRIX mView, MYRECT_PLUS rc, unsigned int Color, int FillFlag){
	MyDrawBox(mView, rc.x, rc.y, rc.x+rc.w, rc.y+rc.h, Color, FillFlag);
}

void MyDrawLine(MATRIX mView, float x1, float y1, float x2, float y2, int Color ) {
	VECTOR pos[] = {
		VGet(x1,		y1,		0),	// 1
		VGet(x2 - 1,	y2,		0),	// 2
	};
	MATRIX m = mView;
	for(int i = 0; i < 2; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	DrawLineAA(pos[0].x, pos[0].y, pos[1].x, pos[1].y, Color);
}

void MyDrawCircle(MATRIX mView, float x, float y, float r) {
	MATRIX m = mView;
	VECTOR pos;
	pos = VGet(x, y, 0);

	pos = VTransform(pos, m);

	DrawCircleAA(pos.x, pos.y, r, GetColor(0,168,0), TRUE);

}

//----------------------------------------------------------------------
// @brief 位置を揃えて文字列を描く
// @param x x座標
// @param y y座標
// @param posBaseX -1:左揃え, 0:中央, 1:右揃え
// @param color 色
// @param str 文字列
// @return なし
// ----------------------------------------------------------------------
void DrawPosString(int x, int y, int posBaseX, unsigned int color, const char* str) {
	int w = GetDrawStringWidth(str, static_cast<int>(strlen(str)));	// 描画する文字の横サイズを得る
	if(posBaseX == 0) {
		// 中央揃えなのでx位置を左に半分ずらす
		x -= w / 2;
	}
	else if(posBaseX > 0) {
		// 右揃えなのでx位置を左にずらす
		x -= w;
	}
	DrawString(x, y, str, color);
}

//----------------------------------------------------------------------
// @brief 画像の塗りつぶし描画
// @param mView ビュー行列
// @param position 位置
// @param zoom 拡大率
// @param angle 回転角度
// @param width 画像の幅
// @param height 画像の高さ
// @param GrHandle 画像ハンドル
// @param Color 色
// @param turn 反転フラグ
// @param param 透明度
// @return なし
//----------------------------------------------------------------------
void PortalIn(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int GrHandle, int Color, int turn,float param)
{
	// 回転×拡縮×並行移動
	MATRIX mRot = MGetRotZ(angle);						// 2Dでx,yを回転させるには、3DならZ軸回転になる
	MATRIX mScale = MGetScale(VGet(zoom, zoom, 1));		// Z方向の倍率は1のまま
	MATRIX mTrans = MGetTranslate(position);
	MATRIX m;
	m = MMult(mRot, mScale);
	m = MMult(m, mTrans);
	m = MMult(m, mView);

	// 描画する画像の4つの頂点座標
	VECTOR pos[4] = {
		// 通常用（左上から右回り）
		VGet(-width / 2.0f, -height / 2.0f, 0),	// 左上
		VGet(width / 2.0f, -height / 2.0f,0),	// 右上
		VGet(width / 2.0f,  height / 2.0f,0),	// 右下
		VGet(-width / 2.0f,  height / 2.0f,0),	// 左下
	};

	// 4つの頂点座標全てに行列を掛けて変換する
	for (int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}

	// Ｚバッファを有効にする
	SetUseZBufferFlag(TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(param));


	// Ｚバッファに画像と同じ大きさのマスクを書き込む
	DrawBoxToZBuffer(static_cast<int>(pos[0].x),
		static_cast<int>(pos[0].y),
		static_cast<int>(pos[2].x),
		static_cast<int>(pos[2].y), TRUE, DX_ZWRITE_MASK);

	// Ｚバッファに画像の形でマスクを刳り貫く
	DrawExtendGraphToZBuffer(static_cast<int>(pos[0].x),
		static_cast<int>(pos[0].y),
		static_cast<int>(pos[2].x),
		static_cast<int>(pos[2].y),
		GrHandle, DX_ZWRITE_CLEAR);

	// 画像の大きさのボックスを描画する(マスクが刳り貫かれているところしか塗りつぶされない)
	DrawBoxAA(pos[0].x, pos[0].y, pos[2].x, pos[2].y, Color, TRUE);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// Ｚバッファを無効にする
	SetUseZBufferFlag(FALSE);
}