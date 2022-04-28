//===========================================
//飛行機の処理
//Author:KatoMizuki
//===========================================
#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

#include "happening.h"

//前方宣言
class CEffect3D;
class CSmoke;

//================================================
//マクロ定義
//================================================
#define AIRPLANE_INIT_ROT_Y		(-D3DX_PI / 4.0f)		//生成時の向き
#define AIRPLANE_SMOKE_NUM		(3)						//飛行機雲を出す量

//================================================
//クラスの定義
//================================================
//クラスの定義
class CAirplane : public CHappenig
{
public:
	CAirplane(CObject::PRIORITY Priority = CObject::PRIORITY::HAPPENING);		//コンストラクタ
	~CAirplane();																//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CAirplane *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);

	bool GetHitPlayer(void) { return m_bHitPlayer; }							//プレイヤーに当たったかどうか取得処理
	void SetHitPlayer(const bool bHitPlayer) { m_bHitPlayer = bHitPlayer; }		//プレイヤーに当たったかどうか取得処理

private:
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_rot;						//向き
	bool m_bHitPlayer;						//プレイヤーと当たったかどうか
	int m_nMoveCounter;						//進んでいる時間のカウンター
	vector<CSmoke*> m_pSmoke;				//飛行機雲のポインタ
};

#endif // !_AIRPLANE_H_