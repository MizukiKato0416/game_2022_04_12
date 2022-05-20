//===========================================
//スコア処理
//Authore:加藤瑞葵
//===========================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "object.h"
#include "number.h"

//前方宣言
class CObject2D;

//================================================
//マクロ定義
//================================================
#define MAX_SCORE_POLYGON		(8)				//ポリゴンの最大数
#define MAX_SCORE				(99999999)		//スコアの最大値
#define SCORE_POLYGON_WIDTH		(30.0f)			//ポリゴンの幅
#define SCORE_POLYGON_HEIGHT	(60.0f)			//ポリゴンの高さ

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CScore : public CObject
{
public:
	CScore(CObject::PRIORITY Priority = CObject::PRIORITY::SCORE);	//コンストラクタ
	~CScore();								//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(const int &nScore);
	void AddScore(const int &nValue);
	int GetScore(void);
	CNumber *GetNumber(const int nNumber);

	static CScore *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);

private:
	CNumber *m_apNumber[MAX_SCORE_POLYGON];			//numberのインスタンス
	int m_nScore;									//スコア
	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_size;								//サイズ
	CObject2D *m_pUnit;								//単位のポインタ
	CObject2D *m_pConma;							//スコアのポインタ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_SCORE_H_