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

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CScore::CScore(CObject::PRIORITY Priority) :CObject(Priority)
{
	m_nScore = 0;
	memset(m_apNumber, NULL, sizeof(m_apNumber[MAX_SCORE_POLYGON]));
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
		m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(m_pos.x - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), m_pos.y, 0.0f),
												 m_size);
		m_apNumber[nCntNumber]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_NUMBER"));
	}
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
CScore* CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
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