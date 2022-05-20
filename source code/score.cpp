//================================================
//スコア処理
//Authore:加藤瑞葵
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "score.h"
#include "manager.h"
#include "number.h"
#include "play_data.h"
#include "texture.h"
#include "object2D.h"

//================================================
//マクロ定義
//================================================
#define SCORE_CONMA_NUM		(6)		//コンマをはさむ位置
#define SCORE_CONMA_SIZE	(15.0f)	//コンマのサイズ
#define SCORE_UNIT_SIZE		(60.0f)	//単位のサイズ
#define SCORE_CONMA_POS_X	(5.0f)	//コンマの位置調整値
#define SCORE_POS_SHIFT_X	(20.0f)	//スコアの位置をずらす量

//================================================
//デフォルトコンストラクタ
//================================================
CScore::CScore(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_nScore = 0;
	memset(m_apNumber, NULL, sizeof(m_apNumber[MAX_SCORE_POLYGON]));
	m_pConma = nullptr;
	m_pUnit = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CScore::~CScore()
{

}

//================================================
//初期化処理
//================================================
HRESULT CScore::Init()
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		//小数点をつけるため、SCORE_COMMA_NUMつ目の数字からずらす
		if (nCntNumber >= SCORE_CONMA_NUM)
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x + SCORE_POS_SHIFT_X - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), m_pos.y, 0.0f),
												     m_size);
		}
		else
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), m_pos.y, 0.0f),
												     m_size);
		}
		m_apNumber[nCntNumber]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("number.png"));
	}

	//コンマの生成
	m_pConma = CObject2D::Create(D3DXVECTOR3(m_pos.x  - SCORE_CONMA_POS_X - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * SCORE_CONMA_NUM) + (m_size.x / 2.0f), m_pos.y + m_size.y / 4.0f, 0.0f),
												      D3DXVECTOR3(SCORE_CONMA_SIZE, SCORE_CONMA_SIZE, 0.0f),
		                                              static_cast<int>(CObject::PRIORITY::SCORE));
	m_pConma->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("conma.png"));

	//単位の生成
	m_pUnit = CObject2D::Create(D3DXVECTOR3(m_pos.x + SCORE_POS_SHIFT_X - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * MAX_SCORE_POLYGON) + (m_size.x / 2.0f), m_pos.y, 0.0f),
								     D3DXVECTOR3(SCORE_UNIT_SIZE, SCORE_UNIT_SIZE, 0.0f),
		                                             static_cast<int>(CObject::PRIORITY::SCORE));
	m_pUnit->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("m.png"));

	return S_OK;
}

//================================================
//終了処理
//================================================
void CScore::Uninit(void)
{
	//プレイデータの取得
	CPlayData *pPlayData = NULL;
	pPlayData = CManager::GetInstance()->GetPlayData();

	//スコアをプレイデータに保存
	pPlayData->SetScore(m_nScore);

	//ナンバーの破棄
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] != nullptr)
		{
			m_apNumber[nCntNumber]->Uninit();
			delete m_apNumber[nCntNumber];
			m_apNumber[nCntNumber] = nullptr;
		}
	}

	//コンマの破棄
	if (m_pConma != nullptr)
	{
		m_pConma->Uninit();
		m_pConma = nullptr;
	}

	//単位の破棄
	if (m_pUnit != nullptr)
	{
		m_pUnit->Uninit();
		m_pUnit = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CScore::Update(void)
{
	
}

//================================================
//描画処理
//================================================
void CScore::Draw(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber]->Draw();
	}
}

//================================================
//生成処理
//================================================
CScore* CScore::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//インスタンスの生成
	CScore *pScore = NULL;
	if (pScore == NULL)
	{
		pScore = new CScore;
		if (pScore != NULL)
		{
			pScore->m_pos = pos;
			pScore->m_size = size;
			pScore->Init();
		}
	}
	return pScore;
}

//================================================
//スコア取得処理
//================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//================================================
//スコア設定処理
//================================================
void CScore::SetScore(const int &nScore)
{
	m_nScore = nScore;

	//最大値よりも大きくなったら
	if (m_nScore > MAX_SCORE)
	{
		//最大値にする
		m_nScore = MAX_SCORE;
	}

	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore / (int)powf(10, MAX_SCORE_POLYGON - 1));
		}
		else if (nCntNumber == MAX_SCORE_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % (int)powf(10, MAX_SCORE_POLYGON - nCntNumber) / (int)powf(10, MAX_SCORE_POLYGON - 1 - nCntNumber));
		}
	}
}

//================================================
//スコア加算処理
//================================================
void CScore::AddScore(const int &nValue)
{
	m_nScore += nValue;

	//最大値よりも大きくなったら
	if (m_nScore > MAX_SCORE)
	{
		//最大値にする
		m_nScore = MAX_SCORE;
	}

	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore / (int)powf(10, MAX_SCORE_POLYGON - 1));
		}
		else if (nCntNumber == MAX_SCORE_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % (int)powf(10, MAX_SCORE_POLYGON - nCntNumber) / (int)powf(10, MAX_SCORE_POLYGON - 1 - nCntNumber));
		}
	}
}

//=============================================================================
// number取得処理
//=============================================================================
CNumber* CScore::GetNumber(int nNumber)
{
	return m_apNumber[nNumber];
}