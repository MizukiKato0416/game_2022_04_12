//===========================================
//プレイデータ管理処理
//Author:加藤瑞葵
//===========================================
#ifndef _PLAY_DATA_H_
#define _PLAY_DATA_H_
#include "main.h"

//前方宣言
class CGauge;
class CScore;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CPlayData
{
public:
	CPlayData();			//コンストラクタ
	~CPlayData();			//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);

	void SetScore(const int &nScore) { m_nScore = nScore; }							//スコアの設定
	int GetScore(void) { return m_nScore; }											//スコアの取得
	void SetScorePoint(CScore *&pScore) { m_pScore = pScore; }						//スコアのポインタ設定処理
	CScore *GetScorePoint(void) { return m_pScore; }								//スコアのポインタ取得処理
	void SetTime(const int &nTime) { m_nTime = nTime; }								//時間の設定
	int GetTime(void) { return m_nTime; }											//時間の取得

private:
	//メンバ変数
	int m_nScore;					//スコア
	CScore *m_pScore;				//スコアのポインタ
	int m_nTime;					//時間
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_PLAY_DATA_H_