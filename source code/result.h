//===========================================
//リザルト処理
//Author:加藤瑞葵
//===========================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "object.h"

//================================================
//前方宣言
//================================================
class CRanking;
class CObject2D;

//================================================
//マクロ定義
//================================================

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CResult : public CObject
{
public:
	CResult(PRIORITY priorty = PRIORITY::NONE);				//コンストラクタ
	~CResult();				//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CRanking *m_pRank;
	CObject2D *m_pCommu;
	int m_nResultCounter;				//タイトルに行くまでのカウンター
	bool m_bCommu;
	bool m_bBg;
};
//================================================
//プロトタイプ宣言
//================================================
#endif // !_RESULT_H_