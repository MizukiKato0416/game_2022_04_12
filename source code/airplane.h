//===========================================
//飛行機の処理
//Author:KatoMizuki
//===========================================
#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

#include "happening.h"

//前方宣言
class CEffect3D;

//================================================
//マクロ定義
//================================================

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

	bool GetHitPlayer(void) { return m_bHitPlayer; }						//プレイヤーに当たったかどうか取得処理
	void SetHitPlayer(bool bHitPlayer) { m_bHitPlayer = bHitPlayer; }		//プレイヤーに当たったかどうか取得処理

private:
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_rot;						//向き
	bool m_bHitPlayer;						//プレイヤーと当たったかどうか
	int m_nMoveCounter;						//進んでいる時間のカウンター
};

#endif // !_AIRPLANE_H_