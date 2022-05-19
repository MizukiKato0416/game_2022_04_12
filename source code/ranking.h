//===========================================
//ランキング処理
//Authore:加藤瑞葵
//===========================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "object.h"
#include "number.h"
#include "score.h"

//前方宣言
class CTcpClient;
class CCommunicationData;

//================================================
//マクロ定義
//================================================
#define MAX_RANKING (6)								//ランキングの最大数
#define MAX_SCORE_DATA (MAX_RANKING + 1)			//スコアデータの最大数
#define RANKING_POLYGON_WIDTH (30.0f * 1.0f)		//ポリゴンの幅
#define RANKING_POLYGON_HEIGHT (60.0f * 1.0f)		//ポリゴンの高さ

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CRanking : public CObject
{
public:
	CRanking(CObject::PRIORITY Priority = CObject::PRIORITY::RANKING);		//コンストラクタ
	~CRanking();									//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetConnect(void) { return m_bConnect; }
	bool GetOnece(void) { return m_bOnece; }

	static CRanking *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);
	static void Connect(CTcpClient *pCommu, CCommunicationData *pCommuData, D3DXVECTOR3 pos, D3DXVECTOR3 size, bool *bConnect, bool *bOnece);
	static void CreateScore(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static CScore *m_apScore[MAX_RANKING];	//スコアのポインタ
	CTcpClient *m_pCommu;					//通信用
	CCommunicationData *m_pCommuData;		//通信データ
	int m_nScore[MAX_SCORE_DATA];			//スコア
	int m_nNowScore;						//今回のスコア
	bool m_bConnect;						//通信できたか
	bool m_bOnece;							//一回だけ
	D3DCOLORVALUE	m_col;					//カラー
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_size;						//サイズ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_RANKING_H_