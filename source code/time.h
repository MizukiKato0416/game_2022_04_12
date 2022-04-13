//===========================================
//タイム処理
//Author:加藤瑞葵
//===========================================
#ifndef _TIME_H_
#define _TIME_H_
#include "object.h"
#include "number.h"

//================================================
//マクロ定義
//================================================
#define MAX_TIME_POLYGON		(3)				//ポリゴンの最大数
#define TIME_POLIGON_POSY		(30.0f)			//タイムのポリゴンのposY
#define TIME_POLYGON_WIDTH		(50.0f)			//ポリゴンの幅
#define TIME_POLYGON_HEIGHT		(80.0f)			//ポリゴンの高さ
#define START_TIME				(0)				//最初のタイム

//================================================
//前方宣言
//================================================

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CTime : public CObject
{
public:
	CTime(CObject::PRIORITY Priority = CObject::PRIORITY::UI);		//コンストラクタ
	~CTime();								//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddTime(const int &nValue);
	void SetTime(const int &nTime);
	int GetTime(void);
	CNumber *GetNumber(int nNumber);

	static CTime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nStartTime);

private:
	CNumber *m_apNumber[MAX_TIME_POLYGON];	//numberのインスタンス
	int m_nTime;							//タイム
	int m_nCounter;							//時間を変えるためのカウンター
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_size;						//サイズ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_SCORE_H_#pragma once
