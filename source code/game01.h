//===========================================
//ゲーム処理
//Author:加藤瑞葵
//===========================================
#ifndef _GAME01_H_
#define _GAME01_H_
#include "object.h"
#include "main.h"

//前方宣言
class CPlayer;
class CFloor;
class CRoad;
class CGauge;
class CBg;

//================================================
//マクロ定義
//================================================
#define GAME01_MAX_ROAD		(2)		//道の最大数
#define GAME01_MAX_BG		(3)		//背景の最大数

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
class CGame01 : public CObject
{
public:
	CGame01(CObject::PRIORITY Priority = CObject::PRIORITY::NONE);		//コンストラクタ
	~CGame01();									//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Camera(void);					//カメラの処理
	void Road(void);					//道の処理
	void Gauge(void);					//ゲージ処理
	void Shot(void);					//発射処理

	//メンバ変数
	CPlayer *m_pPlayer;					//プレイヤーのポインタ
	CFloor *m_pFloor;					//床のポインタ
	CRoad *m_apRoad[GAME01_MAX_ROAD];	//道のポインタ
	D3DXVECTOR3 m_mouseTriggerPos;		//マウスをクリックした瞬間の位置
	CGauge *m_pGauge;					//発射ゲージ
	int m_nGaugeCounter;				//ゲージが満タンの時間を設定するためのカウンター
	CBg *m_pBg[GAME01_MAX_BG];			//背景のポインタ
};

#endif // !_GAME01_H_