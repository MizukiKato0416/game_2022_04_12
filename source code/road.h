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
class CModelSingle;
class CHappenig;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRoad : public CObject
{
public:
	//---------------------------
	// 列挙型
	//---------------------------
	enum class CANDIDATES_PLACE
	{
		CANDIDATES_00 = 0,	// 候補1
		CANDIDATES_01,	// 候補2
		CANDIDATES_02,	// 候補3
		CANDIDATES_03,	// 候補4
		CANDIDATES_04,	// 候補5
		CANDIDATES_05,	// 候補5
		MAX	// 総数
	};
	CRoad(CObject::PRIORITY priorty = PRIORITY::ROAD);	// デフォルトコンストラクタ
	~CRoad();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	static CRoad *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const float &move_speed);	// 生成処理
	void SetSpeed(const float &move_speed) { m_move_speed = move_speed; }	// セッター
	float GetSpeed(void) { return m_move_speed; }	// ゲッダー
	void DeleteRoad(void);	// 道削除処理

private:
	void SkyInstallation(const int &happening_type, const int &installation_position_x, const int &installation_position_y);	// 空用の設置
	void GroundInstallation(const int &happening_type, const int &installation_position);	// 地面用の設置
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_size;	// サイズ
	CModelSingle *m_cloud;	// 雲
	CFloor *m_floor;	// 床
	vector<CHappenig*> m_happening_model;	// ハプニング用モデル
	float m_move_speed;	// 移動量
};
#endif