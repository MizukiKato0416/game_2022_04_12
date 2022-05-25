//===========================================
//会話の処理
//Author:KatoMizuki
//===========================================
#ifndef _WIND_H_
#define _WIND_H_

#include "object.h"

//前方宣言
class CEffect2D;
class CObject2D;

//================================================
//マクロ定義
//================================================
#define EFFECT_CLICK_RING_NUM	(2)		//リングエフェクトの数
#define EFFECT_CLICK_STAR_NUM	(3)		//星エフェクトの数

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEffectClick : public CObject
{
public:
	CEffectClick(CObject::PRIORITY Priority = CObject::PRIORITY::CLICK_EFFECT);	//コンストラクタ
	~CEffectClick();															//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffectClick *Create(const D3DXVECTOR3 &pos);

private:
	void Sparkle(void);		//キラキラエフェクトの処理
	void Ring(void);		//リングエフェクトの処理
	void Star(void);		//星エフェクトの処理

	CEffect2D *m_pRing[EFFECT_CLICK_RING_NUM];			//リングエフェクト
	CObject2D *m_pStar[EFFECT_CLICK_STAR_NUM];			//星エフェクト
	CEffect2D *m_pStarBg[EFFECT_CLICK_STAR_NUM];		//星エフェクトの裏のぼかし
	CEffect2D *m_pSparkle;								//キラキラエフェクト
	D3DXVECTOR3 m_pos;									//位置
	int m_nCounter;										//カウンター
	float m_fStarDiffer;								//スターの中心からの距離
	float m_fStarRot[EFFECT_CLICK_STAR_NUM];			//スターの向き
	D3DXVECTOR3 m_ringAddSize[EFFECT_CLICK_RING_NUM];	//リングエフェクトのサイズの加算量	
};

#endif // !_WIND_H_