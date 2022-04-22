//===========================================
//ゲージ処理
//Author:KatoMizuki
//===========================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "object2D.h"

//前方宣言

//================================================
//マクロ定義
//================================================
#define GAUGE_SHOT_POS_X	(SCREEN_WIDTH / 2.0f - GAUGE_SHOT_SIZE_X / 2.0f)	//ショットゲージの位置X
#define GAUGE_SHOT_POS_Y	(100.0f)											//ショットゲージの位置Y
#define GAUGE_SHOT_SIZE_X	(600.0f)											//ショットゲージのサイズX
#define GAUGE_SHOT_SIZE_Y	(50.0f)												//ショットゲージのサイズY

//================================================
//クラスの定義
//================================================
//クラスの定義
class CGauge : public CObject2D
{
public:
	CGauge(CObject::PRIORITY Priority = CObject::PRIORITY::UI);		//コンストラクタ
	~CGauge();									//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nMaxNum, int nNum);

	void AddGauge(int nNum);					//ゲージ増減処理
	void SetGauge(int nNum);					//ゲージ設定処理
	int GetGauge(void) { return m_nNum; }		//ゲージ取得処理
	void SetMaxNum(int nMaxNum);				//ゲージ最大数値設定処理
	int GetMaxNum(void) { return m_nMaxNum; }	//ゲージ最大数値取得処理

private:
	int m_nMaxNum;					//ゲージの最大数値
	int m_nNum;						//ゲージの現在数値
	D3DXVECTOR3 m_sizeMax;			//サイズの最大値
};

#endif // !_GAUGE_H_