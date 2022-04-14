//=============================================================================
//
// rsoad処理 [road.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _ROAD_H_
#define _ROAD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CFloor;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRoad : public CObject
{
public:
	//---------------------------
	// 列挙型
	//---------------------------
	enum class HAPPENING_TYPE
	{
		NONE = 0,	// 無し
	};
	CRoad(CObject::PRIORITY priorty = PRIORITY::ROAD);	// デフォルトコンストラクタ
	~CRoad();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	static CRoad *Create(const D3DXVECTOR3 &pos, const HAPPENING_TYPE &type, const float &move_speed);	// 生成処理
	void SetSpeed(const float &move_speed) { m_move_speed = move_speed; }	// セッター
	float GetSpeed(void) { return m_move_speed; }	// ゲッダー
private:
	HAPPENING_TYPE m_happening_type;	// 種類
	D3DXVECTOR3 m_pos;	// 位置
	CFloor *m_floor;	// 床
	float m_move_speed;	// 移動量
};

#endif